/*
 * burning20.cpp
 *
 *  Created on: May 1, 2020
 *      Author: serg
 */

#include "burning20.h"
#include "../sgametool.h"

#include "../../sys_main.h"
#include "../../General/swap_vars.h"
#include "../../General/queue.h"
#include "../../HARDWARE/inout.h"

void GameOver1(Uint8 irq);

extern stRecvData svRecvData;
//extern ts_TxPipeBuf T_TxPipeBuf;

Uint8 sCurSymbArrGame1[5][3];

void ReelGame1(Uint8 irq){
	int shift = 0;
	Sys_Queue_Clear(irq);

	if(svRecvData.MediaState == ISFM_RET_TAKE){
		Sys_Queue_AddFunc(GameOver1, 2);
		return;
	}
	updatePanelInfo();

	shift = SetByteBuf(CMD_GAME1, shift);
	shift = SetByteBuf(OSTM_CMD_REEL, shift);
	shift = SetPanelBuf(shift);
	shift = SetSymbBuf((Uint8*)sCurSymbArrGame1, 15, shift);

	SndSysBuf(shift);
	Sys_Queue_AddFunc(ReelGame1, 20);
}

void GameOver1(Uint8 irq){
	int shift = 0;
	Uint32 code;

	Sys_Queue_Clear(irq);

	code = code = getKeyCode();

	if(code == 'E'){
		Sys_Queue_AddFunc(ReelGame1, 2);
		return;
	}

	updatePanelInfo();

	shift = SetByteBuf(CMD_GAME1, shift);
	shift = SetByteBuf(OSTM_CMD_GOVER, shift);
	shift = SetPanelBuf(shift);
	shift = SetSymbBuf((Uint8*)sCurSymbArrGame1, 15, shift);

	SndSysBuf(shift);
	Sys_Queue_AddFunc(GameOver1, 20);
}

void WaitLoadGame1(Uint8 irq){
	Sys_Queue_Clear(irq);

	if(svRecvData.MediaState == ISFM_RET_INIT){
		Sys_Queue_AddFunc(GameOver1, 2);
		return;
	}
	Sys_Queue_AddFunc(WaitLoadGame1, 20);
}

void RunGame1 (Uint8 irq){
	int shift = 0;

	Sys_Queue_Clear(irq);

	swp_GameParams.currentLine = 5;
	swp_GameParams.currentBet = 10;

	sCurSymbArrGame1[0][2] = 7;

	shift = SetByteBuf(CMD_GAME1, shift);
	shift = SetByteBuf(OSTM_CMD_LOAD, shift);
	SndSysBuf(shift);

	printf("run g1\n");
	fflush(stdout);

	Sys_Queue_AddFunc(WaitLoadGame1, 20);
}



