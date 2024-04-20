#include <iostream>
#include <queue>

using namespace std;

mutex peopleMtx;
mutex elevatorMtx;

// Struct to represent a person
struct Person {
    string name;
    int start;
    int end;
    // int arrival;
    int wait;
};

// Buffer for people
queue<Person> peopleBuffer;

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
queue<Elevator> elevatorBuffer;