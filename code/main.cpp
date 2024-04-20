#include <iostream>
#include <thread>
#include "reader.cpp"
#include "scheduler.cpp"

using namespace std;

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