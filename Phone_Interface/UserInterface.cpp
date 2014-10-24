#include "mbed.h"
#include "UserInterface.h"
//#include "Display.h"

UserInterface::UserInterface(int ts, int ds, int ws, SeeedStudioTFTv2 *d) : 
    numberTouchable(ts), numberDrawable(ds), numberWritable(ws), screen(d){
    touchable = (Touchable**) malloc(ts * sizeof(Touchable));
    drawable =  (Drawable**) malloc(ds * sizeof(Drawable));
    writeable = (Writeable**) malloc(ws * sizeof(Writeable));
}

void UserInterface::touch(point& p){
   for(int i = 0; i < numberTouchable; i++){
     touchable[i]->touch(p);    
   }
}

void UserInterface::draw(){
  
  screen->cls();
  screen->fill(0,0,240,340, 0xFFFF);
  
  for(int i = 0; i < numberDrawable; i++){
     drawable[i]->draw();    
   }
}

void UserInterface::sendInput(const char *c){
    for(int i = 0; i < numberWritable; i++){
        writeable[i]->sendInput(c);
    }
}

//void UserInterface::deleteInput(int n){
//    for(int i = 0; i < numberWritable; i++){
//        writeable[i]->deleteInput(n);
//    }
//}

// if the compiler give warnings about abstract classes for Drawable and Touchable
// the these no ops might be of help for getting the compiler to work.
//void Drawable::draw(){}
//void Touchable::touch(int x, int y){}
