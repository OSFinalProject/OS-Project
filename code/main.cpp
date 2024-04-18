#include <iostream>
#include <api.cpp>

using namespace std;

int main(){
    cout << "Hello Carson!" << "\n";
    cout << "Hello Isha!" << "\n";
    cout << "Hello Kaitlyn!" << "\n";

    send_put("Simulation/start",0)
    return 0;
}