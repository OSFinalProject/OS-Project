/*
===========================================================================================
Title : output.cpp
Description : This file outputs the results from scheduler.cpp
Author : Travis Rose (R#11736997), Kaitlyn Urano (R#11555972), Carson Spaniel (R#11712895)
Date : 04/20/2024
Version : 1.0
Usage : Compile and run this program using the GNU C++ compiler
Notes : Run chmod +x * in order to apply permissions.
C++ Version : Version 11
============================================================================================
*/
void outputLoop(){
    while(true){
        if(outputBuffer.empty()){
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }
        outputMtx.lock();
        string out = outputBuffer.front();
        outputBuffer.pop();
        if (out != ""){
            send_put(out);
        }
        outputMtx.unlock();
    }
}