/*
=============================================================================
Title : cleanInput.cpp
Description : This file cleans the input returned from the API
Author : Kaitlyn Urano (R#11555972)
Date : 04/18/2024
Version : 1.1
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void cleanElevator(string input){
    istringstream iss(input);

    string bayID, directionString;
    int currentFloor, passengerCount, remainingCapacity; 

    getline(iss, bayID, '|');
    iss >> currentFloor;
    getline(iss, directionString, '|');
    iss >> passengerCount;
    iss >> remainingCapacity;
}

void cleanPerson(string input){
    istringstream iss(input);

    string personID;
    int startFloor, endFloor; 

    getline(iss, personID, '|');
    iss >> startFloor;
    iss >> endFloor;
}

int main(){
    cleanElevator("A|1|U|2|8");
    cleanPerson("Eric_R|1|2");
}