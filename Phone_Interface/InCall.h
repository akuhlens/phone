#ifndef InCall_h
#define InCall_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"



class InCall : public UserInterface{  
    public:
    InCall(Command *command, SeeedStudioTFTv2 *display);
};

#endif
