#ifndef READLINE_H
#define READLINE_H
#include <mbed.h>

int readline(Serial *pc, char* line, int len);
#endif