#include "Display.h"
#include "Arial12x12.h"

Display::Display(int x, int y, int width, int height, Command *ctl, SeeedStudioTFTv2 *display){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->content = (char*) malloc(256 * sizeof(char));
    this->contentIndex = 0;
    this->controller = ctl;
    this->display = display;
    this->bgColor = DarkGrey;
    this->fgColor = GreenYellow;
    this->bordorWidth = 0;

    for(int i=0;i<256;++i)
        content[i] = 0;

}
      
void Display::draw(){
    // for(int i=0;i<bordorWidth;++i)
        // display->rect(x+i,y+i,x+width-i,y+height-i,fgColor);
    
    display->locate(x,y);
    display->background(bgColor);
    display->foreground(fgColor);
    display->fillrect(x,y,x+width,y+height,bgColor);
    display->set_font((unsigned char*) Arial12x12);
    display->printf("%s\n",content);
    //display->character(x+(width/2)-6,y+(height/2)-6,);
}
void Display::sendInput(const char *c){
    if(*c == '\b'){
        content[--contentIndex] = '\0';
    }else if(*c == 13){
        content[0] = '\0';
        contentIndex = 0;
    }else{
        content[contentIndex++] = *c;
        content[contentIndex] = '\0';
    }
    
    draw();
}

