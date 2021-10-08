/*
 * graphic.cpp
 *
 *  Created on: Mar 11, 2020
 *      Author: serg
 */

#include "media.h"

cMedia::cMedia(void){
	BackBuffer = NULL;
	for(int i =0; i < FONT_AMOUNT; i++){
		Font[i] = NULL;
	}
	HEIGHT = 0;
	WIDTH = 0;
}

RET_STATE cMedia::InitMedia(int width, int height){

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return RET_ERROR;
	WIDTH = width;
	HEIGHT = height;
	BackBuffer = SDL_SetVideoMode(WIDTH,HEIGHT,32, SDL_SWSURFACE); //SDL_DOUBLEBUF
	SDL_WM_SetCaption("Moving Image", NULL);

	if (TTF_Init() < 0)
		return RET_ERROR;

	return RET_OK;
}

void cMedia::CloseMedia(void){
	TTF_Quit();
	SDL_Quit();
}

RET_STATE cMedia::LoadFont(FONT _font){
	Font[_font] = TTF_OpenFont(sFontFile[_font].file, sFontFile[_font].ptrsize);
	if(Font[_font] == NULL){
		return RET_ERROR;
	}
	TTF_SetFontStyle(Font[_font], TTF_STYLE_BOLD);
	return RET_OK;
}

int cMedia::GetHeight(){
	return HEIGHT;
}
int cMedia::GetWidth(){
	return WIDTH;
}
void cMedia::OutScreen(){
	SDL_Flip(BackBuffer);
}
SDL_Surface* cMedia::LoadImage(const char* filename)
{
	SDL_Surface* imageLoaded = NULL;
	SDL_Surface* RetSurface = NULL;

	imageLoaded = IMG_Load(filename);

	if(imageLoaded == NULL)
	{
		return NULL;
	}

	RetSurface = SDL_DisplayFormat(imageLoaded);
	SDL_FreeSurface(imageLoaded);
	if(RetSurface == NULL)
	{
		return NULL;
	}
	return RetSurface;
}
SDL_Surface* cMedia::LoadImage(const char* filename, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* imageLoaded = NULL;
	SDL_Surface* RetSurface = NULL;

	imageLoaded = IMG_Load(filename);

	if(imageLoaded == NULL)
	{
		return NULL;
	}

	RetSurface = SDL_DisplayFormat(imageLoaded);
	SDL_FreeSurface(imageLoaded);
	if(RetSurface == NULL)
	{
		return NULL;
	}

	Uint32 colorKey = SDL_MapRGB(RetSurface->format, r, g, b);
	SDL_SetColorKey(RetSurface, SDL_SRCCOLORKEY, colorKey);

	return RetSurface;
}
SDL_Surface* cMedia::LoadImageAlpha(const char* filename)
{
	SDL_Surface* imageLoaded = NULL;
	SDL_Surface* RetSurface = NULL;

	imageLoaded = IMG_Load(filename);

	if(imageLoaded == NULL)
	{
		return NULL;
	}
	RetSurface = SDL_DisplayFormatAlpha(imageLoaded);
	SDL_FreeSurface(imageLoaded);
	if(RetSurface == NULL)
	{
		return NULL;
	}
	SDL_SetAlpha(RetSurface, SDL_SRCALPHA,0);

	return RetSurface;
}

void cMedia::DrawImage(SDL_Surface* pImage, SDL_Rect* pImgPos,  int x, int y){
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	SDL_BlitSurface(pImage, pImgPos, BackBuffer, &destRect);
}

void cMedia::DrawImage(SDL_Surface* pImage, SDL_Rect* pImgPos,  SDL_Rect* pFonPos){
	SDL_BlitSurface(pImage, pImgPos, BackBuffer, pFonPos);
}

void cMedia::DrawImage(SDL_Surface* pImage, SDL_Rect* pImgPos, SDL_Surface* pLayer, SDL_Rect* pLayerPos){
	SDL_BlitSurface(pImage, pImgPos, pLayer, pLayerPos);
}

void cMedia::SetClipRect(SDL_Rect* pRect){
	SDL_SetClipRect(BackBuffer, pRect);
}

// set color from format surface
Uint32 cMedia::PrivateColor(SDL_Surface *surface, COLOR _color){
	Uint8 r = ColorTable[_color][0];
	Uint8 g = ColorTable[_color][1];
	Uint8 b = ColorTable[_color][2];
	return SDL_MapRGB(surface->format, r, g, b );
}

void cMedia::FillRect(int x, int y, int width, int height, COLOR _color) {

	Uint32 color = PrivateColor(BackBuffer, _color);
	SDL_Rect rect;
	rect.x =  x;
	rect.y =  y;
	rect.w = width;
	rect.h = height;
	SDL_FillRect(BackBuffer, &rect, color);
}

