#ifndef Menu_h
#define Menu_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"



class Menu : public UserInterface{  
    public:
    Menu(Command *command, SeeedStudioTFTv2 *display);
};

#endif
