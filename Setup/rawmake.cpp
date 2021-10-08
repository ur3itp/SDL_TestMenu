/*
 * boot.cpp
 *
 *  Created on: Mar 10, 2020
 *      Author: serg
 */

#include "rawmake.h"

extern cMedia oMedia;

tDosRaw sDosRaw;

int LoadFontDos(void){
	if(RET_OK != oMedia.LoadFont(FONT_SETUP_BIG) ||
			RET_OK != oMedia.LoadFont(FONT_SETUP_BASE))
		return 1;
	return 0;
}

int ConstrDos(void){
	int res = 0;
	int i, j;

	for(i = 0; i < 2; i++){
		for(j = 0; j < 3; j++ ){
			sDosRaw.Bar[i][j] = new unsigned char[50];
			if(NULL == sDosRaw.Bar[i][j]){
				res++;
			}
		}
	}
	for(i = 0; i < 3; i++){
		for(j = 0; j < 5; j++ ){
			sDosRaw.Key[i][j] = new unsigned char[20];
			if(NULL == sDosRaw.Key[i][j]){
				res++;
			}
		}
	}
	for(i = 0; i < RAW_MAX; i++){
		sDosRaw.Raw[i] = new unsigned char[RAW_SIGN];
			if(NULL == sDosRaw.Raw[i]){
				res++;
			}
	}
	return res;
}

void clearDos(void){
	int i, j;
	for( i =0; i < 2; i++){
		for( j = 0; j < 3; j++){
			sDosRaw.cntBar[i][j] = 0;
		}
	}
	for( i=0; i < 3; i++){
		for( j = 0; j < 5; j++){
			sDosRaw.cntKey[i][j] = 0;
		}
	}
	for( i = 0; i < RAW_MAX; i++){
		sDosRaw.cntRaw[i]  = 0;
	}
}

int SetLayer(Uint8 *pbuf){
	int i = 0;
	sDosRaw.Layer = pbuf[i++];
	return i;
}

int SetRaw(Uint8 *pbuf){
	int i = 0;
	int j, k;

	while(i < RAW_MAX ){
		sDosRaw.cntRaw[i] = pbuf[i];
		i++;
	}

	for( j = 0; j < RAW_MAX; j++){
		for( k = 0; k < sDosRaw.cntRaw[j]; k++){
			sDosRaw.Raw[j][k] = pbuf[i++];
		}
		sDosRaw.Raw[j][sDosRaw.cntRaw[j]] = 0;
	}
	return i;
}

int SetBar(Uint8 *pbuf){
	int pos = 0;
	int i, j, x;
	for( i = 0; i < 2; i++){
		for( j = 0; j < 3; j++){
			sDosRaw.cntBar[i][j] = pbuf[pos++];
		}
	}

	for( i = 0; i < 2; i++){
		for( j = 0; j < 3; j++){
			for( x = 0; x < sDosRaw.cntBar[i][j]; x++){
				sDosRaw.Bar[i][j][x] = pbuf[pos++];
			}
			sDosRaw.Bar[i][j][sDosRaw.cntBar[i][j]] = 0;
		}
	}
	return pos;
}

int SetKey(Uint8 *pbuf){
	int pos = 0;
	int i, j, x;
	for( i = 0; i < 3; i++){
		for( j = 0; j < 5; j++){
			sDosRaw.cntKey[i][j] = pbuf[pos++];
		}
	}

	for( i = 0; i < 3; i++){
		for( j = 0; j < 5; j++){
			for( x = 0; x < sDosRaw.cntKey[i][j]; x++){
				sDosRaw.Key[i][j][x] = pbuf[pos++];
			}
			sDosRaw.Key[i][j][sDosRaw.cntKey[i][j]] = 0;
		}
	}
	return pos;
}

int SetDos(Uint8 *pbuf){
	int shift ;
	shift =  SetLayer(pbuf);
	shift +=  SetRaw(&pbuf[shift]);
	shift += SetBar(&pbuf[shift]);
	shift += SetKey(&pbuf[shift]);
	return shift;
}

void FillFon(COLOR  _color){
	oMedia.FillRect(0, 0, oMedia.GetWidth(), oMedia.GetHeight(), _color);
}

void FillBar(int x, int y, int width, int height, COLOR _color){
	oMedia.FillRect(x, y, width, height, _color);
}

void DrawRaw(FONT _font, COLOR DefColor ){
	int x = RAW_XPOS;
	int y = RAW_YPOS;

	for(int i = 0; i < RAW_MAX; i++){
		if(sDosRaw.cntRaw[i] != 0){
			oMedia.TTF_DrawTextRich(_font,(char*)sDosRaw.Raw[i], x, (y + sFontFile[_font].ptrsize * i), DefColor);
//			printf("%s\n", (char*)sDosRaw.Raw[i]);
//			fflush(stdout);
		}
	}
}


void DrawKey(FONT _font, COLOR DefColor){
	int length;
	int x, y;
	const int x1 = 75;
	const int x2 = 235;
	const int x3 = 395;
	const int x4 = 555;
	const int x5 = 715;
	const int y1 = 544;
	const int y2 = 544 + 14;
	const int y3 = 544 + 28;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 5; j++){
			if(sDosRaw.Key[i][j] != 0){
				length = strlen((char*)sDosRaw.Key[i][j]);
				switch(i){
					case 0:	y = y1;	break;
					case 1:	y = y2;	break;
					case 2:	y = y3;	break;
				}
				switch(j){
					case 0:	x = x1; break;
					case 1:	x = x2; break;
					case 2:	x = x3; break;
					case 3:	x = x4; break;
					case 4:	x = x5; break;
				}
				x = x - length * 9/2;
				oMedia.TTF_DrawTextRich(_font,(char*)sDosRaw.Key[i][j], x, y, DefColor);
			}
		}
	}

}

void DrawBar(FONT _font, COLOR DefColor){
	int length;
	int x;
	const int x1 = 10;
	const int x2 = 400;
	const int x3 = 790;
	const int y1 = 5;
	const int y2 = 20;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 3; j++){
			if(sDosRaw.cntBar  != 0){
				length = strlen((char*)sDosRaw.Bar[i][j]);
				switch(j){
					case 0:		x = x1;					break;
					case 1:		x = x2 - length * 9/2;	break;
					case 2:		x = x3 - length *9;		break;
				}
				oMedia.TTF_DrawTextRich(_font,(char*)sDosRaw.Bar[i][j], x, (i==0) ? y1 : y2, DefColor);
			}
		}
	}
}

void VisibleSetup(void){
	oMedia.OutScreen();
}


