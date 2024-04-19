/*
=============================================================================
Title : reader.cpp
Description : This file cleans the input returned from the API and reads it
Author : Kaitlyn Urano (R#11555972), Carson Spaniel (R#11712895)
Date : 04/18/2024
Version : 1.2
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <fstream>
#include <mutex>
#include <queue>
#include "api.cpp"

using namespace std;
mutex mtx;
queue<BufferEntry> buffer;


// Struct to represent a person
struct Person {
    string name;
    int start;
    int end;
    int wait;
};

// Struct to represent an elevator
struct Elevator {
    string id;
    int currentFloor;
    string direction;
    int passengerCount;
    int remainingCapacity;
};

// Reader thread function
void readerThread(Elevator elevator) {
    vector<Person> people;

    while (true) {
        // mtx.lock();

        // Read and process people data
        string peopleDataString = send_get("NextInput");
        if (peopleDataString == "NONE") {
            // mtx.unlock();
            // No more people data, wait for a short period
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        else if (peopleDataString == "Simulation is not running."){
            break;
        }
        cout << "Received people data: " << peopleDataString << endl; // Test line
        Person p = cleanPerson(peopleDataString);
        cout << "Parsed person: " << p.name << ", Start: " << p.start << ", End: " << p.end << endl; // Test line
        people.push_back(p);

        // Read and process elevator data
        string elevatorDataString = send_get("ElevatorStatus/" + elevator.id);
        cout << "Received elevator data: " << elevatorDataString << endl; // Test line
    }
}

vector<Elevator> readElevators(const string& inputFile){
    vector<Elevator> elevators;
    fstream input(inputFile);
    string line;

    while(getline(input, line)){
        Elevator elevator = cleanElevator(line);
        elevators.push_back(elevator);
        cout << "Processed elevator: " << elevator.id << ", Floor: " << elevator.currentFloor << ", Direction: " << elevator.direction << ", Passengers: " << elevator.passengerCount << ", Remaining Capacity: " << elevator.remainingCapacity << endl; // Test line
    }
    return elevators;
}

Elevator cleanElevator(string input){
    for(int i=0;i<input.length();i++){
        if(int(input[i]) == 9){
            input[i] = '|';
        }
    }

    cout << input << "\n";
    istringstream iss(input);
    Elevator elevator;

    getline(iss, elevator.id, '|');
    iss >> elevator.currentFloor;
    getline(iss, elevator.direction, '|');
    iss >> elevator.passengerCount;
    iss >> elevator.remainingCapacity;

    return elevator;
}

Person cleanPerson(string input){
    istringstream iss(input);
    Person person;

    getline(iss, person.name, '|');
    iss >> person.start;
    iss >> person.end;
    person.wait = 0;

    return person;
}

// int main(){
//     cleanElevator("A|1|U|2|8");
//     cleanElevator("B\t2\tD\t3\t6");
//     cleanPerson("Eric_R|1|2");
// }