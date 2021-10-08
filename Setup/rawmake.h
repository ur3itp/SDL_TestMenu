/*
 * boot.h
 *
 *  Created on: Mar 10, 2020
 *      Author: serg
 */

#ifndef SETUP_RAWMAKE_H_
#define SETUP_RAWMAKE_H_

#include "../global.h"
#include "../Tool/media.h"

typedef struct {
	Uint8	Layer;
	Uint8  	cntRaw[RAW_MAX];
	Uint8  	*Raw[RAW_MAX];
	Uint8  	cntBar[2][3];
	Uint8  	*Bar[2][3];
	Uint8 	cntKey[3][5];
	Uint8	*Key[3][5];
}tDosRaw;

int LoadFontDos(void);

int ConstrDos(void);
void clearDos(void);
int SetLayer(Uint8 *pbuf);
int SetRaw(Uint8 *pbuf);
int SetBar(Uint8 *pbuf);
int SetKey(Uint8 *pbuf);
int SetDos(Uint8 *pbuf);
void FillFon(COLOR  _color);
void FillBar(int x, int y, int width, int height, COLOR _color);
void DrawRaw(FONT _font, COLOR DefColor);
void DrawBar(FONT _font, COLOR DefColor);
void DrawKey(FONT _font, COLOR DefColor);
void VisibleSetup(void);


#endif /* SETUP_RAWMAKE_H_ */
