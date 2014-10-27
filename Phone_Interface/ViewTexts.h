#ifndef ViewTexts_h
#define ViewTexts_h
#include "UserInterface.h"
#include "Command.h"
#include "SeeedStudioTFTv2.h"
#include "Button.h"

class ViewTexts : public UserInterface{  
    public:
    ViewTexts(Command *command, SeeedStudioTFTv2 *display);
};

#endif
