#include "Menu.h"
#include "Button.h"

Menu::Menu(Command *command, SeeedStudioTFTv2 *display): UserInterface(1 , 1, 0){
    // Initialize the three buttons on the menu screen
    
    Action *dial = new SwitchScreen(command, DIALER);
    ActionButton *dialer   = new ActionButton(0,   0, 240, 80, dial, "Make Call", command, display);
    //ActionButton *texter   = new ActionButton(0,  80, 240, 80, GOTO_TEXTER,    "Send Text", command, display);
    //ActionButton *viewText = new ActionButton(0, 160, 240, 80, GOTO_VIEW_TEXT, "View Text", command, display);
    //Register them as both drawlable and touchable
    drawable[0] = dialer;
    //drawable[1] = texter;
    //drawable[2] = viewText;
    touchable[0] = dialer;
    //touchable[1] = texter;
    //touchable[2] = viewText;
}
