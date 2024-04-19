#include <iostream>
#include <thread>
#include "reader.cpp"

using namespace std;

int main(int argc, char* argv[]){
    cout << "\n\nStarting Simulation" << "\n";
    send_put("Simulation/start");
    chrono::milliseconds(100);
    cout << "\n";

    // void(argc);
    string buildingInput = argv[1];

    // New below here
    vector<Elevator> elevators = readElevators(buildingInput);
    for(Elevator elevator : elevators){
        thread reader(readerThread, elevator);
        // thread scheduler(schedulerThread);
        // thread output(outputThread);

        reader.join();
        // scheduler.join();
        // output.join();
    }

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