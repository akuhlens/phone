#include <gpsr.h>
#include <readline.h>


GPSR::GPSR() : Serial(D10, D2), cell_power(D9){
    this->turnOnPower();
}

void GPSR::turnOnPower(){
    if(sendCmdWait("AT\n\r", 1) == OK) return;
    cell_power = 0;
    wait(1);
    cell_power = 1;
    wait(1);
    cell_power = 0;
}

cell_status GPSR::call(char *num){
    char str[22];
    sprintf(str, "ATD + + %s;\r\n", num);
    return sendCmdWait(str, 1);
} 

cell_status GPSR::text(char *num, char *text){
    this->printf("AT+CMGS=\"%s\"\r\n", num);
    char c = ' ';
    while(c!='>'){
        c = this->getc();
    }
    this->puts(text);
    this->putc((char)0x1a);
    return getResponse(this->buffer, sizeof(buffer), 1);
}

cell_status GPSR::getText(int index, char *number, char *text){
    getResponse(buffer, 100, 1);
    this->printf("AT+CMGR=%d\r\n",index);
    getResponse(buffer, 256, 1);
    if(buffer[14] == 'O'&& buffer[15] == 'K') return NO_TEXT;
    
    for(int i=0;i<11;i++)
        number[i] = buffer[i+33];
    number[11] = 0;
        
    int i = 0;
    while(buffer[i+80]){
        text[i] = buffer[i+73];
        i++;
    }
    text[i-1] = 0;
    
    return OK;
}

cell_status GPSR::readRTC(char *time){
    if(sendCmdWait("AT+CCLK?\r\n", 1) == OK){
        for(int i=0;i<20;i++)
            time[i] = buffer[i+20];
        time[20] = 0;
        return OK;
    }
    return ERR;
}

cell_status GPSR::sendCmdWait(const char *cmd, int timeout){
    this->puts(cmd);
    return getResponse(this->buffer, sizeof(buffer), timeout);
}

cell_status GPSR::getResponse(char *buffer, int size, int timeout){
    Timer timer;
    timer.start();
    int i = 0;
    while(timer.read() < timeout){
        if(this->readable()){
            while(this->readable() && i < size){
                buffer[i++] = this->getc();
            }
        }
    }
    if(i){
        i = (i < size)? i : (size - 1);
        buffer[i] = 0;
        return OK; // parseStatus(buffer, size)
    }
    timer.stop();
    return TIME_OUT;
}

void GPSR::clean(int range){
    int i = range;
    while(i){
         if(this->readable()){
            this->getc();
            --i;
        }
    }
}


int GPSR::polling(char *response){
    if(this->readable()){

        readline(this, response, 200);
        /*
        while(this->readable()){
            response[i++] = this->getc();
        }
        response[i+1] = 0;
        */
        return 1;
    }else{
        return 0;
    }
}

cell_status GPSR::parse(char *buff){
  buff[4] = 0;
  if(strcmp(buff,"RING") == 0)return RING;
  //if(sscanf(buff, "+CMTI: \"SM\",%d ",&x)) return TEXT;
  //if(sscanf(buff,"OK "))return OK;
  return UNKNOWN;
}

