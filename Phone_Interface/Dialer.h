#ifndef Dialer_h
#define Dialer_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"
#include "Button.h"

class Dialer : public UserInterface{  
    public:
    Dialer(Command *command, SeeedStudioTFTv2 *display);
};

#endif
