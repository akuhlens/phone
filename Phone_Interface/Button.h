#ifndef Button_h
#define Button_h
#include "mbed.h"
#include "UserInterface.h"
#include "SeeedStudioTFTv2.h"
#include "Command.h"

class Button: public Touchable, public Drawable{
    protected:
    // these two is very hacky and needs removed
      Command          *controller; 
      SeeedStudioTFTv2 *display; 
      int x, y, width, height, bordorWidth, bgColor, fgColor;
      const char* label;

    public:
      virtual void touch(point& p) = 0;
      virtual void draw();
      Button(int x, int y, int width, int height, const char* label, Command *ctl, SeeedStudioTFTv2 *display);
};

class CharButton: public Button {
    private:
     char value;
     const char* subValue;
    public:
     virtual void touch(point& p);
     virtual void draw();
     CharButton(int x, int y, int width, int height, const char* label, char value, const char *subValue, Command *ctl, SeeedStudioTFTv2 *display);
};

class CommandButton: public Button {
    private:
      commands command;
    public:
      virtual void touch(point& p);
      CommandButton(int x, int y, int width, int height, commands cmd, const char* label, Command *ctl, SeeedStudioTFTv2 *display);
};

class ActionButton: public Button {
    private:
      Action act;
    public:
      virtual void touch(point& p);
      ActionButton(int x, int y, int w, int h, Action a, const Char* l, Command *c, SeeedStudioTFTv2 *d):
          act(a), Button(x, y, w, h, l, c, d) {};
};
#endif
