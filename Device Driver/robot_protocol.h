/* ------------------------------------------------------------------------ */
/*                  KAIST BATTLE ROBOT CONTROL PROGRAM						*/
/*                   														*/
/*          Coding by YKH      												*/
/*          file : robot_protocol.h    										*/
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
/*                  KAIST BATTLE ROBOT CONTROL PROGRAM            			*/
/*                   														*/
/*          Modified by Goon-Ho Choi, HANOOL ROBOTICS 2003.07.16     		*/
/* ------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------ */
#ifndef __ROBOT_PROTOCOL_H__
#define __ROBOT_PROTOCOL_H__
// 아래의 프로토콜은 상위(Head B/D)에서 로봇 제어 보드 쪽으로의 전달 프로토콜
#define SCI_BUF_SIZE   4
// Check Sum 코드(무선 통신을 위한 안전장치)의 추가를 위해 한 바이트를 늘림
/*********************************************************************
Communication Protocol :

 Start Code(1byte) + Command(1byte) + Data(1byte) + CheckSum = total 4bytes
  0xFF    0x??   0x?? 0x??

*********************************************************************/
#define START_CODE    0x00

/* command definitions */
#define CONT_FWD_LEFT	0x01 /* Left Motor move foward Continuously */ 
#define CONT_FWD_RIGHT  0x02 /* Right Motor move foward Continuously */ 
#define CONT_FWD_ALL	0x03 /* All Motor move foward Continuously */ 
#define CONT_BWD_LEFT   0x04 /* Left Motor move backward Continuously */ 
#define CONT_BWD_RIGHT  0x05 /* Right Motor move backward Continuously */ 
#define CONT_BWD_ALL	0x06 /* All Motor move backward Continuously */
#define CONT_STOP		0x07 /* All Motor stop */
//#define SET_STEP_LEFT   0x08 /* Left Motor Setting steps */
//#define SET_STEP_RIGHT  0x09 /* Right Motor Setting steps */
//#define SET_STEP_ALL	0x0a /* All Motor Setting steps */
//#define GET_STEP_LEFT   0x0b
//#define GET_STEP_RIGHT  0x0c
//#define GET_STEP_ALL	0x0d
//#define STEP_FWD_LEFT   0x0e
//#define STEP_FWD_RIGHT  0x0f
//#define STEP_FWD_ALL	0x10
//#define STEP_BWD_LEFT   0x11
//#define STEP_BWD_RIGHT	0x12
//#define STEP_BWD_ALL	0x13

#define LASER_SHOOT		0x14 /* Shoot the laser pointer */
#define GET_ENERGY		0x15 /* Get the remains energy */
#define GET_SHOT		0x16 /* Get the remains bullet number */

#define SET_V_LEFT		0x17
#define SET_V_RIGHT		0x18
#define SET_V_ALL		0x19
#define GET_V_LEFT		0x1a
#define GET_V_RIGHT		0x1b

#define GET_V_ALL		0x1c ////////////////////////////////////////////

//#define DAMAGE_ALERT	0xFE

// 한울 추가분
#define CHECK_BOTTOM	0x20		// 바닥 센서의 감지 여부와 감지시 위치 정보 받음
#define CHECK_DAMAGE_POINT	0x30	// 피격되었는지 여부와 맞았을 경우 어느 위치인지 대한 정보 받음
#define LASER_READY	0x40	// 준비 되어있으면 data byte에 1, 준비 안되면 0으로 올라 옵니다.

/************************************************************************************/
/* 아래 부분은 위에서 사용한 부분과 틀린 부분임. -> 주의 깊게 봐야함 				*/
/* 위의 Command를 보냈을 경우 Receive부분의 Comm_OK에 실려서 올라옴					*/
/************************************************************************************/ 
#define MOTOR_ALARM	0x41	// 앞에 장애물이 있어서 모터가 과부하가 걸려서 동작할수 없을 경우 임.
#define GAME_OVER	0x42	// 게임이 끝났을 경우 임. 이때는 어떠한 명령을 내려도 리턴 값으로 이값만 올라옴.
#define DEAD 0x44
// 총을 다 맞아서 죽었을때는 움직이지 않습니다. 이때는 어떠한 명령을 내려도 
// 리턴 값으로 이 값만이 전달 되오니 참고 하시기 바랍니다.

