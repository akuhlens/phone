#include "Menu.h"
#include "Button.h"

Menu::Menu(Command *command, SeeedStudioTFTv2 *display): UserInterface(3 , 3, 0){
    // Initialize the three buttons on the menu screen
    CommandButton *dialer   = new CommandButton(0,   0, 240, 80, GOTO_DIALER,    "Make Call", command, display);
    CommandButton *texter   = new CommandButton(0,  80, 240, 80, GOTO_TEXTER,    "Send Text", command, display);
    CommandButton *viewText = new CommandButton(0, 160, 240, 80, GOTO_VIEW_TEXT, "View Text", command, display);
    // Register them as both drawlable and touchable
    drawable[0] = dialer;
    drawable[1] = texter;
    drawable[3] = viewText;
    touchable[0] = dialer;
    touchable[1] = texter;
    touchable[2] = viewText;
}
