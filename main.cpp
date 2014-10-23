#include "mbed.h"
#include "Command.h"

int main(){
    // The Command Class is a state machine that controls the global
    // behavior of the device.
    
    // initialize everything
    Command *controller = new Command();
    // start the state machine
    int status = controller->run();
    return status;
}   