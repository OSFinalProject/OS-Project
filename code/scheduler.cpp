/*
============================================================================================
Title : scheduler.cpp
Description : This file contains the scheduler thread
Author : Carson Spaniel (R#11712895), Travis Rose (R#11736997), Kaitlyn Urano (R#11555972),
    Isha Koregave (R#11743130)
Date : 04/20/2024
Version : 3.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
===========================================================================================
*/
// Function to get the next elevator RR
Elevator getNextElevator(Person person){
    Elevator nextElevator;
    while(true){
        elevatorMtx.lock();
        nextElevator = elevatorBuffer.front();
        elevatorBuffer.erase(elevatorBuffer.begin());
        elevatorBuffer.push_back(nextElevator);
        elevatorMtx.unlock();
        // If going up, make sure the elevator they get assigned to can travel to that floor. Same thing going down but make sure elevator can pick them up
        if ((person.distance > 0 && person.end <= nextElevator.highestFloor) || (person.distance < 0 && person.start <= nextElevator.highestFloor)){
            break;
        }
    }
    return nextElevator;
}

// Function to get the next person using SPN
Person getNextPerson(){
    // Find the shortest process
    auto compare = [&](const auto &a, const auto &b) {
        return (abs(a.distance) < abs(b.distance));
    };
    peopleMtx.lock();
    // Sort by shortest process
    sort(peopleBuffer.begin(), peopleBuffer.end(), compare);
    Person nextPerson = peopleBuffer.front();
    peopleBuffer.erase(peopleBuffer.begin());
    peopleMtx.unlock();
    return nextPerson;
}

// Function to sort people
void schedulerLoop(){
    while(!done){
        if(peopleBuffer.empty() || elevatorBuffer.empty()){
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        else{
            Person person = getNextPerson();
            Elevator elevator = getNextElevator(person);
            
            outputMtx.lock();
            outputBuffer.push("/AddPersonToElevator/"+person.name+"/"+elevator.id);
            outputMtx.unlock();
        }
    }
}
