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
// // Function to clear elevator status data from API
// Elevator cleanElevatorStatus(string input)
// {
//     istringstream iss(input);
//     Elevator elevator;

//     getline(iss, elevator.id, '|');
//     iss >> elevator.currentFloor;
//     getline(iss, elevator.direction, '|');
//     iss >> elevator.passengerCount;
//     iss >> elevator.remainingCapacity;

//     return elevator;
// }

// Function to clean .bdlg file data
Elevator cleanBldgElevator(string input)
{
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
Person cleanPerson(string input)
{
    istringstream iss(input);
    Person person;

    getline(iss, person.name, '|');
    iss >> person.start;
    iss.ignore(1);
    iss >> person.end;
    person.distance = person.end - person.start;
    return person;
}

// Function to read elevator data from .bldg file
void readElevators(const string &inputFile)
{
    fstream input(inputFile);
    string line;

    // process while there are lines to read
    while (getline(input, line))
    {
        Elevator elevator = cleanBldgElevator(line);
        elevatorMtx.lock();
        elevatorBuffer.push_back(elevator); // add to buffer
        elevatorMtx.unlock();
    }
}

// // Function to get elevator status from API
// void elevatorStatusCheck(Elevator elevator)
// {
//     // Read and process elevator data
//     string elevatorDataString = send_get("ElevatorStatus/" + elevator.id);
//     if (elevatorDataString == "Simulation is not running.")
//     {
//         return;
//     }
//     // Cleaning the status data when it is retrieved
//     elevator = cleanElevatorStatus(elevatorDataString);
//     elevatorMtx.lock();
//     elevatorBuffer.push_back(elevator); // adding elevator to the buffer
//     elevatorMtx.unlock();
// }

// // Loop to constantly check elevator status
// void elevatorLoop(const string &buildingInput)
// {
//     // Read in building information
//     readElevators(buildingInput);
//     // While there are elevators in the buffer, get status
//     while (!elevatorBuffer.empty())
//     {
//         elevatorMtx.lock();
//         Elevator elevator = elevatorBuffer.front();
//         elevatorBuffer.erase(elevatorBuffer.begin());
//         elevatorMtx.unlock();
//         elevatorStatusCheck(elevator); // get the status
//         this_thread::sleep_for(chrono::milliseconds(500));
//     }
// }

// Reader thread function
void readerThread(const string &buildingInput)
{
    readElevators(buildingInput);
    while (true)
    {
        // Read and process people data
        string peopleDataString = send_get("NextInput");
        if (peopleDataString == "NONE")
        {
            // No more people data, wait for a short period
            this_thread::sleep_for(chrono::milliseconds(500));
            continue;
        }
        // Breaks when simulation is not running
        else if (peopleDataString == "")
        {
            done = true;
            break;
        }
        // Clean the data received
        Person p = cleanPerson(peopleDataString);

        peopleMtx.lock();
        peopleBuffer.push_back(p); // add to buffer
        peopleMtx.unlock();
    }
}
