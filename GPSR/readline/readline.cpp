#include <readline.h>

int readline(Serial *pc, char* line, int len){
    int index = 0;

    while (true){
        char character = pc->getc();
        if(index >= len){
            //pc->printf("\n\r");
            return index;
        }
        switch(character){
            case '\n':
                pc->puts("\n\r");
                line[index] = '\0';
                return index;
            case '\r':
                pc->puts("\n\r");
                line[index] = '\0';
                return index;
            case 127:
                if (index > 0){
                pc->puts("\b \b");
                index -= 1;
                }
                break;
            default:
                if (character > 31 && character < 126){
                    pc->putc(character);
                    line[index] = character;
                    index += 1;
                }
                break;
        }
    }
}