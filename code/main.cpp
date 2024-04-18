#include <iostream>
#include "api.cpp"

using namespace std;

int main(){

    cout << "\n\nStarting Simulation" << "\n";
    send_put("Simulation/start");

    cout << "\n\nNext Input:\n" << send_get("NextInput") << "\n";

    cout << "\n\nAdding Eric_R to elevator A" << "\n";
    send_put("AddPersonToElevator/Eric_R/A");

    cout << "\n\nElevator A status:\n"<< send_get("ElevatorStatus/A") << "\n";
    
    return 0;
}