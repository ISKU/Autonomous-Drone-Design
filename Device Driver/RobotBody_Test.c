#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include "amazon2_sdk.h"
#include "graphic_api.h"

#include "uart_api.h"
#include "robot_protocol.h"

#include "linux_kbhit.h"

void Logo(void)
{
  	printf("\n\n\n");
  	printf("*****************************************\n");
  	printf("     Welcome to Drone Platform Board \n");
  	printf("     Team: 내맘에SoC드론 \n");
	printf("*****************************************\n"); 
	printf("x - init	w - upPitch	s - downPitch	z - upRoll	c - downRoll\n");
	printf("\nSelected Test Item :  ");
}

void AutoControl()
{
	BOOL b_loop = TRUE;
	int initial = 100;
	int i = 100000;
	char Item;
	
	if (open_graphic() < 0)
		return -1;

	SURFACE* bmpsurf = 0;
	U16* fpga_videodata = (U16*)malloc(180 * 120 * 2);
	
	direct_camera_display_off();
	
	while (initial--) {
		if(kbhit()) {
			printf("\nKey Interrupt\n");
			return 0;
		}
		printf("Initializing");
	}
	
    printf("\nStart AutoControl\n");
    while (i--) {
		
		// Draw 180x120 videodata
		clear_screen();
		read_fpga_video_data(fpga_videodata);
		draw_fpga_video_data(fpga_videodata, 10, 10);
		flip();
		
		// Key Control
		Logo();
 		Item = getchar();
		putchar(Item);

		switch(Item) {
			case 'x' : case 'X' : init();		  break;
			case 'w' : case 'W' : upPitch();      break;
			case 's' : case 'S' : downPitch(); 	  break;
			case 'd' : case 'D' : upYaw();		  break;
			case 'a' : case 'A' : downYaw();      break;
			case 'q' : case 'Q' : upThrottle();   break;
			case 'e' : case 'E' : downThrottle(); break;
			case 'z' : case 'Z' : upRoll(); 	  break;
			case 'c' : case 'C' : downRoll();	  break;
			case 'v' : case 'V' : return 0;
		}

		printf(" %d\n", i);
	}
	
	free(fpga_videodata);
	if (bmpsurf != 0)
		release_surface(bmpsurf);
	close_graphic();
	
	printf("End AutoControl\n");
}

int TestItemSelectRobot(void)
{
   char Item;
 	
	while(1) {
        Logo();
		printf("\nSelected Test Item :  ");
 		Item = getchar();
		putchar(Item);

		switch(Item) {
			case 'x' : case 'X' : init();		  break;
			case 'w' : case 'W' : upPitch();      break;
			case 's' : case 'S' : downPitch(); 	  break;
			case 'd' : case 'D' : upYaw();		  break;
			case 'a' : case 'A' : downYaw();      break;
			case 'q' : case 'Q' : upThrottle();   break;
			case 'e' : case 'E' : downThrottle(); break;
			case 'z' : case 'Z' : upRoll(); 	  break;
			case 'c' : case 'C' : downRoll();	  break;
			case 'v' : case 'V' : return 0;
			
		/*
			case 'a' : case 'A' : init();				break;
			case 'b' : case 'B' : InitSlow();				break;
			case 'z' : case 'Z' : return 0;
			default : printf("\nNo Test Item Selected");	break;
			*/
		}
	}
	return 0;
}

#include <termios.h>
static struct termios inittio, newtio;

void init_console(void)
{
    tcgetattr(0, &inittio);
    newtio = inittio;
    newtio.c_lflag &= ~ICANON;
    newtio.c_lflag &= ~ECHO;
    newtio.c_lflag &= ~ISIG;
    newtio.c_cc[VMIN] = 1;
    newtio.c_cc[VTIME] = 0;

    cfsetispeed(&newtio, B115200);

    tcsetattr(0, TCSANOW, &newtio);
}

int main(void)
{
	int ret;

	init_console();

	ret = uart_open();
	if (ret < 0) return EXIT_FAILURE;

	uart_config(UART1, 9600, 8, UART_PARNONE, 1);

	//TestItemSelectRobot();
   
    AutoControl();
	uart_close();

	return 0;
}


