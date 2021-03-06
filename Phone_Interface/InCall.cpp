#include "InCall.h"
#include "Button.h"

InCall::InCall(Command *command, SeeedStudioTFTv2 *display): UserInterface(1 , 1, 0, display){
    Action *hangUp = new HangupCall(command);
    ActionButton *hangUpButton   = new ActionButton(0,  0, 240, 80, hangUp, "Hangup", command, display);
  
    //Register them as both drawlable and touchable
    drawable[0] = hangUpButton;
    touchable[0] = hangUpButton;
}
