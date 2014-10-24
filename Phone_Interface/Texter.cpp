#include "Texter.h"
#include "Display.h"

Texter::Texter(Command *command, SeeedStudioTFTv2 *display): UserInterface(13 ,14, 1, display){
    NumButton *cb0 = new NumButton( 80, 270, 80, 50, "0", command, display);
    NumButton *cb1 = new NumButton(  0, 120, 80, 50, "1", command, display);
    NumButton *cb2 = new NumButton( 80, 120, 80, 50, "2", command, display);
    NumButton *cb3 = new NumButton(160, 120, 80, 50, "3", command, display);
    NumButton *cb4 = new NumButton(  0, 170, 80, 50, "4", command, display);
    NumButton *cb5 = new NumButton( 80, 170, 80, 50, "5", command, display);
    NumButton *cb6 = new NumButton(160, 170, 80, 50, "6", command, display);
    NumButton *cb7 = new NumButton(  0, 220, 80, 50, "7", command, display);
    NumButton *cb8 = new NumButton( 80, 220, 80, 50, "8", command, display);
    NumButton *cb9 = new NumButton(160, 220, 80, 50, "9", command, display);

    Display *disp = new Display(0,0,240,80,command,display);

    Action *backspace = new Backspace(command);
    ActionButton *backspaceButton = new ActionButton(160, 270, 80, 50, backspace, "Back", command, display);

    Action *switchTyper = new WriteText(command, &(disp->contentIndex),disp->content);
    ActionButton *typer = new ActionButton(0, 80, 240, 40, switchTyper, "Text", command, display);

    Action *switchMenu = new SwitchScreen(command, MENU);
    ActionButton *back   = new ActionButton(0, 270, 80, 50, switchMenu, "Menu", command, display);

    //ModeButton *enter = new modeButton(50, 50, 50, 50, "Enter", command, display);
        
    
    
    //this->disp = disp;
    
    drawable[0] = cb0;
    drawable[1] = cb1;
    drawable[2] = cb2;
    drawable[3] = cb3;
    drawable[4] = cb4;
    drawable[5] = cb5;
    drawable[6] = cb6;
    drawable[7] = cb7;
    drawable[8] = cb8;
    drawable[9] = cb9;
    drawable[10] = disp;
    drawable[11] = typer;
    drawable[12] = back;
    drawable[13] = backspaceButton;
    
    touchable[0] = cb0;
    touchable[1] = cb1;
    touchable[2] = cb2;
    touchable[3] = cb3;
    touchable[4] = cb4;
    touchable[5] = cb5;
    touchable[6] = cb6;
    touchable[7] = cb7;
    touchable[8] = cb8;
    touchable[9] = cb9;
    touchable[10] = typer;
    touchable[11] = back;
    touchable[12] = backspaceButton;
    
    writeable[0] = disp;
}
