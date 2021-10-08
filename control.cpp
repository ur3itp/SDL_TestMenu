/*
 * global.cpp
 *
 *  Created on: Feb 8, 2020
 *      Author: serg
 */

#include "control.h"
#include <SDL/SDL.h>

#include "./Setup/dosmode.h"
#include "./Menu/menu.h"
#include "./Games/games.h"
#include "./Games/BurningHot20/mgame1.h"
#include "./Games/BurningHot5/mgame2.h"

void PipeReceive(Uint8 *pBuf, Uint16 Length);

ts_RxLinkBuf T_RxLinkBuf;
ts_TxLinkBuf T_TxLinkBuf;

T_MGparam St_GameParam;
T_RXparam St_RXparam;

pMfunc pCurrentScene;

void LinkReceive(Uint8 *pBuf, Uint16 Length){
	Uint16 i =0;
	while(i < Length){
		T_RxLinkBuf.pBuf[i] = pBuf[i];
		i++;
	}
	T_RxLinkBuf.Length = Length;
	T_RxLinkBuf.Set++;
}
void LinkSend(Uint8 *pBuf, Uint16 Length){
	PipeReceive(pBuf, Length);
}

RET_STATE InitNet(void)
{
	T_RxLinkBuf.pBuf = new Uint8[SIZE_LINK_RX];
	T_TxLinkBuf.pBuf = new Uint8[SIZE_LINK_TX];
	if(T_RxLinkBuf.pBuf == NULL || T_TxLinkBuf.pBuf == NULL){
		return RET_ERROR;
	}
	T_TxLinkBuf.Set = 0;
	T_TxLinkBuf.Get = 0;
	T_RxLinkBuf.Get = 0;
	T_RxLinkBuf.Set = 0;

	pCurrentScene = NULL;
	return RET_OK;
}

void MediaUpdate (void) {

	Uint8 cmd;
	Uint8 syn[2];
	int shift = 0;


	if(T_RxLinkBuf.Set > T_RxLinkBuf.Get){

		cmd = T_RxLinkBuf.pBuf[shift++];

		syn[0] = CMD_ACK;
		syn[1] = MediaState;
		LinkSend(syn, sizeof(syn));
		T_RxLinkBuf.Get++;

		switch(cmd){
			case CMD_BOOT:
				parse_boot(&T_RxLinkBuf.pBuf[shift], T_RxLinkBuf.Length - shift);
				BootDos();
				break;
			case CMD_SETUP:
				parse_boot(&T_RxLinkBuf.pBuf[shift], T_RxLinkBuf.Length - shift);
				SetupDos();
				pCurrentScene = NULL;//SetupDos;
				break;
			case CMD_MENU:
				parse_menu(&T_RxLinkBuf.pBuf[shift], T_RxLinkBuf.Length - shift);
				uMenu();
				pCurrentScene = uMenu;
				break;
			case CMD_GAME1:
//				parse_game1(&T_RxLinkBuf.pBuf[x], T_RxLinkBuf.Length - x);
//				shift = parse_interface(T_RxLinkBuf.pBuf, shift);
//				MediaState = Game1();
//				pCurrentScene = Game1;
				break;
			case CMD_GAME2:
				shift = parse_game2(T_RxLinkBuf.pBuf, shift);
				MediaState = Game2();
				pCurrentScene = Game2;
				break;
			default:
				break;
		}
	}
	else{
		if(pCurrentScene != NULL){
			MediaState = pCurrentScene();
		}
	}
}


