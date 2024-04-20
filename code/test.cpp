/*SAMPLE FORMAT 

TEST_CASE("functions", "functions")
{
    REQUIRE_FALSE(function1(0));
    REQUIRE_FALSE(function1(5));
    REQUIRE(function1(10));
}
*/

//do we need test cases for all function? or just functions that retur something?

#include "Catch2/catch.hpp"
#include "functions.h"

//test cases for reader.cpp functions
TEST_CASE("Clean elevator status - Valid input", "[cleanElevatorStatus]")
{
    std::string input = "Elevator1|5|UP|2|8";
    Elevator result = cleanElevatorStatus(input);
    REQUIRE(result.id == "Elevator1");
    REQUIRE(result.currentFloor == 5);
    REQUIRE(result.direction == "UP");
    REQUIRE(result.passengerCount == 2);
    REQUIRE(result.remainingCapacity == 8);
}

TEST_CASE("Clean elevator status - Empty input", "[cleanElevatorStatus]")
{
    std::string input = "";
    REQUIRE_FALSE(cleanElevatorStatus(input))
   
}

//test cases for scheduler.cpp functions