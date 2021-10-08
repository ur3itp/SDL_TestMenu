/*
 * jpot.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: serg
 */

#include "jpot.h"
#include <SDL/SDL.h>
#include "../Tool/media.h"

extern cMedia oMedia;
extern SDL_Surface *pMenuItem;

void ViewJPot(void){
	SDL_Rect bar;

	//JackPot
	bar.w = 108;
	bar.h = 30;
	bar.x = 294;
	bar.y = 0;

	oMedia.DrawImage(pMenuItem, &bar, 4, 12 );
	bar.y = bar.h;
	oMedia.DrawImage(pMenuItem, &bar, 125, 12 );
	bar.x += bar.w;
	bar.y = 0;
	oMedia.DrawImage(pMenuItem, &bar, 570, 12 );
	bar.y = bar.h;
	oMedia.DrawImage(pMenuItem, &bar, 686, 12 );

	oMedia.TTF_DrawText(FONT_MENU,(char*) "123456", 33, 16, WHITE);

}
