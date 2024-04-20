/*
=============================================================================
Title : reader.cpp
Description : This file contains the struct for elevator and people along with their buffers
Author : Kaitlyn Urano (R#11555972)
Date : 04/20/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/

mutex peopleMtx;
mutex elevatorMtx;

// Struct to represent a person
struct Person {
    string name;
    int start;
    int end;
    int arrival;
    int wait;
};

// Buffer for people
vector<Person> peopleBuffer;

// Struct to represent an elevator
struct Elevator {
    string id;
    int lowestFloor;
    int highestFloor;
    int currentFloor;
    string direction;
    int passengerCount;
    int remainingCapacity;
    int totalCapacity;
};

// Buffer for elevator
vector<Elevator> elevatorBuffer;