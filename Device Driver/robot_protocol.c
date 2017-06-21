/************************************************************************
  Title     : Robot Body Protocol Source File
  File name : robot_protocol.c    

  Author    : adc inc. (oxyang@adc.co.kr)
  History
		+ v0.0  2007/2/14
		+ v1.0  2008/8/6
************************************************************************/
#include <stdio.h>
#include <string.h>
#include "robot_protocol.h"
#include "uart_api.h"
//////////////////////////////////////////////////// Protocol Test
unsigned char throttle;
unsigned char roll;
unsigned char pitch;
unsigned char yaw;

void DelayLoop(int delay_time)
{
	while(delay_time)
		delay_time--;
}

void Send_Command(unsigned char throttle, unsigned char roll, unsigned char pitch, unsigned char yaw)
{
	unsigned char Command_Buffer[5] = {0};

	Command_Buffer[0] = START_CODE;	// Start Byte -> 0x00
	Command_Buffer[1] = throttle; // Start Byte1 -> 0x55
    Command_Buffer[2] = roll;
	Command_Buffer[3] = pitch;
	Command_Buffer[4] = yaw;  
	
	uart1_buffer_write(Command_Buffer, 5);
	printf("\n\nS : %x, T : %x, R : %x, P : %x, Y : %x \n\n", Command_Buffer[0], Command_Buffer[1], Command_Buffer[2], Command_Buffer[3], Command_Buffer[5]);
}

#define ERROR	0
#define OK	1

void init(void) // Start code
{
	throttle = 0x01;
	roll 	 = 0x7f;
	pitch 	 = 0x7f;
	yaw 	 = 0x7f; //start drone
	
	Send_Command(throttle, roll, pitch, yaw);
}
//-------------------------------------------------- Control 
void upThrottle(void)
{
	if(roll != 0x7f)
		roll = 0x7f;
	Send_Command(throttle++, roll, pitch, yaw);
	printf("just in case, check the [w] key was pushed wright\n and you fill the rest of function\n ");
}
void downThrottle(void)
{
	if(roll != 0x7f)
		roll = 0x7f;
	Send_Command(throttle--, roll, pitch, yaw);
}

void upRoll(void)
{
	roll += 10;
	Send_Command(throttle, roll++, pitch, yaw);
}

void downRoll(void)
{
	roll -= 10;
	Send_Command(throttle, roll--, pitch, yaw);
}

void upPitch(void)
{
	pitch += 10;
	Send_Command(throttle, roll, pitch++, yaw);
}

void downPitch(void)
{
	pitch -= 10;
	Send_Command(throttle, roll, pitch--, yaw);

}

void upYaw(void)
{
	Send_Command(throttle, roll, pitch, yaw++);
}

void downYaw(void)
{
	Send_Command(throttle, roll, pitch, yaw--);
}
/*
void InitSlow()
{
	Send_Command(0x02, 0xfd);
}*/

