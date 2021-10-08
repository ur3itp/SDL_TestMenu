/*
 * mgame2.cpp
 *
 *  Created on: May 5, 2020
 *      Author: serg
 */

#include "mgame2.h"
#include <SDL/SDL.h>

#include "../../Tool/media.h"

extern cMedia oMedia;

//##############################################
const Sint8  arrRollShiftStart[] = {-5 , -10, -15, -20, -25, -30};
const Sint8  arrRollShiftStop[] = {10, 20, 30, 40, 30, 20, 10, 0, -5, -10, 0};
const Uint8  arrRollStartTime[] = {0, 10, 20, 30, 40};
const Uint16 arrReelSpeedTime[] = {50, 70, 100, 130, 160};
const Uint16 arrReelSlowly[] = {10, 150, 200, 250, 300};
const Uint16 shiftReelSpeed = 28;
const Uint16 shiftReelSlowly = 15;

mtRoll mvRoll[5] = {
		{IDLE_ROLL, 0, 0, 0},
		{IDLE_ROLL, 0, 0, 0},
		{IDLE_ROLL, 0, 0, 0},
		{IDLE_ROLL, 0, 0, 0},
		{IDLE_ROLL, 0, 0, 0}
};

const Uint8 symbRoll1[] = { 0, 1, 3 ,4 , 5, 2, 6, 7, 8, 9, 10, 1, 2, 3, 5, 2, 4, 0, 2, 8, 4, 3, 1, 8};
const Uint8 symbRoll2[] = { 0, 1, 3 ,4 , 5, 2, 6, 7, 8, 9, 10, 1, 2, 3, 5, 2, 4, 0, 2, 8, 4, 3, 1, 8};
const Uint8 symbRoll3[] = { 0, 1, 3 ,4 , 5, 2, 6, 7, 8, 9, 10, 1, 2, 3, 5, 2, 4, 0, 2, 8, 4, 3, 1, 8};
const Uint8 symbRoll4[] = { 0, 1, 3 ,4 , 5, 2, 6, 7, 8, 9, 10, 1, 2, 3, 5, 2, 4, 0, 2, 8, 4, 3, 1, 8};
const Uint8 symbRoll5[] = { 0, 1, 3 ,4 , 5, 2, 6, 7, 8, 9, 10, 1, 2, 3, 5, 2, 4, 0, 2, 8, 4, 3, 1, 8};
const Uint8 *pSymbRoll[5] = {symbRoll1, symbRoll2, symbRoll3, symbRoll4, symbRoll5};
const Uint8 symbRollAmount[5] = {sizeof(symbRoll1), sizeof(symbRoll2), sizeof(symbRoll3), sizeof(symbRoll4), sizeof(symbRoll5) };

Uint8 mSwapSymbArrGame2[5][3];
Uint8 mRollSymbArrGame2[5][5];

//##############################################

Uint8 IntStGame2;
Uint32 RetStGame2;

SDL_Surface *pFonGame2;
SDL_Surface *pSymGame2;
SDL_Surface *pAnmGame2[11];
SDL_Surface *pExpGame2;

void InitGame2(void){
	LoadCounter = 0;
}

