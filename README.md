#Lab6 - Phone
####Students: Jonathan Wegener and Andre Kuhlenschmidt

###The Project:
This project is the software for a phone that is running on the ST Nucleo microcontroller.
It is built using the mbed developer tools which doesn't seem to be terribly portable for
sharing projects but is very portable for moving from one micro controller to another. 
Their tool is hosted at https://github.com/mbedmicro/mbed.git. 

###Results: 
Our phone works for sending and recieving text messages and phone calls. We are particularly proud of our control
loop which allows you to recieve phone calls at anytime. This could be use to implement asynchronous notifications
of arbitrary nature. 

###Difficulties: 
We continue to have issue with recieving touches in the wrong place of the screen. If we had more time
I would say that this could be debugged or at the very least filtered by checking for multiple touches before "recieving"
a touch. Another issue is that sometimes printing any given string causes the nucleo to freeze. There is some indication
that printing commas is the cause of this but that seems unlikely.

###What did we learn: 
We continue to refine our ability to put together a control loop. This project was more about using
available assests wisely then building something new. I, Andre, learned about the existence of strstr which seems to have
many applications. 