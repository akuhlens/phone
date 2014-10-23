#ifndef Command_H
#define Command_H
#include "mbed.h"
#include "SeeedStudioTFTv2/SeeedStudioTFTv2.h"
#include "UserInterface.h"


// The Configuation for the sceen device
// Touch pins
#define PIN_XP          A3
#define PIN_XM          A1
#define PIN_YP          A2
#define PIN_YM          A0
// Display SPI pins
#define PIN_MOSI        D11
#define PIN_MISO        D12
#define PIN_SCLK        D13
#define PIN_CS_TFT      D5
#define PIN_DC_TFT      D6
#define PIN_BL_TFT      D7
#define PIN_CS_SD       D4
#define X_MAX 240
#define Y_MAX 320

#define MENU 0
#define DIALER 1
#define TEXTER 2
#define TYPER 3
#define VIEW_TEXT 4
#define HAS_CALL 5
#define IN_CALL 6

typedef enum{HALTED, RUNNING} run_state;
typedef enum{OK, UNDEFINED_ERROR} error_status;
typedef enum{GOTO_MENU, GOTO_DIALER, GOTO_TEXTER, GOTO_TYPER, GOTO_VIEW_TEXT, HANGUP_GOTO_MENU, ANSWER_GOTO_IN_CALL} commands;

void fixpoint_orientation(point& p);

class Command {
    public:
      void sendInput(const char *c);
      //void deleteInput(int n);
      //void sendState(State s, char v);
      void sendCommand(commands c);
      error_status run();
      Command();
      static Serial pc;
      int currentUI;
      static SeeedStudioTFTv2 screen;
      UserInterface* ui[2];
      run_state isRunning;
};

class Action{
  public:
    virtual void envoke() = 0;
};

class SwitchScreen : Action{
    Command *cmd;
    int scrn;
  public:
    virtual void envoke();
    SwitchScreen(Command *command, int screen) : cmd(command), scrn(screen){};
};

#endif
