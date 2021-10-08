/*
 * s_menu.cpp
 *
 *  Created on: Apr 24, 2020
 *      Author: serg
 */

#include "../sMenu/s_menu.h"

#include "../sys_main.h"
#include "../General/swap_vars.h"
#include "../General/queue.h"
#include "../General/utility.h"
#include "../HARDWARE/inout.h"

extern ts_TxPipeBuf T_TxPipeBuf;

stMenu svMenu;

Uint8 CurrentPage = 0;
Uint8 SelectGame = 0;

void MenuInit(){
	svMenu.Credit 	= swp_GlobalParams.Credit;
	svMenu.denom 	= swp_GlobalParams.CurrentDenom;
	svMenu.lang 	= swp_GlobalParams.Language;

	for(int i = 0; i < 10; i++){
		svMenu.arr[i] = swp_FixedParams.GameList[CurrentPage * 10 + i];
	}

}

int SetMenuBuf(int shift){

	Uint8 *p = (Uint8*)&svMenu;
	for(uint i = 0; i < sizeof(stMenu); i++){
		T_TxPipeBuf.pBuf[shift++] = p[i];
	}
	return shift;
}

void RunMenu(Uint8 irq){
	Sys_Queue_Clear(irq);
	Sys_Queue_AddFunc(sMenu, 20);
}

void sMenu(Uint8 irq){
	int shift;
	Uint32 code;
	Uint32 temp;
	static Uint32 chsum = 0;

	code = getKeyCode();

	Sys_Queue_Clear(irq);

	if(code == 'S'){
		Loading(xxxMENU, xxxSETUP);
		return;
	}

	if(code == 'D'){
		switch(svMenu.select){
			case 0:		break;
			case 1:		break;
			case 2:		Loading(xxxMENU, xxxGame2);		break;
			case 3:		Loading(xxxMENU, xxxGame1);		break;
			case 4:		break;
			case 5:		break;
			case 6:		break;
			case 7:		break;
			case 8:		break;
			case 9:		break;
		}
		return;
	}

	MenuInit();

	if(code == '1' ){
		svMenu.select++;
		svMenu.select = svMenu.select % 10;
	}

	shift = SetByteBuf(CMD_MENU, 0);
	shift = SetMenuBuf(shift);
	temp = sumarr(T_TxPipeBuf.pBuf, shift);
	if(chsum != temp){
		SndSysBuf(shift);
		chsum = temp;
	}

	Sys_Queue_AddFunc(sMenu, 20);
}

