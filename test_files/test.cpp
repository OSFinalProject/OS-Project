/*
============================================================================================
Title : test.cpp
Description : This file contains tests for the functions seleceted for unit testing
Author : Isha Koregave (R#11743130)
Date : 04/21/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : 
C++ Version : Version 11
===========================================================================================
*/
#define CONFIG_CATCH_MAIN
#include "catch.hpp"
#include "functions.h"


//TEST CASES FOR READER THREAD BASE FUNCTIONS
TEST_CASE("Clean person data - Valid input", "cleanPerson")
{
    std::string input = "Alice|2|5";
    Person result = cleanPerson(input);
    REQUIRE(result.name == "Alice");
    REQUIRE(result.start == 2);
    REQUIRE(result.end == 5);
    REQUIRE(result.distance == 3); // Distance should be end - start
}

TEST_CASE("Clean person data - Negative distance", "cleanPerson")
{
    std::string input = "Alice|5|2";
    Person result = cleanPerson(input);
    REQUIRE(result.name == "Alice");
    REQUIRE(result.start == 5);
    REQUIRE(result.end == 2);
    REQUIRE(result.distance == -3);
}

//TEST CASES FOR ELEVATOR STATUS THREAD BASE FUNCTIONS
TEST_CASE("Clean elevator status - Valid input", "cleanElevatorStatus")
{
    std::string input = "Elevator1|5|U|2|8";
    Elevator result = cleanElevatorStatus(input);
    REQUIRE(result.id == "Elevator1");
    REQUIRE(result.currentFloor == 5);
    REQUIRE(result.direction == "U");
    REQUIRE(result.passengerCount == 2);
    REQUIRE(result.remainingCapacity == 8);
}

TEST_CASE("Clean elevator status - Empty input", "cleanElevatorStatus")
{
    std::string input = "";
    REQUIRE_FALSE(cleanElevatorStatus(input))
   
}

TEST_CASE("Clean building elevator - Valid input", "cleanBldgElevator") {
    std::string input = "Elevator1|1|10|5|8";
    Elevator result = cleanBldgElevator(input);
    
    REQUIRE(result.id == "Elevator1");
    REQUIRE(result.lowestFloor == 1);
    REQUIRE(result.highestFloor == 10);
    REQUIRE(result.currentFloor == 5);
    REQUIRE(result.totalCapacity == 8);
}


TEST_CASE("Get group of people for selected elevator - Valid input", "getGroup") {
 
    Elevator selectedElevator;
    selectedElevator.remainingCapacity = 3; // Assuming enough remaining capacity for a group of people

    
    std::vector<Person> peopleBuffer = {
        {"Person1", 2, 5},  
        {"Person2", 3, 7},  
        {"Person3", 1, 6}   
      
    };

    // Assign the mock people buffer to the global variable
    ::peopleBuffer = peopleBuffer;

   
    std::vector<Person> group = getGroup(selectedElevator);


    REQUIRE(group.size() == 3); // Expect three persons in the group

    // Verify the properties of the persons in the group
    REQUIRE(group[0].name == "Person1");
    REQUIRE(group[0].start == 2);
    REQUIRE(group[0].end == 5);
   
}

// SCHEDULER THREAD BASE FUNCTIONS
TEST_CASE("Get next elevator - Elevator buffer not empty (2 elevators)", "[getElevator]") {
    
    std::vector<Elevator> elevatorBuffer = {
        {"Elevator1", 1, 10, 5, 8}, 
        {"Elevator2", 2, 9, 6, 7}   
       
    };

    // Assign the mock elevator buffer to the global variable
    ::elevatorBuffer = elevatorBuffer;

  
    Elevator nextElevator1 = getElevator();
    Elevator nextElevator2 = getElevator();

    // Verify the content of the returned elevators
    REQUIRE(nextElevator1.id == "Elevator1");
    REQUIRE(nextElevator1.lowestFloor == 1);
    REQUIRE(nextElevator1.highestFloor == 10);
    REQUIRE(nextElevator1.currentFloor == 5);
    REQUIRE(nextElevator1.totalCapacity == 8);

    REQUIRE(nextElevator2.id == "Elevator2");
    REQUIRE(nextElevator2.lowestFloor == 2);
    REQUIRE(nextElevator2.highestFloor == 9);
    REQUIRE(nextElevator2.currentFloor == 6);
    REQUIRE(nextElevator2.totalCapacity == 7);

    // Verify the content of the elevator buffer after getting the next elevators
    REQUIRE(elevatorBuffer.empty());// Expecting no elevator in buffer
    REQUIRE(elevatorBuffer[0].id != "Elevator1"); // Ensure the returned elevators are removed from the buffer
    REQUIRE(elevatorBuffer[1].id != "Elevator2");
}



