/*
============================================================================================
Title : functions.cpp
Description : This file contains functions seleceted for unit testing
Author : Isha Koregave (R#11743130)
Date : 04/21/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : 
C++ Version : Version 11
===========================================================================================
*/

#include <functions.h>
#include "catch.hpp"
//READER THREAD BASE FUNCTIONS


Person cleanPerson(string input){// Function to clean the people data
    istringstream iss(input);
    Person person;

    getline(iss, person.name, '|');
    iss >> person.start;
    iss.ignore(1);
    iss >> person.end;
    person.distance = person.end - person.start;
    return person;
}

//ELEVATOR STATUS THREAD BASE FUNCTIONS

Elevator cleanBldgElevator(string input){//Function to clean .bdlg file data
    istringstream iss(input);
    Elevator elevator;

    getline(iss, elevator.id, '\t');
    iss >> elevator.lowestFloor;
    iss >> elevator.highestFloor;
    iss >> elevator.currentFloor;
    iss >> elevator.totalCapacity;

    return elevator;
}


Elevator cleanElevatorStatus(string input){//Function to clear elevator status data from API
    istringstream iss(input);
    Elevator elevator;

    getline(iss, elevator.id, '|');
    iss >> elevator.currentFloor;
    getline(iss, elevator.direction, '|');
    iss >> elevator.passengerCount;
    iss >> elevator.remainingCapacity;

    return elevator;
}


vector<Person> getGroup(Elevator selectedElevator){//Function to group candidates together for elevator trips

    // Vector to store group of candidates with similar trips
    vector<Person> group = {};
    // If there is enough remaining capacity for a group of people
    if (selectedElevator.remainingCapacity > 2){
        // Add selected person to the group
        peopleMtx.lock();
        Person selectedPerson = peopleBuffer.front();
        peopleBuffer.erase(peopleBuffer.begin());
        peopleMtx.unlock();

        group.push_back(selectedPerson);
        int peopleInGroup = 1;

        // Check for all candidates in the peopleBuffer 
        int size = peopleBuffer.size();
        for(int i = 0; i < size; i++){
            Person candidate = peopleBuffer[i];
            if (peopleInGroup >= selectedElevator.remainingCapacity){
                break;
            }
            // If candidate is going up and their trip is within range of the selectedPerson going up
            if ((candidate.distance > 0 && selectedPerson.distance > 0) && (candidate.start >= selectedPerson.start && candidate.start <= selectedPerson.end && candidate.end <= selectedPerson.end && candidate.end >= selectedPerson.start)){
                group.push_back(candidate);
                peopleInGroup++;
                // Remove the candidate from the peopleBuffer
                peopleMtx.lock();
                peopleBuffer.erase(peopleBuffer.begin() + i);
                i--;
                size--;
                peopleMtx.unlock();
            }
            // If candidate is going down and their trip is within range of the selectedPerson going down
            if ((candidate.distance < 0 && selectedPerson.distance < 0) && (candidate.start <= selectedPerson.start && candidate.start >= selectedPerson.end && candidate.end >= selectedPerson.end && candidate.end <= selectedPerson.start)){
                group.push_back(candidate);
                peopleInGroup++;
                // Remove the candidate from the peopleBuffer
                peopleMtx.lock();
                peopleBuffer.erase(peopleBuffer.begin() + i);
                i--;
                size--;
                peopleMtx.unlock();
            }
        }
    }
    return group;
}

// SCHEDULER THREAD BASE FUNCTIONS


Elevator getElevator(){//Function to get the next elevator
    while(elevatorBuffer.empty()){
        this_thread::sleep_for(chrono::milliseconds(100));
        continue;
    }
    elevatorMtx.lock();
    Elevator nextElevator = elevatorBuffer.front();
    elevatorBuffer.erase(elevatorBuffer.begin());
    elevatorBuffer.push_back(nextElevator);
    elevatorMtx.unlock();
    return nextElevator;
}



