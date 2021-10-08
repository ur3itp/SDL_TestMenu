/*
 * menu.h
 *
 *  Created on: Apr 24, 2020
 *      Author: serg
 */

#ifndef MENU_MENU_H_
#define MENU_MENU_H_

#include "../global.h"

#define ICON_WIDTH 150
#define ICON_HEIGHT 90

typedef struct{
	Uint8 maxPage;
	Uint8 curPage;
	Uint8 arr[10];
	Uint8 select;
	Uint8 lang;
	Uint16 denom;
	Uint32 Credit;
} mtMenu;

RET_STATE InitMenu(void);

void parse_menu(Uint8 *pBuf, Uint16 Length);
Uint32 uMenu(void);

#endif /* MENU_MENU_H_ */