// CheckSum 방식
/*	CheckSum = ((unsigned char)Command & 0x0f) + (((unsigned char)Command>>4)&0x0f) 
				+ ((unsigned char)Data & 0x0f) + (((unsigned char)Data>>4)&0x0f);
*/


//
//
// 로봇 제어 보드에서 상위(HEAD) 보드로의 전송 프로토콜
//
//
/*********************************************************************
Communication Protocol :

 Start Code(1byte) + Comm_OK(1byte) + Data(1byte) + CheckSum = total 4bytes
  0xFF    0x??   0x?? 0x??

*********************************************************************/
// 데이터는 일단 1byte면 되지만 송수신의 크기를 일치시켰습니다.
//#define CHECK_BOTTOM에 대한 리턴 데이터
// 왼쪽 위 감지 :		Data=0x01;
// 왼쪽 아래 감지 :		Data=0x04;
// 오른쪽 위 감지 :		Data=0x11;
// 오른쪽 아래 감지 :	Data=0x14;
/******************Bottom*****************************/
// 위의 값은 틀린 값임 ->아래 값을 참조하세요
// 탱크를 위에서 보았을 경우 입니다.
// 비트 0->왼쪽 앞
// 비트 1->오른쪽 앞
// 비트 2->왼쪽 뒤
// 비드 3->오른쪽 뒤

//#define CHECK_DAMAGE_POINT에 대한 리턴 데이터
// 정면 피격 :		Data=0x01; 
// 후면 피격 :		Data=0x04;
// 우측면 피격 :	Data=0x11;
// 좌측면 피격 :	Data=0x14;

/********************* Damage Point ******************/
// 비트 0-> 정면
// 비트 1-> 오른쪽
// 비트 2-> 후면
// 비트 3-> 왼쪽

//#define COMM_ERROR
// 전송 받은 명령에 오류가 있을 경우 재전송을 요구함.
//		Comm_OK=0xFF;

//#define COMM_OK
// 전송 받은 명령에  오류가 없을 경우
// Comm_OK=0x00;
// 전송 받은 명령이 리턴 데이터를 요구하는 경우 : Data에 해당 데이터 리턴
// 전송 받은 명령이 리턴 데이터를 요구하지 않은 경우 : Data=0x00 

// CheckSum 방식
/*	CheckSum = ((unsigned char)Comm_OK & 0x0f) + (((unsigned char)Comm_OK>>4)&0x0f) 
				+ ((unsigned char)Data & 0x0f) + (((unsigned char)Data>>4)&0x0f);
*/

/* 
- 참고적으로 거의 모든 프로토콜은 이전과 동일하게 가려고 했습니다.

- 추가된 프로토콜은 배선의 간략화 등을 위한 것과 경기를 좀더 더 효율적인 진행을 위한 것입니다.

- CheckSum 코드의 추가는 무선 통신을 위한 조치입니다.

  CheckSum코드의 추가로 HEAD 보드 쪽에서 명령을 전송 후 반드시 수신 모드로 전환 대기 하셔야 합니다.
이 경우 전송 선로 문제로 Hang Up이 걸릴 수 있으므로 일정 시간 동안 데이터의 수신이 없으면 알람 등의 조치가 있어야 합니다.

- 저희 쪽에서 재전송 요구가 보내지거나  CheckSum이 일치 하지 않으면 반드시 이전 명령을 다시 보내 주십시오.
*/

////////////////////////////////////////////////////////////////////////////////
void DelayLoop(int delay_time);
//void Send_Command(unsigned char Ldata, unsigned char Ldata1);
void Send_Command(unsigned char throttle, unsigned char roll, unsigned char pitch, unsigned char yaw);
unsigned char Receive_Ack(void);
void init(void);
//void InitSlow();

void upThrottle(void);
void downThrottle(void);
void upRoll(void);
void downRoll(void);
void upPitch(void);
void downPitch(void);
void upYaw(void);
void downYaw(void);
////////////////////////////////////////////////////////////////////////////////

#endif // __ROBOT_PROTOCOL_H__


