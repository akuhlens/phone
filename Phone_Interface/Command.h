#ifndef Command_H
#define Command_H
#include "mbed.h"
#include "SeeedStudioTFTv2/SeeedStudioTFTv2.h"
// the serial port for printf in debuging

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

typedef enum{HALTED, RUNNING} run_state;
typedef enum{OK, UNDEFINED_ERROR} error_status;

void fixpoint_orientation(point& p);

class UserInterface;

class Command {
    public:
      void sendInput(const char *c);
      //void deleteInput(int n);
      //void sendState(State s, char v);
      error_status run();
      Command();
      static Serial pc;
      int currentUI;
    private:
      static SeeedStudioTFTv2 screen;
      UserInterface* ui[2];
      run_state isRunning;
};

// There is a cyclic dependancy here hence the forward declaration
#include "UserInterface.h"

#endif
