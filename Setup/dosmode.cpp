/*
 * dosmode.cpp
 *
 *  Created on: Mar 12, 2020
 *      Author: lot
 */


#include "dosmode.h"

Uint8 *pSetupBuf;

RET_STATE InitSetup(void){
	pSetupBuf = new Uint8[4096];
	if(NULL == pSetupBuf){
		printf("error allocate pSetupBuf");
		return RET_ERROR;
	}
	if(0 != ConstrDos()){
		printf("error contr dos");
		return RET_ERROR;
	}
	if(0 != LoadFontDos()){
		printf("error load font dos");
		return RET_ERROR;
	}
	return RET_OK;
}

void parse_boot(Uint8 *pBuf, Uint16 Length){
	int i = 0;

	if(Length > 4096){
		printf("size big setup");
		return;
	}
	while(Length > i){
		pSetupBuf[i] = pBuf[i];
		i++;
	}
}

void BootDos(void){
	SetDos(pSetupBuf);
	FillFon(BLACK);
	DrawRaw(FONT_SETUP_BASE, WHITE);
	VisibleSetup();
}

void SetupDos(void){

	FillFon(BLUE);
	FillBar(0, 0, 800, 45, DARKBLUE);
	for(int i =0; i < 5; i++){
		FillBar(15 + i*160, 540, 120, 50, AQUA);
	}

	clearDos();
	SetDos(pSetupBuf);

	DrawRaw(FONT_SETUP_BASE, WHITE);
	DrawBar(FONT_SETUP_BASE, WHITE);
	DrawKey(FONT_SETUP_BASE, RED);
	VisibleSetup();
}
