#include "Command.h" // implicitly "mbed.h", "SeeedStudioTFTv2.h"
#include "Arial12x12.h"
#include "Dialer.h"
#include "Menu.h"


Serial Command::pc(USBTX, USBRX);
SeeedStudioTFTv2 Command::screen(PIN_XP, PIN_XM, PIN_YP, PIN_YM, PIN_MOSI, PIN_MISO, PIN_SCLK, PIN_CS_TFT, PIN_DC_TFT, PIN_BL_TFT, PIN_CS_SD);
//CharButton b(50, 50, 80, 60, "1", 'a', (Command*)0, &Command::screen);


Command::Command(){
    //1 initialize screen settings
    //1.1 Configure the background
    screen.background(Black);
    screen.foreground(White);
    screen.cls();
    
    
    //1.2 display splash screen 
    screen.set_font((unsigned char*) Arial12x12);
    int x, y;
    for(x = 0; x < X_MAX; x = x + 50){
      for(y = 0; y < Y_MAX; y = y + 15){
        screen.locate(x,y);
        screen.printf("J & A");
      }
    }
    
    //1.3.0 The various UserInterfaces are stored in an array
    // The starting Ui is the menu
    currentUI = 0;
    //1.3.1 Create the various screens 
    ui[0]= new Menu(this, &screen);
    ui[1]= new Dialer(this, &screen);
    
    // Calibrate the screen
    screen.calibrate();
    //1.3 set the isRunning state to RUNNING
    isRunning = RUNNING;
    
    //inititialize all of the components
    
    
}

void Command::sendInput(const char *c){
  ui[currentUI]->sendInput(c);
}

//void Command::deleteInput(int n){
//    ui[currentUI]->deleteInput(n);
//}

void fixpoint_orientation(point& p){
    int x = (p.y * 3) / 4;  
    p.y = (p.x * 4) / 3;
    p.x = x;    
}

error_status Command::run(){
   point p; //= (point*) malloc(sizof(point));
   p.x = 0;
   p.y = 0;
   
   ui[currentUI]->draw();
   
   while(isRunning){
        if (screen.getPixel(p) ){
            // The points are inverted and incorrectly scaled by this factor
            fixpoint_orientation(p);
            pc.printf("%d %d\n\r",p.x,p.y);
            ui[currentUI]->touch(p);
        }
    }
    return OK;
}



void Command::sendCommand(commands c){
    switch(c){
    case GOTO_MENU:{
        
    }break;
    case GOTO_DIALER:{
        currentUI = DIALER;
        ui[DIALER]->draw();
    }break;
    case GOTO_TEXTER:

        break;

    case GOTO_TYPER:

        break;

    case GOTO_VIEW_TEXT:

        break;

    case HANGUP_GOTO_MENU:

        break;

    case ANSWER_GOTO_IN_CALL:

        break;
    
    default:
        break;
    }
}

void Action::envoke(){}

void SwitchScreen:: envoke(){
    cmd->currentUI = scrn;
    cmd->ui[scrn]->draw();
}
