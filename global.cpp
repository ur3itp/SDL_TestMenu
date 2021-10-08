/*
 * global.cpp
 *
 *  Created on: Mar 11, 2020
 *      Author: serg
 */

#include "global.h"
#include <SDL/SDL.h>

static Uint32 MediaTick;
static Uint32 videoTick;
static Uint32 TickCadr = 20;

Uint8 MediaState = ST_IDLE;

const char* setup_font = "./Setup/Font/courier-new-cyr.ttf";
const char* temp_font = "./Setup/Font/Beba.ttf";
const char* credit_font = "./Setup/Font/OneSlot.ttf";

tFontFile sFontFile[4] = {	{setup_font, 14},
							{setup_font, 24},
							{temp_font, 16},
							{temp_font, 24}
						};


// raw enum COLOR ; Column R G B
Uint8 ColorTable[MAX_COLOR][3] = {	{ 0,		0xff,		0xff},
							{ 0,		0,			0},
							{ 0,		0,			0xff},
							{ 0xa5,		0x2a,		0x2a},
							{ 0,		0xff,		0xff},
							{ 0,		0,			0xa0},
							{ 0xff,		0,			0xff},
							{ 0,		0x80,		0},
							{ 0x80,		0x80, 		0x80},
							{ 0xad,		0xd8,		0xe6},
							{ 0,		0xff,		0},
							{ 0xff,		0,			0xff},
							{ 0x80,		0,			0},
							{ 0,		0,			0x80},
							{ 0x80,		0x80,		0},
							{ 0xff,		0xa5,		0},
							{ 0x80,		0,			0x80},
							{ 0xff,		0,			0},
							{ 0xc0,		0xc0,		0xc0},
							{ 0,		0x80,		0x80},
							{ 0xff, 	0xff,		0xff},
							{ 0xff, 	0xff,		0}
};

const char *pTmplColor[MAX_COLOR] = { "aqua", "black", "blue", "brown", "cyan", "darkblue",
							"fuchsia", "green", "grey", "lightblue", "lime","magenta",
							"maroon", "navy", "olive", "orange" ,"purple", "red", "silver",
							"teal", "white", "yellow"
							};

const char *pTablLang[]= {"USD", "UAH", "RUR", "ILS"};


void mSetTick(void){
	MediaTick = SDL_GetTicks();
}

Uint32 mGetTick(void){
	return MediaTick;
}

bool UpdateCadr(void){
	Uint32 temp = SDL_GetTicks();
	if(temp > videoTick){
		if((temp - videoTick) > TickCadr ){
			videoTick = temp;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if((0xFFFFFFFF - videoTick + temp) > TickCadr ){
			videoTick = temp;
			return true;
		}
		else {
			return false;
		}
	}

}
