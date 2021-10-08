/*
 * graphic.h
 *
 *  Created on: Mar 11, 2020
 *      Author: serg
 */

#ifndef MEDIA_H_
#define MEDIA_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "../global.h"
#include "rtext.h"

#define FONT_AMOUNT  5

class cMedia: public cRText{
public:

	cMedia(void);
	RET_STATE InitMedia(int width, int height);
	void CloseMedia(void);

	RET_STATE LoadFont(FONT _font);

	int GetWidth(void);
	int GetHeight(void);

	void FillRect(int x, int y, int width, int height, COLOR _color);
	void FillRect(SDL_Surface *surface, int x, int y, int width, int height, COLOR _color);

	void OutScreen(void);

	SDL_Surface* LoadImage(const char* filename);
	SDL_Surface* LoadImage(const char* filename, Uint8 r, Uint8 g, Uint8 b);
	SDL_Surface* LoadImageAlpha(const char* filename);
	void DrawImage(SDL_Surface* pImage, SDL_Rect* pImgPos, int x, int y);
	void DrawImage(SDL_Surface* pImage, SDL_Rect* pImgPos, SDL_Surface* pLayer, SDL_Rect* pLayerPos);
	void DrawImage(SDL_Surface* pImage, SDL_Rect* pImgPos,  SDL_Rect* pFonPos);

	void SetClipRect(SDL_Rect* pRect);

	void TTF_DrawText(SDL_Surface* surface, FONT _font, char* raw, int x, int y, COLOR _color);
	void TTF_DrawText(FONT _font, char *raw, int x, int y, COLOR _color );
	void TTF_DrawTextRich(FONT _font, char *raw, int x, int y, COLOR _color );
	int TTF_TextSize(FONT _font, char *raw, int *w, int *x);

private:

	SDL_Surface* BackBuffer;
	int WIDTH, HEIGHT;

	TTF_Font *Font[FONT_AMOUNT];

	Uint32 PrivateColor(SDL_Surface* surface, COLOR _color);

	SDL_Color CastColor(COLOR _color);
};


#endif /* MEDIA_H_ */