void cMedia::FillRect(SDL_Surface *surface, int x, int y, int width, int height, COLOR _color) {

	Uint32 color = PrivateColor(surface, _color);
	SDL_Rect rect;
	rect.x =  x;
	rect.y =  y;
	rect.w = width;
	rect.h = height;
	SDL_FillRect(surface, &rect, color);
}

SDL_Color cMedia::CastColor(COLOR _color){
	SDL_Color color;
	color.r = ColorTable[_color][0];
	color.g = ColorTable[_color][1];
	color.b = ColorTable[_color][2];
	return color;
}

void cMedia::TTF_DrawText(SDL_Surface *surface, FONT _font, char *raw, int x, int y, COLOR _color ){

	SDL_Surface *renderText;
	SDL_Color color;
	SDL_Rect pos;

	color = CastColor(_color);

	// check in stock font
	if(NULL == Font[_font]){
		printf("font unable");
		return;
	}
	// check in stock end escape
	if(!chend_raw(raw, RAW_SIGN)){
		sprintf(raw, " raw donot have end");
	}

//	renderText = TTF_RenderText_Solid(Font[_font], raw , color);
	renderText = TTF_RenderText_Blended(Font[_font], raw , color);

	pos.x = x;
	pos.y = y;

	SDL_BlitSurface(renderText, NULL, surface, &pos);
	SDL_FreeSurface(renderText);

}

void cMedia::TTF_DrawText(FONT _font, char *raw, int x, int y, COLOR _color ){

	SDL_Surface *renderText;
	SDL_Color color;
	SDL_Rect pos;

	color = CastColor(_color);

	// check in stock font
	if(NULL == Font[_font]){
		printf("font unable");
		return;
	}
	// check in stock end escape
	if(!chend_raw(raw, RAW_SIGN)){
		sprintf(raw, " raw donot have end");
	}

//	TTF_SetFontStyle(Font[_font], TTF_STYLE_NORMAL);

//	renderText = TTF_RenderText_Solid(Font[_font], raw , color);
	renderText = TTF_RenderText_Blended(Font[_font], raw , color);

	pos.x = x;
	pos.y = y;

	SDL_BlitSurface(renderText, NULL, BackBuffer, &pos);
	SDL_FreeSurface(renderText);

}

void cMedia::TTF_DrawTextRich(FONT _font, char *raw, int x, int y, COLOR _color ){

	SDL_Surface *renderText;
	SDL_Color color, tcolor;
	SDL_Rect pos;

	Uint8 ixcolor;
	Uint8 i;
	char *tstra, *tstrb;
	char arrc[RAW_SIGN];

	color = CastColor(_color);
	tcolor = color;
	//memset(arrc, 0, sizeof(arrc));

	if(NULL == Font[_font]){
		printf("font unable");
		return;
	}
	// check in stock end escape
	if(!chend_raw(raw, RAW_SIGN)){
		sprintf(arrc, " raw donot have end");
		raw[RAW_SIGN -1] = 0;
	}

	ixcolor = 0;
	tstra = raw;
	pos.y = y;
	pos.x = x ;

	while(1){
		do{
			tstrb = strstr(tstra, modOpenColor[ixcolor]);
			if(NULL != tstrb){
				break;
			}
		}while(++ixcolor < MAX_COLOR);

		i = 0;
		if(tstrb == NULL){
			strcpy(arrc, tstra);
		} else {
			color = CastColor((COLOR) ixcolor);
			while(tstra < tstrb){
				arrc[i++] = *tstra++;
			}
			arrc[i] = '\0';
		}

		renderText = TTF_RenderText_Blended(Font[_font], arrc , tcolor);
//		renderText = TTF_RenderText_Solid(Font[_font], arrc , tcolor);

		SDL_BlitSurface(renderText, NULL, BackBuffer, &pos);
		SDL_FreeSurface(renderText);
		pos.x += i * 9;

		if(tstrb == NULL){
			return;
		}

		tstrb += strlen(modOpenColor[ixcolor]);
		tstra = tstrb;
		tstrb = strstr(tstra, modCloseColor);

		if(tstrb == NULL){
			return;
		}

		i=0;
		while(tstra < tstrb){
			arrc[i++] = *tstra++;
		}
		arrc[i] = '\0';

//		renderText = TTF_RenderText_Solid(Font[_font], arrc , color);
		renderText = TTF_RenderText_Blended(Font[_font], arrc , color);

		SDL_BlitSurface(renderText, NULL, BackBuffer, &pos);
		SDL_FreeSurface(renderText);

		pos.x += i * 9;
		tstrb += strlen(modCloseColor);
		tstra = tstrb;
	}
}

int cMedia::TTF_TextSize(FONT _font, char *raw, int *w, int *h){
	return TTF_SizeText(Font[_font], raw, w, h);
}
