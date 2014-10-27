#include "Command.h" // implicitly "mbed.h", "SeeedStudioTFTv2.h"
#include "Arial12x12.h"
#include "Dialer.h"
#include "Menu.h"
#include "Texter.h"
#include "Typer.h"
#include "HasCall.h"
#include "InCall.h"
#include "ViewTexts.h"

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
    ui[MENU]    = new Menu(this, &screen);
    ui[DIALER]  = new Dialer(this, &screen);
    ui[TEXTER]  = new Texter(this, &screen);
    ui[TYPER]   = new Typer(this, &screen);
    ui[HAS_CALL]= new HasCall(this, &screen);
    ui[IN_CALL] = new InCall(this, &screen);
    ui[VIEW_TEXT] = new ViewTexts(this, &screen);  
  // Calibrate the screen
    screen.calibrate();
    //1.3 set the isRunning state to RUNNING
    isRunning = RUNNING;
    
    
    // 1.4 Get a cellular connection
    cell = new GPRS(D10, D2, 9600, "18123455508");
    
    if(cell->powerCheck() != 0){
      DigitalOut cell_power(CELL_POWER_TOGGLE_PIN);
      cell_power = 0;
      wait(1);
      cell_power = 1;
      wait(1);
      cell_power = 0;
    }
    
    if(cell->init() != 0){
      pc.puts("\n\rSomething is funny with the modem\n\r");
    }
    
    
}

void Command::sendInput(const char *c){
  ui[currentUI]->sendInput(c);
}

void fixpoint_orientation(point& p){
    int x = (p.y * 3) / 4;  
    p.y = (p.x * 4) / 3;
    p.x = x;    
}

error_status Command::run(){
    // A buffer that will never go away;
    char buffer[100];
    static const int bufferLen = sizeof(buffer);
    memset(buffer, 0 , bufferLen);


    Timer timeCnt;

    point p; //= (point*) malloc(sizof(point));
    p.x = 0;
    p.y = 0;

    
    int i;
    //char *s = NULL;
    

    ui[currentUI]->draw();

    while(cell->gprsSerial.readable()) {
        char c = cell->gprsSerial.getc();
    }
    wait(0.5);
  
    //START:
  
    memset(buffer, 0 , bufferLen);
    i = 0;
    while(1) {

        if (screen.getPixel(p) ){
            // The points are inverted and incorrectly scaled by this factor
            fixpoint_orientation(p);
            pc.printf("%d %d\n\r",p.x,p.y);
            ui[currentUI]->touch(p);
        
        }else if(cell->gprsSerial.readable()) {
            timeCnt.start();  // start timer
            while(1) {
                while (cell->gprsSerial.readable()) {
                    char c = cell->gprsSerial.getc();
                    
                    if (c == '\r' || c == '\n'){
                       c = '$';
                    }
                    
                    buffer[i] = c;
                    i++;
                    
                    if(i > 100) {
                        i = 0;
                        break;
                    }
                }
                if(timeCnt.read() > 2) {          // time out
                    timeCnt.stop();
                    timeCnt.reset();
                    break;
                }
            }


            if(NULL != strstr(buffer,"RING")) {
                currentUI = HAS_CALL;
                ui[currentUI]->draw();
            }

            memset(buffer, 0 , bufferLen);
            i = 0;
        }
    }
    /*
     else if(NULL != (s = strstr(gprsBuffer,"+CMT"))) { //SMS: $$+CMTI: "SM",24$$
        if(NULL != (s = strstr(gprsBuffer,"+32"))) {
            s += 6;
            int i = 0;
            cleanBuffer(messageBuffer,SMS_MAX_LENGTH);
            while((*s != '$')&&(i < SMS_MAX_LENGTH-1)) {
                messageBuffer[i++] = *(s++);
            }
            messageBuffer[i] = '\0';
            return MESSAGE_SMS;
        } else {
            goto START;
        }
    } else {
        goto START;
    }*/

    return NO_ERROR;
}

void Action::envoke(){}

void Backspace::envoke(){
    const char c = '\b';
    cmd->sendInput(&c);
}

void SwitchScreen::envoke(){
    //const char c = 13;
    //cmd->sendInput(&c);
    cmd->currentUI = scrn;
    cmd->ui[scrn]->draw();
}

void MakeCall::envoke(){
    // Here's where we answer the call
    cmd->pc.printf("%d\n",*count);
    cmd->pc.printf("%s\n",buffer);
    if(*count == 11){
        // char number[11];
        // for(int i=0;i<11;++i)
        //     number[i] = buffer[i];
        cmd->cell->callUp(buffer);

        const char c = 13;
        cmd->sendInput(&c);
        cmd->currentUI = IN_CALL;
        cmd->ui[IN_CALL]->draw();
    }
    
}

void WriteText::envoke(){
    cmd->pc.printf("%s\n", buffer);
    if(*length == 11){
        for(int i=0;i<11;++i)
            cmd->curNumber[i] = buffer[i];
        cmd->curNumber[11] = '\0';
        const char c = 13;
        cmd->sendInput(&c);
        cmd->currentUI = TYPER;
        cmd->ui[TYPER]->draw();    
    }
}

void SendText::envoke(){
    cmd->pc.printf("number: %s message: %s\n",cmd->curNumber, message);
    cmd->cell->sendSMS(cmd->curNumber, message);

    const char c = 13;
    cmd->sendInput(&c);
    cmd->currentUI = MENU;
    cmd->ui[MENU]->draw();
}

void AnswerHasCall::envoke(){
    // Here's where we answer the call
    cmd->cell->answer();

    const char c = 13;
    cmd->sendInput(&c);
    cmd->currentUI = IN_CALL;
    cmd->ui[IN_CALL]->draw();
}

void HangupCall::envoke(){
    // Here's where we hangup the call
    cmd->cell->gprsSerial.puts("ATH\r\n");
    cmd->currentUI = MENU;
    cmd->ui[cmd->currentUI]->draw();
}


void NextText::envoke(){
    _command->pc.printf("state == %d\n\r",*_state);
    _command->cell->readSMS(_buffer, 6); 
    _command->pc.printf("%s\n\r", _buffer);
    // *_state += 1;
    _command->ui[_command->currentUI]->draw();
}

void PrevText::envoke(){
    //int prevState = _state;
    // if(! _command->cell->readSMS(_buffer, (*_state) - 1)){
    //   *_state -= 1;
    // }
    // _command->ui[_command->currentUI]->draw();
}

