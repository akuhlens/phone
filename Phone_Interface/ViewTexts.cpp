#include "ViewTexts.h"
#include "Display.h"

ViewTexts::ViewTexts(Command *command, SeeedStudioTFTv2 *display): UserInterface(3 ,4, 1, display){

    static index = 0;

    Display *disp = new Display(0,0,240,240,command,display);

    Action *backspace = new Backspace(command);
    ActionButton *backspaceButton = new ActionButton(0, 240, 80, 80, backspace, "Back", command, display);

    Action *previousText = new PrevText(command, &index, disp);
    ActionButton *pText = new ActionButton(80, 240, 80, 80, previousText, "Previous", command, display);

    Action *nextText = new NextText(command, &index, disp);
    ActionButton *nText   = new ActionButton(160, 240, 80, 80, nextText, "Next", command, display);

    drawable[0] = disp;
    drawable[1] = typer;
    drawable[2] = back;
    drawable[3] = backspaceButton;
    
    touchable[0] = typer;
    touchable[1] = back;
    touchable[2] = backspaceButton;
    
    writeable[0] = disp;
}
