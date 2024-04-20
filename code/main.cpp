/*
=============================================================================
Title : main.cpp
Description : Main driver code for the entire OS.
Author : Kaitlyn Urano (R#11555972), Carson Spaniel (R#11712895), Travis Rose (R#11736997)
Date : 04/20/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
=============================================================================
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

#include "api.cpp"
#include "struct.cpp"
#include "reader.cpp"
#include "scheduler.cpp"

int main(int argc, char* argv[]){
    cout << "\n\nStarting Simulation" << "\n";
    send_put("Simulation/start");
    chrono::milliseconds(100);
    cout << "\n";

    string buildingInput = argv[1];

    thread peopleReader(readerThread);
    thread elevatorStatus(elevatorLoop, buildingInput);

    chrono::milliseconds(500);
    thread schedulerThread(testPeople);
    thread schedulerElevatorThread(testElevator);

    peopleReader.join();
    elevatorStatus.join();
    schedulerThread.join();
    schedulerElevatorThread.join();
    

    send_put("Simulation/stop");
    cout << "\n";
    return 0;
}