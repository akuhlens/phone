#include "ViewTexts.h"
#include "Display.h"

ViewTexts::ViewTexts(Command *command, SeeedStudioTFTv2 *display): UserInterface(3 ,4, 1, display){

    static int index = 0;

    Display *disp = new Display(0,0,240,240,command,display);
    
    Action *menuAct = new SwitchScreen(command, MENU);
    ActionButton *menu = new ActionButton(0, 240, 80, 80, menuAct, "Menu", command, display);

    Action *previousText = new PrevText(command, &index, disp->content);
    ActionButton *pText = new ActionButton(80, 240, 80, 80, previousText, "Previous", command, display);

    Action *nextText = new NextText(command, &index, disp->content);
    ActionButton *nText   = new ActionButton(160, 240, 80, 80, nextText, "Next", command, display);

    drawable[0] = disp;
    drawable[1] = pText;
    drawable[2] = nText;
    drawable[3] = menu;
    
    touchable[0] = pText;
    touchable[1] = nText;
    touchable[2] = menu;
    
    writeable[0] = disp;
}
