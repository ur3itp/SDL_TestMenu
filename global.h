/*
 * global.h
 *
 *  Created on: Mar 11, 2020
 *      Author: serg
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int8_t		Sint8;
typedef u_int8_t		Uint8;
typedef int16_t		Sint16;
typedef u_int16_t	Uint16;
typedef int32_t		Sint32;
typedef u_int32_t	Uint32;

typedef Uint32 (*pMfunc)(void);

#define CMD_BOOT 	0x01
#define CMD_SETUP	0x02
#define CMD_MENU	0x04
#define CMD_GAME1	0x07
#define CMD_GAME2	0x0A
#define CMD_SYNC	0x55
#define CMD_ACK		0xAA

#define ST_IDLE			0x00
#define ST_MENU_LOAD	0x02
#define ST_MENU_DONE	0x03
#define ST_MENU			0x04
#define ST_MENU_EXIT	0x05

#define RAW_MAX  30
#define RAW_SIGN 200
#define RAW_XPOS 20
#define RAW_YPOS 40

#define MAX_COLOR 22

enum FONT
{
	FONT_SETUP_BASE = 0,
	FONT_SETUP_BIG,
	FONT_MENU,
	FONT_CREDIT
};

typedef struct{
	const char* file;
	int ptrsize;
} tFontFile;

enum COLOR
{
	AQUA = 0,
	BLACK,
	BLUE,
	BROWN,
	CYAN,
	DARKBLUE,
	FUCHSIA,
	GREEN,
	GREY,
	LIGHTBLUE,
	LIME,
	MAGENTA,
	MAROON,
	NAVY,
	OLIVE,
	ORANGE,
	PURPLE,
	RED,
	SILVER,
	TEAL,
	WHITE,
	YELLOW
};
//	R G B


enum RET_STATE
{
	RET_OK =0,
	RET_BUSY,
	RET_ERROR
};

typedef struct{
	Uint8			ConnectStatus;
	Uint8			Series[3];
	Uint32			Credit;
	Uint8			PosLanguage;
	Uint8			ArrLanguage[10];
	Uint8			PosDenom;
	Uint16			ArrDenom[10];
	Uint32			BetMin;
	Uint32			MaxBet;
	Uint32			Price;
	Uint32			Win;
	Uint8			GameStatus;
	Uint32			Number;
	Uint32			ScriptCount;
	Uint32			SwapCount;

	Uint8			Version;
	Uint8			SubVersion;

	Uint8			TypeBonus;
	Uint32			CreditBonus;

	Uint8			JackPot1Type;
	Uint32			JackPot1Value;
	Uint8			JackPot2Type;
	Uint32			JackPot2Value;
	Uint8			JackPot3Type;
	Uint32			JackPot3Value;
	Uint8			JackPot4Type;
	Uint32			JackPot4Value;
} TParams;

extern const char *pTablLang[];
extern const char *pTmplColor[MAX_COLOR];
extern Uint8 ColorTable[][3];
extern tFontFile sFontFile[4];
extern Uint8 MediaState;

void mSetTick(void);
Uint32 mGetTick(void);
bool UpdateCadr(void);

#endif /* GLOBAL_H_ */
