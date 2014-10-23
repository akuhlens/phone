#include "Dialer.h"
#include "Display.h"

Dialer::Dialer(Command *command, SeeedStudioTFTv2 *display): UserInterface(10 ,11, 1){
    CharButton *cb0 = new CharButton( 80, 270, 80, 50, "0", '0',"yz#", command, display);
    CharButton *cb1 = new CharButton(  0, 100, 80, 50, "1", '0',"", command, display);
    CharButton *cb2 = new CharButton( 80, 100, 80, 50, "2", '0',"abc", command, display);
    CharButton *cb3 = new CharButton(160, 100, 80, 50, "3", '0',"def", command, display);
    CharButton *cb4 = new CharButton(  0, 160, 80, 50, "4", '0',"ghi", command, display);
    CharButton *cb5 = new CharButton( 80, 160, 80, 50, "5", '0',"jkl", command, display);
    CharButton *cb6 = new CharButton(160, 160, 80, 50, "6", '0',"mno", command, display);
    CharButton *cb7 = new CharButton(  0, 220, 80, 50, "7", '0',"pqr", command, display);
    CharButton *cb8 = new CharButton( 80, 220, 80, 50, "8", '0',"stu", command, display);
    CharButton *cb9 = new CharButton(160, 220, 80, 50, "9", '0',"vwx", command, display);
    //ModeButton *enter = new modeButton(50, 50, 50, 50, "Enter", command, display);
        
    Display *disp = new Display(0,0,240,60,command,display);
    
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

    
    writeable[0] = disp;
}
