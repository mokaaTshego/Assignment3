#define CATCH_CONFIG_MAIN // So that catch will define a main method
#include "catch.hpp"
#include "PGMImageProcessor.h"
#include "ConnectedComponents.h"
#include <limits.h>

//Testing using chess-thresh.pgm
const int ZERO_COMPONENTS = 0; //no components
const int THRESHOLD = 200;
const int MIN = 3;
const int MAX = 6;
std::string INPUT_FILENAME = "chess-thresh.pgm";
std::string OUTPUT_FILENAME = "new.pgm";
MKXTSH013 :: PGMImageProcessor pgmprocessor;

TEST_CASE("PGMImageProcessor Class Unit Tests"){


    SECTION("Reading file"){

        REQUIRE(pgmprocessor.readFile(INPUT_FILENAME) == true);

    }
    SECTION("Extracting Components"){ //check if components are extracted

        REQUIRE(pgmprocessor.extractComponents(THRESHOLD,MIN) == 15812);
    }

    SECTION("Filtered Components"){ // check for filtered

        REQUIRE(pgmprocessor.filterComponentsBySize(MIN,MAX) == 15812);

    }
    SECTION("Write OutputFile"){

        REQUIRE(pgmprocessor.writeComponents(OUTPUT_FILENAME) == true);

    }



}
