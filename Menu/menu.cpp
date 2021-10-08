/*
 * menu.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: serg
 */

#include "menu.h"
#include "../Event/jpot.h"
#include "../Tool/media.h"

extern cMedia oMedia;

SDL_Surface *pMenuFon;
SDL_Surface *pMenuIcon;
SDL_Surface *pMenuItem;

const char *pn[6] = {"1", "2", "3", "4", "5", "6"};

mtMenu mvMenu;

const char *pNameGame[] = {"No Game", "5 Burning Heart", "10 Burning Heart", "5 Burning Hot", "20 Burning Hot", "40 Burning Hot",
		"40 Burning Hot 6",
		"Hot&Cash", "40 Hot&Cash", "40 Lucky King", "40 Mega Clover", "Caramel Hot", "Dice&Roll", "More Dice&Roll",
		"Flaming Hot", "Flaming Hot Extreme", "40 Super Hot", "Lucky Wild", "Lucky Wild more", "Super 20", "Lucky Hot",
		"20 Dazzling Hot"
};


RET_STATE InitMenu(void){

	pMenuFon = oMedia.LoadImage("./Menu/Resource/back.png");
	pMenuIcon = oMedia.LoadImage("./Menu/Resource/icon.png");
	pMenuItem = oMedia.LoadImageAlpha("./Menu/Resource/item.png");
	if(pMenuFon == NULL || pMenuIcon == NULL || pMenuItem == NULL){
		return RET_ERROR;
	}

	if( RET_OK != oMedia.LoadFont(FONT_CREDIT) ||
			RET_OK != oMedia.LoadFont(FONT_MENU)){
		return RET_ERROR;
	}

	return RET_OK;
}

void parse_menu(Uint8 *pBuf, Uint16 Length){
	int i = 0;

	Uint8 *p = (Uint8*) &mvMenu;

	if(Length > sizeof(mtMenu)){
		printf("size big menu");
		return;
	}
	while(Length > i){
		p[i] = pBuf[i];
		i++;
	}
}

Uint32 uMenu(void){

	int ngame;
	int Length;
	char _credit[20];

	static Uint32 _tick;
	static Uint32 _select;

	SDL_Rect icon;
	SDL_Rect bar;

	icon.h = ICON_HEIGHT;
	icon.w = ICON_WIDTH;

	if(_select != mvMenu.select){
		_tick =  mGetTick();
		_select = mvMenu.select;
	}
	if(_tick + 1000 < mGetTick() ){
		_tick = mGetTick();
	}

	// bar undo text name game pos in atlas
	bar.w = 150;
	bar.h = 13;
	bar.x = 0;
	bar.y = 0;

	oMedia.DrawImage(pMenuFon, NULL, 0, 0);

	//visible select game
	if( _tick + 500 > mGetTick() ){
		int x , y;
		x = mvMenu.select >= 5 ? (mvMenu.select - 5) * (ICON_WIDTH + 10) : mvMenu.select * (ICON_WIDTH + 10);
		y = mvMenu.select >= 5 ? (135 + 175) : 135;
		oMedia.FillRect(x, y, ICON_WIDTH + 10, 140, GREY);
	}

	// draw icon
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 5; j++ ){
			ngame = mvMenu.arr[j + i * 5];
			icon.x = ICON_WIDTH * (ngame % 10);
			icon.y = ICON_HEIGHT * (ngame / 10);
			oMedia.DrawImage(pMenuIcon, &icon, 5 + (ICON_WIDTH + 10) * j , i*180 + 140);
			oMedia.DrawImage(pMenuItem, &bar, 5 + (ICON_WIDTH + 10) * j , i*180 + 140 + 110);
			Length = strlen(pNameGame[ngame])*9;
			oMedia.TTF_DrawText(FONT_MENU, (char*)pNameGame[ngame], (ICON_WIDTH + 10) * j + ((150 - Length)/2), i*180 + 140 + 110, WHITE);
		}
	}

	// text select game in atlas
	bar.w = 288;
	bar.h = 34;
	bar.x = 0;
	bar.y = 40;

//	if( _tick + 1000 < mGetTick() ){
		oMedia.DrawImage(pMenuItem, &bar, 262, 488 );
//	}

	// flag language

	bar.w = 61;
	bar.h = 41;
	bar.x = 0;
	bar.y = 74;

	oMedia.DrawImage(pMenuItem, &bar, 615, 536 );

	// indicator amount page
	bar.w = 26;
	bar.h = 26;
	bar.x = 0;
	bar.y = 13;

	for(int i = 0; i < 3; i ++){
		oMedia.DrawImage(pMenuItem, &bar, 345 + i * 35, 550 );
	}
	// select page
	bar.w = 26;
	bar.h = 26;
	bar.x = 26;
	bar.y = 13;

	oMedia.DrawImage(pMenuItem, &bar, 345 + mvMenu.curPage * 35, 550 );

	// text number page
	for(int i = 0; i < 3; i ++){
		oMedia.TTF_DrawText(FONT_MENU,(char*) pn[i], 345 + i * 35 + 8, 550 + 2, WHITE);
	}

	// text CREDIT
	sprintf(_credit, "%d", mvMenu.Credit );
	oMedia.TTF_DrawText(FONT_CREDIT,_credit, 42, 545, YELLOW);

	// logo
	bar.w = 209;
	bar.h = 102;
	bar.x = 510;
	bar.y = 0;
	oMedia.DrawImage(pMenuItem, &bar, 294, 14 );

	ViewJPot();

	oMedia.OutScreen();
	return ST_MENU;
}

void uCloseMenu(void){

}
