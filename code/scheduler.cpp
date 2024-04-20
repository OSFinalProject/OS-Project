/*
=============================================================================
Title : scheduler.cpp
Description : This file contains the scheduler thread
Author :Carson Spaniel (R#11712895), Travis Rose (R#11736997)
Date : 04/20/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/
void testPeople(){
    while(true){
        if(!peopleBuffer.empty()){
            peopleMtx.lock();
            Person nextPerson = peopleBuffer.front();
            peopleBuffer.erase(peopleBuffer.begin());
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
            elevatorBuffer.erase(elevatorBuffer.begin());
            elevatorMtx.unlock();
            cout << nextElevator.id << "\n";
        }
    }
}

// void getElevatorInfo(){
//     elevatorMtx.lock();
//     vector<Elevator> tempElevators;
//     while(!elevatorBuffer.empty()){

//     }
// }