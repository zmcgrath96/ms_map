#include <iostream>
#include <vector>

#include "MSMap.hpp"

int main(){

    MSMap * map = new MSMap();

    float mass = 316.308;
    std::string sequence = "ZAM";

    std::cout << "Adding mass with sequence to the map\n";
    map->insert(mass, sequence);

    mass = 218.095;
    sequence = "PSM";

    std::cout << "Adding a different mass with a different sequence to the map\n";
    map->insert(mass, sequence);

    std::cout << "Searching for mass that we put in there\n";
    std::vector<std::string> results = map->search((float)316.302, 20);

    std::cout << "Results:\n";
    for (std::string result: results) std::cout << result + " ";
    std::cout << "\n";

    return 1;
}