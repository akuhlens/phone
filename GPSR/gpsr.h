#ifndef GPRS_H 
#define GPRS_H
#include <mbed.h>

typedef enum{OK, NO_CRIR, ERR, UNKNOWN, NO_TEXT, TIME_OUT, RING, TEXT} cell_status;

class GPSR : public Serial {
    public:
    GPSR();
    cell_status call(char *num);
    cell_status text(char *num, char *text);
    cell_status getText(int index, char *number, char *text);
    cell_status getResponse(char* buffer, int size_buf, int timeout);
    cell_status sendCmdWait(const char *cmd, int timeout);
    cell_status parseStatus(char *buffer);
    cell_status readRTC(char *time);
    cell_status parse(char *buff);
    int polling(char *response);

    private:
    void turnOnPower();
    DigitalOut cell_power;
    char buffer[355];
    void clean(int range);
};

#endif
