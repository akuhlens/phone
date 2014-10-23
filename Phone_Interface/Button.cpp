#include "Button.h"
#include "Display.h"
#include "Arial12x12.h"

Button::Button(int x, int y, int width, int height, const char* label, Command *ctl, SeeedStudioTFTv2 *display){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->label = label;
    this->controller = ctl;
    this->display = display;
    this->bgColor = Black;
    this->fgColor = White;
    this->bordorWidth = 6;
}

CharButton::CharButton(int x, int y, int width, int height, const char* label, char value, const char *subValue, Command *ctl, SeeedStudioTFTv2 *disp) : Button(x, y, width, height, label, ctl, disp)
{
    value = value;
    this->subValue = subValue;
    disp->locate(0,0);
}

CommandButton::CommandButton(int x, int y, int width, int height, int command, const char* label, Command *ctl, SeeedStudioTFTv2 *disp) : Button(x, y, width, height, label, ctl, disp)
{
    this->command = command;
    disp->locate(0,0);
}
          
void CharButton::draw(){
    display->fillrect(x, y, x+width,y+height,bgColor);
    display->rect(x+bordorWidth,y+bordorWidth,x+width-bordorWidth,y+height-bordorWidth,fgColor);
    display->locate(x+(width/2)-6,y+(height/2)-6);
    display->background(bgColor);
    display->foreground(fgColor);
    display->set_font((unsigned char*) Arial12x12);
    display->printf("%s\n",label);
    display->locate(x+(width/2)-14,y+(height/2)+6);
    display->printf("%s\n",subValue);
    //display->character(x+(width/2)-6,y+(height/2)-6,);
}

void Button::draw(){
    display->fillrect(x, y, x+width,y+height,bgColor);
    display->rect(x+bordorWidth,y+bordorWidth,x+width-bordorWidth,y+height-bordorWidth,fgColor);
    display->locate(x+(width/2)-6,y+(height/2)-6);
    display->background(bgColor);
    display->foreground(fgColor);
    display->set_font((unsigned char*) Arial12x12);
    display->printf("%s\n",label);
}

void CharButton::touch(point& p){
    if ((x < p.x) && (p.x < (x + width)) &&  y < p.y && p.y < (y + height)){
        
        // invert the colors while the button is held
        int bg = this->bgColor;
        int fg = this->fgColor;
        bgColor = fg;
        fgColor = bg;
        
        this->controller->sendInput(this->label);
        
        draw();
        
        while(display->getPixel(p)); //spin until the key is unpressed
        
        bgColor = bg;
        fgColor = fg;
        draw();
        
        int counter = 0, pos=0;
        while(counter < 5000){
            if(display->getPixel(p)){
                fixpoint_orientation(p);
                controller->pc.printf("%d %d\n\r",p.x,p.y);
                if((x < p.x) && (p.x < (x + width)) &&  y < p.y && p.y < (y + height)){
                    counter = 0;
                    this->controller->sendInput("\b");
                    this->controller->sendInput(this->subValue + pos);
                    pos = (pos+1)%3;
                    while(display->getPixel(p));
                }else{
                    
                    return;
                }
            }
            counter++;
        }

   }
}

void CommandButton::touch(point& p){
    if ((x < p.x) && (p.x < (x + width)) &&  y < p.y && p.y < (y + height)){
        
        // invert the colors while the button is held
        int bg = this->bgColor;
        int fg = this->fgColor;
        bgColor = fg;
        fgColor = bg;
        
        draw();
                
        while(display->getPixel(p)); //spin until the key is unpressed
        bgColor = bg;
        fgColor = fg;
        draw();

   }
}
