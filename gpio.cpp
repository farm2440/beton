#include "gpio.h"
/* See /home/svilen/work/Qtopia/stivlib/docs/GPIO.html for details */
/*
 От блога ми farm2440.blogspot.com - как се достъпват gpio от команден ред:

HOW TO CONTROL GPIO FROM THE COMMAND LINE:
When the new kernel is uploaded let's first check the access to GPIO from the command line.
Telnet to mini2440 and go to sys/class/gpio folder:

$ telnet 192.168.1.230
[root@FriendlyARM /]# cd sys/class/gpio/
[root@FriendlyARM gpio]# ls
export       gpiochip0    gpiochip128  gpiochip160  gpiochip192  gpiochip224  gpiochip32   gpiochip64   gpiochip96   unexport

Folders gpiochip0 , gpiochip128 .... represent GPIO drivers for each port. Ports are named A,B,C....
Check the port for each gpiochipX:

[root@FriendlyARM gpio]# cat gpiochip0/label
GPIOA
[root@FriendlyARM gpio]# cat gpiochip32/label
GPIOB
[root@FriendlyARM gpio]# cat gpiochip192/label
GPIOG

Each pin has it's corresponding access number. For example buzzer is connected to GPB0 ( Port B pin 0) and port B is accessible from gpiochip32 so the number to access the buzzer is 32.
Led1 is connected go GPB5. It's access number is 32+5 = 37
Buttons are connected to port G - gpiochip192

Function    Port    Access number
Buzzer        GPB0    32
Led1           GPB5    37
Led2           GPB6    38
Led3           GPB7    39
Led4           GPB8    40
Btn1           GPG0    192
Btn2           GPG3    195
Btn3           GPG5    197
Btn4           GPG6    198
Btn5           GPG7    199
Btn6           GPG11    203


Now open access to the buzzer. :

[root@FriendlyARM gpio]# echo 32  > export
[root@FriendlyARM gpio]# ls
export       gpio32       gpiochip0    gpiochip128  gpiochip160  gpiochip192  gpiochip224  gpiochip32   gpiochip64   gpiochip96   unexport

A new link gpio32 appeared now. Let's check the current direction and make it an output:

[root@FriendlyARM gpio]# cat gpio32/direction
in

[root@FriendlyARM gpio]# echo "high" > gpio32/direction
[root@FriendlyARM gpio]# cat gpio32/direction
out

Turn the buzzer on and off:
[root@FriendlyARM gpio]# echo "1" > gpio32/value
[root@FriendlyARM gpio]# echo "0" > gpio32/value

Close the access:
[root@FriendlyARM gpio]# echo 32  > unexport

  */

//--------------------------------------------------------------------------------------------------------
GPIO::GPIO(int pin)
/*
  Към конструктора се подава число , което определя пина от хедъра. Всеки GPIO пин има свой уникален номер.
  За удобство номерата на пиновете на хедъра са дефинирани към GPIO номерата в gpio.h както е даден по долу:

  #define	PIN31	32   //buzzer

Each pin has it's corresponding access number. For example buzzer is connected to GPB0 ( Port B pin 0) and port B is accessible from gpiochip32 so the number to access the buzzer is 32.
Led1 is connected go GPB5. It's access number is 32+5 = 37
Buttons are connected to port G - gpiochip192

Function    Port    Access number
Buzzer        GPB0    32
Led1           GPB5    37
Led2           GPB6    38
Led3           GPB7    39
Led4           GPB8    40
Btn1           GPG0    192
Btn2           GPG3    195
Btn3           GPG5    197
Btn4           GPG6    198
Btn5           GPG7    199
Btn6           GPG11    203

  */
{	_pinNumber = pin;
	_valueString = QString("/sys/class/gpio/gpio%1/value").arg(pin);
	_directionString = QString("/sys/class/gpio/gpio%1/direction").arg(pin);
	_strPin = QString("%1").arg(pin);
}
//--------------------------------------------------------------------------------------------------------
GPIO::~GPIO()
{
FILE * fp;
//This will create the folder /sys/class/gpio/gpio37
		if ((fp = fopen("/sys/class/gpio/unexport", "ab")) == NULL) return;
		rewind(fp);		//Set pointer to begining of the file
                fwrite(_strPin.toLatin1(), sizeof(char),_strPin.length() , fp);
		fclose(fp);
}
//--------------------------------------------------------------------------------------------------------
int GPIO::openPin()
{
FILE * fp;
//This will create the folder /sys/class/gpio/gpio37
	if ((fp = fopen("/sys/class/gpio/export", "ab")) == NULL) return -1;	
	rewind(fp);//Set pointer to begining of the file
        fwrite(_strPin.toLatin1(), sizeof(char),_strPin.length() , fp);
	fclose(fp);
	return 0;
}
//--------------------------------------------------------------------------------------------------------
int GPIO::closePin()
{
FILE * fp;
//This will create the folder /sys/class/gpio/gpio37
		if ((fp = fopen("/sys/class/gpio/unexport", "ab")) == NULL) return -1;		
		rewind(fp);//Set pointer to begining of the file
                fwrite(_strPin.toLatin1(), sizeof(char),_strPin.length() , fp);
		fclose(fp);
		return 0;
}
//--------------------------------------------------------------------------------------------------------
int GPIO::setDirection(Direction direction)
{ //set direction in/out. returns 0 if ok and -1 on error
	FILE * fp;
                        if ((fp = fopen(_directionString.toLatin1(), "rb+")) == NULL) return -1;
			rewind(fp);//Set pointer to begining of the file
			if(direction == In)  fwrite("in", sizeof(char),4, fp);
			if(direction == Out) fwrite("out", sizeof(char),4, fp);
			fclose(fp);
			return 0;
}
//--------------------------------------------------------------------------------------------------------
/*
int GPIO::getDirection()
{//returns direction
	
}*/
//--------------------------------------------------------------------------------------------------------
int GPIO::setState(bool state)
{//state is 0 or 1. No effect if other value. returns the new state or -1 on error
FILE * fp;
                if ((fp = fopen(_directionString.toLatin1(), "rb+")) == NULL) return -1;
		rewind(fp);//Set pointer to begining of the file
		if(state) fwrite("high", sizeof(char),4, fp);
		else fwrite("low", sizeof(char),3, fp);
		fclose(fp);
		return 0;
}
//--------------------------------------------------------------------------------------------------------
bool GPIO::getState()
{	//returns 1 or 0 - the pin state. Returns -1 on error
FILE * fp;
char value;
        if ((fp = fopen(_valueString.toLatin1(), "rb+")) == NULL) return false;
	rewind(fp);//Set pointer to begining of the file
	fread(&value, sizeof(char),1, fp);
	fclose(fp);
	if(value=='1') return true;
	if(value=='0') return false;
	return false;
}
//--------------------------------------------------------------------------------------------------------
