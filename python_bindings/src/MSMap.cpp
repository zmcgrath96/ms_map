#include "MSMap.hpp"

/******************** massSequences ********************/
massSequences::massSequences(){}

massSequences::massSequences(float mass, std::string sequence){
    this->mass = mass;
    this->sequences.push_back(sequence);
}

/******************** MSMapEntry ********************/
MSMapEntry::MSMapEntry(){}

/**
 * Add a mass and sequence to the interlal list of massSequences
 * 
 * @param mass      float       the mass value converted to an int after the decimal
 * @param sequence  std::string the sequence associated with the mass
*/
void MSMapEntry::addMassSequence(float mass, std::string sequence){
    
    // if we find a mass remainder that is equal to mass, add the sequence and return
    for (massSequences * ms: this->massSequencesVec){
        if (std::abs(mass - ms->mass) < DELTA){

            // make sure that the vector of sequences DOESN'T already have this sequence
            for (std::string seq: ms->sequences) if (seq == sequence) return;

            ms->sequences.push_back(sequence);
            return;
        }
    }

    // making it this far means that we have not found it, so we should add a new one
    massSequences * newEntry = new massSequences(mass, sequence);
    this->massSequencesVec.push_back(newEntry);
}

/**
 * Get the list of massSequences that contain the mass += a tolerance
 * 
 * @param mass      float       the mass value to search for
 * @param ppmTol    int         the tolerance in parts per million to allow in the search
 * 
 * @return vector<massSeuences *> the massSequences that have a mass within the tolerance
*/
std::vector<std::string> MSMapEntry::getValuesByMass(float mass, int ppmTol){
    // look through my mass sequence vec to see if we have a mass within the tolerance
    std::vector<std::string> results;

    // get the upper and lower bounds to the mass
    float DaTol = ppmToDa(mass, ppmTol);
    float lowerBound = mass - DaTol;
    float upperBound = mass + DaTol;

    // go through each of the values in the internal list and search for the bounds
    for (massSequences * ms: this->massSequencesVec){
        // if the mass at this sequence is within the tolerance, add the 
        // sequences to the results list
        if (lowerBound <= ms->mass && ms->mass <= upperBound){
            std::vector<std::string> copiedKmers(ms->sequences);
            results.insert(results.end(), copiedKmers.begin(), copiedKmers.end());
        }
    }

    return results;
}

/******************** MSMap ********************/
MSMap::MSMap(){}

/**
 * Add a sequence with a mass to the table
 * 
 * @param mass      float   the mass associated with the input sequence
 * @param sequence  string  the string of amino acids with the input mass
 * 
*/
void MSMap::insert(float mass, std::string sequence){
    // get just the key
    int insertKey = static_cast<int>(mass);

    // check to see if the key is in the map
    std::unordered_map<int, MSMapEntry *>::const_iterator mapReturn = this->internalMap.find(insertKey);

    // if this isn't found, then add a new MSMapEntry at the indes
    if (mapReturn == this->internalMap.end()){
        MSMapEntry * newEntry = new MSMapEntry();
        this->internalMap[insertKey] = newEntry;
    }
    
    // add the mass sequence to the value
    this->internalMap[insertKey]->addMassSequence(mass, sequence);
}

/**
 * Get all the sequences associated with a mass
 * 
 * @param mass      float   the mass to search for
 * @param ppmTol    int     the tolerance to allow when searching for the mass
 * 
 * @return vector<string>   all sequences with a mass that falls within the tolerance of the mass
*/
std::vector<std::string> MSMap::search(float mass, int ppmTol){
    // get the upper and lower bound search keys
    float daTol = ppmToDa(mass, ppmTol);
    float upperBound = mass + daTol;
    float lowerBound = mass - daTol;

    int upperBoundKey = static_cast<int>(upperBound);
    int lowerBoundKey = static_cast<int>(lowerBound);

    // hold the results
    std::vector<std::string> results;

    // check the lower bound first
    std::unordered_map<int, MSMapEntry *>::const_iterator mapLowerBoundReturn = this->internalMap.find(lowerBoundKey);
    if (mapLowerBoundReturn != this->internalMap.end()){
        std::vector<std::string> lowerBoundResults = mapLowerBoundReturn->second->getValuesByMass(mass, ppmTol);
        results.insert(results.end(), lowerBoundResults.begin(), lowerBoundResults.end());
    }

    // if the upper bound key does not equal the lower bound key, search that one too
    if (upperBoundKey == lowerBoundKey) return results;

    std::unordered_map<int, MSMapEntry *>::const_iterator mapUpperBoundReturn = this->internalMap.find(upperBoundKey);
    if (mapUpperBoundReturn != this->internalMap.end()){
        std::vector<std::string> upperBoundResults = mapUpperBoundReturn->second->getValuesByMass(mass, ppmTol);
        results.insert(results.end(), upperBoundResults.begin(), upperBoundResults.end());
    }

    return results;
}