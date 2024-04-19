#include <iostream>
#include <thread>
#include "reader.cpp"

using namespace std;

int main(int argc, char* argv[]){
    cout << "\n\nStarting Simulation" << "\n";
    send_put("Simulation/start");
    chrono::milliseconds(100);
    cout << "\n";

    string buildingInput = argv[1];
    vector<Elevator> elevators = readElevators(buildingInput);
    vector<thread> readerThreads;

    

    thread peopleReader(readerThread);
    peopleReader.join();

    // for(Elevator& elevator : elevators){
    //     readerThreads.emplace_back(readerThread);
    // }

    // // Wait for all reader threads to finish
    // for(auto& thread : readerThreads){
    //     thread.join();
    // }

    send_put("Simulation/stop");
    cout << "\n";
    return 0;
}

/*
    cout << "\n\nNext Input:\n" << send_get("NextInput") << "\n";

    cout << "\n\nAdding Eric_R to elevator A" << "\n";
    send_put("AddPersonToElevator/Eric_R/A");

    cout << "\n\nElevator A status:\n"<< send_get("ElevatorStatus/A") << "\n";
*/