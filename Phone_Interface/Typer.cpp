#include "Typer.h"
#include "Display.h"

Typer::Typer(Command *command, SeeedStudioTFTv2 *display): UserInterface(13 ,14, 1, display){
    CharButton *cb0 = new CharButton( 80, 270, 80, 50, "0", '0',"yz#", command, display);
    CharButton *cb1 = new CharButton(  0, 120, 80, 50, "1", '0',"", command, display);
    CharButton *cb2 = new CharButton( 80, 120, 80, 50, "2", '0',"abc", command, display);
    CharButton *cb3 = new CharButton(160, 120, 80, 50, "3", '0',"def", command, display);
    CharButton *cb4 = new CharButton(  0, 170, 80, 50, "4", '0',"ghi", command, display);
    CharButton *cb5 = new CharButton( 80, 170, 80, 50, "5", '0',"jkl", command, display);
    CharButton *cb6 = new CharButton(160, 170, 80, 50, "6", '0',"mno", command, display);
    CharButton *cb7 = new CharButton(  0, 220, 80, 50, "7", '0',"pqr", command, display);
    CharButton *cb8 = new CharButton( 80, 220, 80, 50, "8", '0',"stu", command, display);
    CharButton *cb9 = new CharButton(160, 220, 80, 50, "9", '0',"vwx", command, display);

    Display *disp = new Display(0,0,240,80,command,display);

    Action *backspace = new Backspace(command);
    ActionButton *backspaceButton = new ActionButton(160, 270, 80, 50, backspace, "Back", command, display);

    Action *text = new SendText(command, disp->content);
    ActionButton *sendText   = new ActionButton(0,   80, 240, 40, text, "Send", command, display);

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
    drawable[11] = sendText;
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
    touchable[10] = sendText;
    touchable[11] = back;
    touchable[12] = backspaceButton;
    
    writeable[0] = disp;
}