Uint32 Load_Game2(void){
	Uint32 var;
	switch(LoadCounter){
		case 0:
			pFonGame2 = oMedia.LoadImage("./Games/BurningHot5/Resource/back.png");
			var = OMTS_RET_LOAD;
			LoadCounter = 1;
			break;
		case 1:
			pSymGame2 = oMedia.LoadImage("./Games/BurningHot20/Resource/atlas_icon.png");
			LoadCounter = 2;
			var = OMTS_RET_LOAD;
			break;
		case 2:
			pAnmGame2[9] = oMedia.LoadImage("./Games/BurningHot5/Resource/baks.png");
			LoadCounter = 3;
			var = OMTS_RET_LOAD;
			break;
		case 3:
			pAnmGame2[4] = oMedia.LoadImage("./Games/BurningHot5/Resource/bell.png");
			LoadCounter = 4;
			var = OMTS_RET_LOAD;
			break;
		case 4:
			pAnmGame2[0] = oMedia.LoadImage("./Games/BurningHot5/Resource/cherry.png");
			LoadCounter = 5;
			var = OMTS_RET_LOAD;
			break;
		case 5:
			pAnmGame2[8] = oMedia.LoadImage("./Games/BurningHot5/Resource/clever.png");
			LoadCounter = 6;
			var = OMTS_RET_LOAD;
			break;
		case 6:
			pAnmGame2[6] = oMedia.LoadImage("./Games/BurningHot5/Resource/grap.png");
			LoadCounter = 7;
			var = OMTS_RET_LOAD;
			break;
		case 7:
			pAnmGame2[1] = oMedia.LoadImage("./Games/BurningHot5/Resource/lemon.png");
			LoadCounter = 8;
			var = OMTS_RET_LOAD;
			break;
		case 8:
			pAnmGame2[5] = oMedia.LoadImage("./Games/BurningHot5/Resource/melon.png");
			LoadCounter = 9;
			var = OMTS_RET_LOAD;
			break;
		case 9:
			pAnmGame2[3] = oMedia.LoadImage("./Games/BurningHot5/Resource/orange.png");
			LoadCounter = 10;
			var = OMTS_RET_LOAD;
			break;
		case 10:
			pAnmGame2[2] = oMedia.LoadImage("./Games/BurningHot5/Resource/plum.png");
			LoadCounter = 11;
			var = OMTS_RET_LOAD;
			break;
		case 11:
			pAnmGame2[7] = oMedia.LoadImage("./Games/BurningHot5/Resource/seven.png");
			LoadCounter = 12;
			var = OMTS_RET_LOAD;
			break;
		case 12:
			pAnmGame2[10] = oMedia.LoadImage("./Games/BurningHot5/Resource/star.png");
			LoadCounter = 13;
			var = OMTS_RET_LOAD;
			break;
		case 13:
			pExpGame2 = oMedia.LoadImage("./Games/BurningHot5/Resource/expand.png");
			LoadCounter = 14;
			var = OMTS_RET_LOAD;
			break;
		case 14:
			var = OMTS_RET_INIT;
			break;
	}
	oMedia.FillRect(0, 0, 800, 600, BLACK);
	oMedia.OutScreen();
	return var;
}

void _mdraws2 (int baraban, int shift){
	SDL_Rect posSymb, posFon;
	int symb;

	posSymb.w = SIZE_SYMBOL;
	posSymb.h = SIZE_SYMBOL;

	for(int j = 0; j < 5; j++){
		symb = mRollSymbArrGame2[baraban][j];
		posSymb.x = symb * SIZE_SYMBOL;
		posSymb.y = 0;
		if(symb > 5){
			posSymb.y = SIZE_SYMBOL;
			posSymb.x -= SIZE_SYMBOL * 6;
		}

		posFon.x = baraban * SIZE_SYMBOL + 14 + baraban*14 ;
		posFon.y = 55 - (SIZE_SYMBOL - j * SIZE_SYMBOL) + shift;
		oMedia.DrawImage(pSymGame2,&posSymb, &posFon);
	}
}

Uint32 draw_symb2(void){
	for(int i = 0; i < 5; i++){
		_mdraws2(i, 0);
		mvRoll[i].mvStateRoll = IDLE_ROLL;
	}

	return OMTS_RET_OVER;
}

