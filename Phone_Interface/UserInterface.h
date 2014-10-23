#ifndef UserInterface_h
#define UserInterface_h
#include "SeeedStudioTFTv2.h"

class Touchable{
    public:
    virtual void touch(point& p) = 0;    
};

class Drawable{
    public:
    virtual void draw() = 0;    
};

class Writeable{
    public:
    virtual void sendInput(const char *c) =0;
    //virtual void deleteInput(int n) =0;
};

class UserInterface : public Touchable, public Drawable, public Writeable {
    public:
      //Display *disp;
      virtual void draw();
      virtual void touch(point& p);
      virtual void sendInput(const char *c);
      UserInterface::UserInterface(int ts, int ds, int ws, SeeedStudioTFTv2 *d);

      SeeedStudioTFTv2 *screen;
      int        numberTouchable;
      Touchable **touchable;
      int        numberDrawable;
      Drawable  **drawable;
      int        numberWritable;
      Writeable  **writeable;
};

#endif
