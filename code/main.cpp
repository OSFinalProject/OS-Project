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

using namespace std;

#include "api.cpp"
#include "struct.cpp"
#include "reader.cpp"
#include "scheduler.cpp"
#include "output.cpp"

int main(int argc, char* argv[]){
    //const int catchResult = Catch::Session().run(argc, argv);  // Run Catch2 tests - PART OF UNIT TESTING

    cout << "\n\nStarting Simulation" << "\n";
    send_put("Simulation/start");
    cout << "\n";

    string buildingInput = argv[1];

    thread peopleReader(readerThread);
    thread elevatorStatus(elevatorLoop, buildingInput);
    thread schedulerThread(schedulerLoop);
    thread outputThread(outputLoop);

    peopleReader.join();
    elevatorStatus.join();
    schedulerThread.join();
    outputThread.join();
    

    send_put("Simulation/stop");
    cout << "\n";


    /*PART OF UNIT TESTING

    std::cin.get();
   
    return retval;  //return result of Catch2 unit testing
    */
    return 0;

    
}