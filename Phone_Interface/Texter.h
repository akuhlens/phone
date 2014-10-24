#ifndef Texter_h
#define Texter_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"
#include "Button.h"

class Texter : public UserInterface{  
    public:
    Texter(Command *command, SeeedStudioTFTv2 *display);
};

#endif
