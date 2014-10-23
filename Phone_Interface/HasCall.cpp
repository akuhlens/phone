#include "HasCall.h"
#include "Button.h"

HasCall::HasCall(Command *command, SeeedStudioTFTv2 *display): UserInterface(2 , 2, 0, display){
    // Initialize the three buttons on the menu screen
    
    Action *answer = new AnswerHasCall(command);
    ActionButton *answerScreen   = new ActionButton(0,   0, 240, 80, answer, "Answer", command, display);
    
    Action *hangUp = new HangupCall(command);
    ActionButton *hangUpButton   = new ActionButton(0,  80, 240, 80, hangUp, "Hangup", command, display);
  
    //Register them as both drawlable and touchable
    drawable[0] = answerScreen;
    drawable[1] = hangUpButton;
    touchable[0] = answerScreen;
    touchable[1] = hangUpButton;
}
