/*
=============================================================================
Title : reader.cpp
Description : This file cleans the input returned from the API and reads it
Author : Kaitlyn Urano (R#11555972), Carson Spaniel (R#11712895)
Date : 04/18/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <fstream>
#include <mutex>
#include "api.cpp"
#include "struct.cpp"

using namespace std;


// Function to clear elevator status data from API
Elevator cleanElevatorStatus(string input){
    for(int i=0;i<input.length();i++){
        if(int(input[i]) == 9){
            input[i] = '|';
        }
    }

    // cout << input << "\n";
    istringstream iss(input);
    Elevator elevator;

    getline(iss, elevator.id, '|');
    iss >> elevator.currentFloor;
    getline(iss, elevator.direction, '|');
    iss >> elevator.passengerCount;
    iss >> elevator.remainingCapacity;

    return elevator;
}

// Function to clean .bdlg file data
Elevator cleanBldgElevator(string input){
    istringstream iss(input);
    Elevator elevator;

    getline(iss, elevator.id, '\t');
    iss >> elevator.lowestFloor;
    iss >> elevator.highestFloor;
    iss >> elevator.currentFloor;
    iss >> elevator.totalCapacity;

    return elevator;
}

// Function to clean the people data
Person cleanPerson(string input){
    istringstream iss(input);
    Person person;

    getline(iss, person.name, '|');
    iss >> person.start;
    iss.ignore(1);
    iss >> person.end;
    person.wait = 0;
    // person.arrival = datetime   

    // cout << "Parsed person: " << person.name << ", Start: " << person.start << ", End: " << person.end << ", Wait: " << person.wait << "\n" <<endl; // Test line
    return person;
}

// Function to read elevator data
void readElevators(const string& inputFile){
    fstream input(inputFile);
    string line;

    while(getline(input, line)){
        Elevator elevator = cleanBldgElevator(line);
        elevatorMtx.lock();
        elevatorBuffer.push(elevator);
        elevatorMtx.unlock();
        // cout << "Processed elevator: " << elevator.id << ", Lowest Floor: " << elevator.lowestFloor << ", Highest Floor: " << elevator.highestFloor << ", Current Floor: " << elevator.currentFloor << ", Total Capacity: " << elevator.totalCapacity << endl; // Test line
    }
}

// Function to get elevator status
void elevatorStatusCheck(Elevator elevator){
    // Read and process elevator data
    string elevatorDataString = send_get("ElevatorStatus/" + elevator.id);
    if(elevatorDataString == "Simulation is not running."){
        return;
    }
    // cout << "Received elevator data: " << elevatorDataString << endl; // Test line
    // Cleaning the status data when it is retrieved 
    elevator = cleanElevatorStatus(elevatorDataString);
    elevatorMtx.lock();
    elevatorBuffer.push(elevator); // adding elevator to the buffer
    elevatorMtx.unlock();
}

// Constantly checking elevator status
void elevatorLoop(const string& buildingInput){
    // Read in building information
    readElevators(buildingInput);

    // While there are elevators in the buffer, get status
    while(!elevatorBuffer.empty()){
        elevatorMtx.lock();
        Elevator elevator = elevatorBuffer.front();
        elevatorBuffer.pop();
        elevatorMtx.unlock();
        elevatorStatusCheck(elevator);
    }
}

// Reader thread function
void readerThread() {
    while (true) {
        // Read and process people data
        string peopleDataString = send_get("NextInput");
        if (peopleDataString == "NONE") {
            // No more people data, wait for a short period
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        // Breaks when simulation is not running
        else if (peopleDataString == "Simulation is not running."){
            break;
        }
        // cout << "Received people data: " << peopleDataString << endl; // Test line
        Person p = cleanPerson(peopleDataString);

        peopleMtx.lock();
        peopleBuffer.push(p);
        peopleMtx.unlock();
    }
}

