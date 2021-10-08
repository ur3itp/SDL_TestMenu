/*
 * games.cpp
 *
 *  Created on: May 1, 2020
 *      Author: serg
 */

#include <SDL/SDL.h>

#include "games.h"
#include "./BurningHot20/mgame1.h"
#include "../Tool/media.h"

extern cMedia oMedia;

Uint8 LoadCounter;

mtPanelInfo mvPanelInfo;

int parse_interface(Uint8 *pbuf, int shift){
	Uint8 *p = (Uint8*) &mvPanelInfo;
	for(Uint32 i = 0; i < sizeof(mtPanelInfo); i++){
		p[i] = pbuf[shift++];
	}
	return shift;
}

void draw_panel (int fix){
	char str[20];
	int w , h;

	sprintf(str, "%d", mvPanelInfo.Credit);
	oMedia.TTF_TextSize(FONT_CREDIT, str, &w, &h);
	oMedia.TTF_DrawText(FONT_CREDIT, str, 280 - w, 558, WHITE);

	sprintf(str, "%d", mvPanelInfo.Bet);
	oMedia.TTF_TextSize(FONT_CREDIT, str, &w, &h);
	oMedia.TTF_DrawText(FONT_CREDIT, str, 785 - w, 493, YELLOW);

	sprintf(str, "%d", mvPanelInfo.Lines);
	oMedia.TTF_TextSize(FONT_CREDIT, str, &w, &h);
	oMedia.TTF_DrawText(FONT_CREDIT, str, 785 - w, 518, AQUA);
	if(fix){
		sprintf(str,"FIX");
		oMedia.TTF_DrawText(FONT_MENU, str, 720, 528, GREEN);
	}

	sprintf(str, "%d", mvPanelInfo.Lines * mvPanelInfo.Bet);
	oMedia.TTF_TextSize(FONT_CREDIT, str, &w, &h);
	oMedia.TTF_DrawText(FONT_CREDIT, str, 785 - w, 557, YELLOW);

	sprintf(str, "%.2f %s", (double) mvPanelInfo.Denom / 10, pTablLang[mvPanelInfo.Lang]);
	oMedia.TTF_DrawText(FONT_MENU, str, 490, 520, WHITE);
}