void _draw_roll2(int baraban){

	switch(mvRoll[baraban].mvStateRoll){
		case IDLE_ROLL:
			mvRoll[baraban].roll_shift = 0;
			if(mvRoll[baraban].roll_move++ == arrRollStartTime[baraban]){
				mvRoll[baraban].mvStateRoll = START_ROLL;
				mvRoll[baraban].roll_move = 0;
			}
			break;
		case START_ROLL:
			mvRoll[baraban].roll_shift = arrRollShiftStart[mvRoll[baraban].roll_move];
			if(++mvRoll[baraban].roll_move == sizeof(arrRollShiftStart)){
				mvRoll[baraban].roll_move = 0;
				mvRoll[baraban].mvStateRoll = SPEED_ROLL;
			}
			break;
		case SPEED_ROLL:
			if(++mvRoll[baraban].roll_move > arrReelSpeedTime[baraban]){
				mvRoll[baraban].roll_move = 0;
				mvRoll[baraban].mvStateRoll = SWAP_ROLL;
			}
			mvRoll[baraban].roll_shift += shiftReelSpeed;
			break;
		case SLOWLY_ROLL:
			mvRoll[baraban].roll_shift += shiftReelSlowly;
			break;
		case SWAP_ROLL:
			mvRoll[baraban].roll_shift += shiftReelSlowly;
			if(mvRoll[baraban].roll_move == 4){
				mvRoll[baraban].mvStateRoll = STOP_ROLL;
				mvRoll[baraban].roll_move = 0;
			}
			break;
		case STOP_ROLL:
			mvRoll[baraban].roll_shift = arrRollShiftStop[mvRoll[baraban].roll_move];
			if(++mvRoll[baraban].roll_move == sizeof(arrRollShiftStop)){
				mvRoll[baraban].roll_move = 0;
				mvRoll[baraban].mvStateRoll = END_ROLL;
			}
			break;
		case END_ROLL:
			break;
	}

	_mdraws2(baraban, mvRoll[baraban].roll_shift);

	if(mvRoll[baraban].roll_shift > 143){
		mvRoll[baraban].roll_shift = 0;
		int i = 4;
		do{
			mRollSymbArrGame2[baraban][i] = mRollSymbArrGame2[baraban][i - 1];
		}while(--i != 0);
		if(mvRoll[baraban].mvStateRoll == SWAP_ROLL){
			mRollSymbArrGame2[baraban][0] =  mSwapSymbArrGame2[baraban][abs(2 - mvRoll[baraban].roll_move++)];

		}
		else{
			mRollSymbArrGame2[baraban][0] =  pSymbRoll[baraban][mvRoll[baraban].roll_ix];
		}
		mvRoll[baraban].roll_ix++;
		if(mvRoll[baraban].roll_ix >= symbRollAmount[baraban]){
			mvRoll[baraban].roll_ix = 0;
		}
	}
}
Uint32 draw_roll2(void){
	Uint32 ret = 0;

	for(int i=0; i < 5; i++){
		_draw_roll2(i);
		if(mvRoll[i].mvStateRoll == END_ROLL){
			ret++;
		}
	}
	if(ret == 5){
		return OMTS_RET_SCORE;
	}
	return OMTS_RET_REEL;
}

Uint32 Game2(void){
	SDL_Rect _rect;
	_rect.x = 14;
	_rect.y = 55;
	_rect.w = 5*143 + 4*14;
	_rect.h = 143 * 3;

	pMfunc pVarReel;


	switch(IntStGame2){
		case IMFS_CMD_LOAD:
			RetStGame2 = Load_Game2();
			return RetStGame2;
			break;
		case IMFS_CMD_GOVER:
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 3; j++){
					mRollSymbArrGame2[i][j+1] = mSwapSymbArrGame2[i][j];
				}
			}
			pVarReel = &draw_symb2;
			break;
		case IMFS_CMD_REEL:
			pVarReel = &draw_roll2;
			break;
		case IMFS_CMD_SCORE:
			pVarReel = &draw_symb2;
			break;

	}

//	if(UpdateCadr()){
		oMedia.DrawImage(pFonGame2, NULL, 0, 0);
		draw_panel(1);
		oMedia.SetClipRect(&_rect);
		RetStGame2 = pVarReel();
		oMedia.SetClipRect(NULL);
		oMedia.OutScreen();
//	}
	return RetStGame2;
}

int parse_game2(Uint8 *pbuf, int shift){

	Uint8 *p = (Uint8*) mSwapSymbArrGame2;

	IntStGame2 = pbuf[shift++];
	switch(IntStGame2){
		case IMFS_CMD_LOAD:
			return shift;
			break;
		case IMFS_CMD_GOVER:
			break;
		case IMFS_CMD_REEL:
			break;
		case IMFS_CMD_SCORE:
			break;
	}
		shift = parse_interface(pbuf, shift);
		for(Uint32 i = 0; i < sizeof(mSwapSymbArrGame2); i++){
			p[i] = pbuf[shift++];
		}
	return shift;
}

