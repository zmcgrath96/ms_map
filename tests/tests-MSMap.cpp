#include <vector>

#include "../src/MSMap.hpp"
#include "catch.hpp"

bool hasString(std::vector<std::string> strings, std::string search){
    for (std::string s: strings) if (s == search) return true;
    return false;
}

TEST_CASE("Testing MSMap functions"){
    MSMap * map;

    SECTION("Initializing a map should not throw any errors"){
        REQUIRE_NOTHROW(map = new MSMap());
    }

    map = new MSMap();
    SECTION("Adding a singular value should not throw an error and search for it should return it"){
        REQUIRE_NOTHROW(map->insert((float)316.308, "ZAM"));
        REQUIRE(hasString(map->search((float)316.307, 20), "ZAM"));
    }

    SECTION("Adding 2 values close enough together and a large enough tolerance in search returns both"){
        REQUIRE_NOTHROW(map->insert((float)316.308, "ZAM"));
        REQUIRE_NOTHROW(map->insert((float)316.31, "ZXM"));

        std::vector<std::string> results = map->search(316.309, 20);

        REQUIRE(hasString(results, "ZAM"));
        REQUIRE(hasString(results, "ZXM"));
    }

    SECTION("Adding 2 values to the same mass will return both sequences on search"){
        REQUIRE_NOTHROW(map->insert((float)316.308, "ZAM"));
        REQUIRE_NOTHROW(map->insert((float)316.308, "AZM"));

        std::vector<std::string> results = map->search(316.308, 5);

        REQUIRE(hasString(results, "ZAM"));
        REQUIRE(hasString(results, "AZM"));
    }

    SECTION("Adding 2 values of the same mass will NOT create duplicat strings"){
        REQUIRE_NOTHROW(map->insert((float)316.308, "ZAM"));
        REQUIRE_NOTHROW(map->insert((float)316.308, "ZAM"));

        int numSeqs = 0;

        for (std::string result: map->search((float)316.308, 10)){
            if (result == "ZAM") numSeqs ++;
        }

        REQUIRE(numSeqs == 1);
    }

}