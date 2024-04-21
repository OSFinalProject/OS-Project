/*
============================================================================================
Title : scheduler.cpp
Description : This file contains the scheduler thread
Author : Carson Spaniel (R#11712895), Travis Rose (R#11736997), Kaitlyn Urano (R#11555972),
    Isha Koregave (R#11746130)
Date : 04/20/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
===========================================================================================
*/
// Function to get the next elevator
Elevator getElevator()
{
    while (elevatorBuffer.empty())
    {
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

// Function to group candidates together for elevator trips
vector<Person> getGroup(Elevator selectedElevator)
{
    // Vector to store group of candidates with similar trips
    vector<Person> group = {};
    // If there is enough remaining capacity for a group of people
    if (selectedElevator.remainingCapacity > 2)
    {
        // Add selected person to the group
        peopleMtx.lock();
        Person selectedPerson = peopleBuffer.front();
        peopleBuffer.erase(peopleBuffer.begin());
        peopleMtx.unlock();

        group.push_back(selectedPerson);
        int peopleInGroup = 1;

        // Check for all candidates in the peopleBuffer
        int size = peopleBuffer.size();
        for (int i = 0; i < size; i++)
        {
            Person candidate = peopleBuffer[i];
            if (peopleInGroup >= selectedElevator.remainingCapacity)
            {
                break;
            }
            // If candidate is going up and their trip is within range of the selectedPerson going up
            if ((candidate.distance > 0 && selectedPerson.distance > 0) && (candidate.start >= selectedPerson.start && candidate.start <= selectedPerson.end && candidate.end <= selectedPerson.end && candidate.end >= selectedPerson.start))
            {
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
            if ((candidate.distance < 0 && selectedPerson.distance < 0) && (candidate.start <= selectedPerson.start && candidate.start >= selectedPerson.end && candidate.end >= selectedPerson.end && candidate.end <= selectedPerson.start))
            {
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

mutex coutMtx;

// Function to sort people
void schedulerLoop()
{
    while (true)
    {
        if (peopleBuffer.empty())
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        else
        {
            Elevator elevator = getElevator();
            vector<Person> candidates = getGroup(elevator);
            for (Person candidateToSend : candidates)
            {
                coutMtx.lock();
                cout << "Adding " << candidateToSend.name << " to elevator " << elevator.id << "\n";
                coutMtx.unlock();
                outputMtx.lock();
                outputBuffer.push("/AddPersonToElevator/" + candidateToSend.name + "/" + elevator.id);
                outputMtx.unlock();
            }
        }
    }
}
