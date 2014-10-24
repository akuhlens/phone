/*
  gprs.h
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:lawliet.zou@gmail.com
  2013-11-14

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef __GPRS_H__
#define __GPRS_H__

#include <stdio.h>
#include "mbed.h"

#define DEFAULT_TIMEOUT         5
#define SMS_MAX_LENGTH          16


enum GPRS_MESSAGE {
    MESSAGE_RING = 0,
    MESSAGE_SMS  = 1,
    MESSAGE_ERROR
};


/** GPRS class.
 *  Used for mobile communication. attention that GPRS module communicate with MCU in serial protocol
 */
class GPRS
{
public:
    /** Create GPRS instance
     *  @param tx  uart transmit pin to communicate with GPRS module
     *  @param rx  uart receive pin to communicate with GPRS module
     *  @param baudRate baud rate of uart communication
     *  @param number default phone number during mobile communication
     */
    GPRS(PinName tx, PinName rx, int baudRate,char *number) : gprsSerial(tx, rx) {
        //gprsSerial.baud(baudRate);
        phoneNumber = number;
    };
    
    int powerCheck(void);
    /** init GPRS module including SIM card check & signal strength & network check
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int init(void);

    /** check SIM card' Status
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int checkSIMStatus(void);

    /** check signal strength
     *  @returns
     *      signal strength in number(ex 3,4,5,6,7,8...) on success
     *      -1 on error
     */
    int checkSignalStrength(void);

    /** set SMS format and processing mode
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int settingSMS(void);

    /** send text SMS
     *  @param  *number    phone number which SMS will be send to
     *  @param  *data   message that will be send to
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int sendSMS(char *number, char *data);

    /** read SMS by index
     *  @param  *message   buffer used to get SMS message
         *  @param  index    which SMS message to read
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int readSMS(char *message, int index);

    /** delete SMS message on SIM card
     *  @param  *index    the index number which SMS message will be delete
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int deleteSMS(int index);

    /** read SMS when coming a message,it will be store in messageBuffer.
     *  @param message  buffer used to get SMS message
     */
    int getSMS(char* message);

    /** call someone
     *  @param  *number    the phone number which you want to call
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int callUp(char *number);

    /** auto answer if coming a call
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int answer(void);

    /** a loop to wait for some event. if a call comes in, it will auto answer it and if a SMS message comes in, it will read the message
     *  @param  *check    whether to check phone number when get event
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int loopHandle(void);

    /** gprs network init
     *  @param *apn Access  Point Name to connect network
     *  @param *userName    general is empty
     *  @param *passWord    general is empty
     */
    int networkInit(char* apn, char* userName = NULL, char* passWord = NULL);
    /** build TCP connect
     *  @param  *ip    ip address which will connect to
     *  @param  *port   TCP server' port number
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int connectTCP(char *ip, char *port);

    /** send data to TCP server
     *  @param  *data    data that will be send to TCP server
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int sendTCPData(char *data);

    /** close TCP connection
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int closeTCP(void);

    /** close TCP service
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int shutTCP(void);

    Serial gprsSerial;
    //USBSerial pc;
    
private:
    /** read from GPRS module and save to buffer array
     *  @param  *buffer buffer array to save what read from GPRS module
     *  @param  *count  the maximal bytes number read from GPRS module
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int readBuffer(char *buffer,int count);

    /** send AT command to GPRS module
     *  @param  *cmd command array which will be send to GPRS module
     */
    void sendCmd(char *cmd);

    /** check GPRS module response before timeout
     *  @param  *resp   correct response which GPRS module will return
     *  @param  *timeout    waiting seconds till timeout
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int waitForResp(char *resp, int timeout);

    /** send AT command to GPRS module and wait for correct response
     *  @param  *cmd    AT command which will be send to GPRS module
     *  @param  *resp   correct response which GPRS module will return
     *  @param  *timeout    waiting seconds till timeout
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int sendCmdAndWaitForResp(char *cmd, char *resp, int timeout);

    Timer timeCnt;
    char *phoneNumber;
    char messageBuffer[SMS_MAX_LENGTH];
};

#endif

