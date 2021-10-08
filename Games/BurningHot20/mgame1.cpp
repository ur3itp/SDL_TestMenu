/*
 * game1.cpp
 *
 *  Created on: May 1, 2020
 *      Author: serg
 */

#include "mgame1.h"
#include <SDL/SDL.h>

#include "../../Tool/media.h"

extern cMedia oMedia;

Uint32 StGame1;

SDL_Surface *pFonGame1;
SDL_Surface *pSymGame1;

void InitGame1(void){
	StGame1 = 0;
}

Uint32 Load_Game1(void){
	Uint32 var;
	switch(StGame1){
		case 0:
			pFonGame1 = oMedia.LoadImage("./Games/BurningHot20/Resource/back.png");
			var = OMTS_RET_LOAD;
			StGame1 = 1;
			break;
		case 1:
			pSymGame1 = oMedia.LoadImage("./Games/BurningHot20/Resource/back.png");
			var = OMTS_RET_LOAD;
			break;
	}
	oMedia.FillRect(0, 0, 800, 600, BLACK);
	oMedia.OutScreen();
	return var;
}

Uint32 Game1(void){
	oMedia.DrawImage(pFonGame1, NULL, 0, 0);
	draw_panel(1);
	oMedia.OutScreen();

	return OMTS_RET_OVER;
}
