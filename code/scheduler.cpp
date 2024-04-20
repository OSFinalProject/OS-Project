#include <iostream>
// #include "struct.cpp"

using namespace std;

void testPeople(){
    while(true){
        if(!peopleBuffer.empty()){
            peopleMtx.lock();
            Person nextPerson = peopleBuffer.front();
            peopleBuffer.pop();
            peopleMtx.unlock();
            cout << nextPerson.name << "\n";
        }
    }
}

void testElevator(){
    while(true){
        if(!elevatorBuffer.empty()){
            elevatorMtx.lock();
            Elevator nextElevator = elevatorBuffer.front();
            elevatorBuffer.pop();
            elevatorMtx.unlock();
            cout << nextElevator.id << "\n";
        }
    }
}

void getElevatorInfo(){
    elevatorMtx.lock();
    queue<Elevator> tempElevators;
    while(!elevatorBuffer.empty())
}