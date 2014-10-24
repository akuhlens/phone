#ifndef Display_h
#define Display_h
#include "mbed.h"
#include "UserInterface.h"
#include "SeeedStudioTFTv2.h"
#include "Command.h"

class Display: public Drawable, public Writeable{
    private:
      Command          *controller; 
      SeeedStudioTFTv2 *display; 
      int x, y, width, height, bordorWidth,contentIndex, bgColor, fgColor;
      char* content;

    public:
      virtual void sendInput(const char *c);
      // virtual void clear();
      virtual void draw();
      Display(int x, int y, int width, int height, Command *ctl, SeeedStudioTFTv2 *display);
};
#endif
