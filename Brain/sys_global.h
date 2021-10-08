/*
 * master.h
 *
 *  Created on: Mar 14, 2020
 *      Author: lot
 */

#ifndef BRAIN_SYS_GLOBAL_H_
#define BRAIN_SYS_GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL/SDL.h>

#define xxxNONE		255
#define xxxSTARTUP 	254
#define xxxSETUP	0
#define xxxMENU		1
#define xxxGame1	2
#define xxxGame2	3
#define xxxGame3	4
#define xxxGame4	5
#define xxxGame5	6
#define xxxGame6	7
#define xxxGame7	8
#define xxxGame8	9
#define xxxGame9	10
#define xxxGame10	11



#define RAW_MAX  30
#define RAW_COLUMN 120
//#define RAW_XPOS 10
//#define RAW_YPOS 40
#define MAX_COLOR 22

typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

typedef void (*pSfunc)(Uint8);

#define CMD_BOOT 	0x01
#define CMD_SETUP	0x02
#define CMD_MENU	0x04
#define CMD_GAME1	0x07
#define CMD_GAME2	0x0A
#define CMD_SYNC	0x55
#define CMD_DATA	0x56
#define CMD_ACK		0xAA

#define MDS_MENU_LOAD	0x02
#define MDS_MENU		0x04


//enum RET_STATE
//{
//	RET_OK =0,
//	RET_BUSY,
//	RET_ERROR
//};

#endif /* BRAIN_SYS_GLOBAL_H_ */
