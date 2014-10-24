#ifndef Typer_h
#define Typer_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"
#include "Button.h"

class Typer : public UserInterface{  
    public:
    Typer(Command *command, SeeedStudioTFTv2 *display);
};

#endif
