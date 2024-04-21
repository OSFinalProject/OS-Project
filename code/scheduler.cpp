/*
============================================================================================
Title : scheduler.cpp
Description : This file contains the scheduler thread
Author : Carson Spaniel (R#11712895), Travis Rose (R#11736997), Kaitlyn Urano (R#11555972)
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
        if ((person.distance > 0 && person.end <= nextElevator.highestFloor) || (person.distance < 0 && person.start <= nextElevator.highestFloor)){
            break;
        }
    }
    return nextElevator;
}

// // Function to get the closest available elevator
// Elevator getNextElevator(Person person){
//     // Find the shortest process
//     auto compare = [&](const auto &a, const auto &b) {
//         // Check if there is capacity 
//         if(a.remainingCapacity > 0 && b.remainingCapacity > 0){
//             // Check if their travel is within range of the two compared elevators
//             if ((person.distance > 0 && person.end <= a.highestFloor && person.end <= b.highestFloor) || (person.distance < 0 && person.start <= a.highestFloor && person.start <= b.highestFloor)){
//                 return (abs(person.start - a.currentFloor) < abs(person.start - b.currentFloor));
//             }
//             // If it is only in range of A
//             else if((person.distance > 0 && person.end <= a.highestFloor) || (person.distance < 0 && person.start <= a.highestFloor))
//             {
//                 return true;
//             }
//         }
//         return false;
//     };
//     sort(elevatorBuffer.begin(), elevatorBuffer.end(), compare);
//     return elevatorBuffer.front();
// }

// Function to get the next person using SPN
Person getNextPerson(){
    // Find the shortest process
    auto compare = [&](const auto &a, const auto &b) {
        return (abs(a.distance) < abs(b.distance));
    };
    peopleMtx.lock();
    sort(peopleBuffer.begin(), peopleBuffer.end(), compare);
    Person nextPerson = peopleBuffer.front();
    peopleBuffer.erase(peopleBuffer.begin());
    peopleMtx.unlock();
    return nextPerson;
}

mutex coutMtx;

// Function to sort people
void schedulerLoop(){
    while(true){
        if(peopleBuffer.empty() || elevatorBuffer.empty()){
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        else{
            Person person = getNextPerson();
            Elevator elevator = getNextElevator(person);

            coutMtx.lock();
            cout << "Adding " << person.name << " to elevator " << elevator.id << "\n";
            coutMtx.unlock();
            
            outputMtx.lock();
            outputBuffer.push("/AddPersonToElevator/"+person.name+"/"+elevator.id);
            outputMtx.unlock();
        }
    }
}
