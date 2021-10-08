/*
 * s_menu.h
 *
 *  Created on: Apr 24, 2020
 *      Author: serg
 */

#ifndef BRAIN_SMENU_S_MENU_H_
#define BRAIN_SMENU_S_MENU_H_

#include "../sys_global.h"

typedef struct{
	Uint8 maxPage;
	Uint8 curPage;
	Uint8 arr[10];
	Uint8 select;
	Uint8 lang;
	Uint16 denom;
	Uint32 Credit;
} stMenu;

void RunMenu(Uint8 irq);
void sMenu(Uint8 irq);
void MenuInit(void);
#endif /* BRAIN_SMENU_S_MENU_H_ */
