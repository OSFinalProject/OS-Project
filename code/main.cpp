#include <iostream>
#include <api.cpp>

using namespace std;

int main(){
    cout << "Hello Carson!" << "\n";
    cout << "Hello Isha!" << "\n";
    cout << "Hello Kaitlyn!" << "\n";

    cout << "\n\nStarting Simulation" << "\n";
    send_put("Simulation/start",0);

    cout << "\n\nNext Input" << "\n";
    send_get("NextInput");

    cout << "\n\nAdding Eric_R to elevator A" << "\n";
    send_put("AddPersonToElevator/Eric_R/A",0);

    cout << "\n\nElevator A status" << "\n";
    send_get("ElevatorStatus/A");

    
    return 0;
}