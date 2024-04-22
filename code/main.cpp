/*
==========================================================================================
Title : main.cpp
Description : Main driver code for the entire OS.
Author : Kaitlyn Urano (R#11555972), Carson Spaniel (R#11712895), Travis Rose (R#11736997)
Date : 04/20/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
============================================================================================
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool done = false;

#include "api.cpp"
#include "struct.cpp"
#include "reader.cpp"
#include "scheduler.cpp"
#include "output.cpp"


int main(int argc, char* argv[]){
    send_put("Simulation/start");
    cout << "\n";

    // To be able to read building data
    string buildingInput = argv[1];

    // The four threads
    thread peopleReader(readerThread, buildingInput);
    // thread elevatorStatus(elevatorLoop, buildingInput);
    thread schedulerThread(schedulerLoop);
    thread outputThread(outputLoop);

    peopleReader.join();
    // elevatorStatus.join();
    schedulerThread.join();
    outputThread.join();

    return 0;
}