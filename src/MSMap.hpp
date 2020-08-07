#ifndef MSMAP_H
#define MSMAP_H

#include <unordered_map>
#include <vector>
#include <iostream>

#include "utils.hpp"

#define DELTA       .0001

class massSequences {
public:
    float mass;
    std::vector<std::string> sequences;

    massSequences();
    massSequences(float mass, std::string sequence);
};

class MSMapEntry {
public:
    std::vector<massSequences *> massSequencesVec;

    MSMapEntry();

    /**
     * Add a mass and sequence to the interlal list of massSequences
     * 
     * @param mass      float       the mass value converted to an int after the decimal
     * @param sequence  std::string the sequence associated with the mass
    */
    void addMassSequence(float mass, std::string sequence);

    /**
     * Get the list of massSequences that contain the mass += a tolerance
     * 
     * @param mass      float       the mass value to search for
     * @param ppmTol    int         the tolerance in parts per million to allow in the search
     * 
     * @return vector<std::string>  the sequences that have a mass within the tolerance
    */
    std::vector<std::string> getValuesByMass(float mass, int ppmTol);
};

class MSMap {
private:
    std::unordered_map<int, MSMapEntry *> internalMap;

public:
    MSMap();

    /**
     * Add a sequence with a mass to the table
     * 
     * @param mass      float   the mass associated with the input sequence
     * @param sequence  string  the string of amino acids with the input mass
     * 
    */
    void insert(float mass, std::string sequence);

    /**
     * Get all the sequences associated with a mass
     * 
     * @param mass      float   the mass to search for
     * @param ppmTol    int     the tolerance to allow when searching for the mass
     * 
     * @return vector<string>   all sequences with a mass that falls within the tolerance of the mass
    */
    std::vector<std::string> search(float mass, int ppmTol);

};
#endif