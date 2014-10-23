#ifndef HasCall_h
#define HasCall_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"



class HasCall : public UserInterface{  
    public:
    HasCall(Command *command, SeeedStudioTFTv2 *display);
};

#endif
