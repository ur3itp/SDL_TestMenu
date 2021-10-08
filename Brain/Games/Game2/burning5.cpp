/*
 * burning5.cpp
 *
 *  Created on: May 5, 2020
 *      Author: serg
 */

#include "burning5.h"
#include "../sgametool.h"

#include "../../sys_main.h"
#include "../../General/swap_vars.h"
#include "../../General/queue.h"
#include "../../HARDWARE/inout.h"

void GameOver2(Uint8 irq);

extern stRecvData svRecvData;
//extern ts_TxPipeBuf T_TxPipeBuf;

Uint8 sCurSymbArrGame2[5][3];

void ProcScore2(Uint8 irq){
	int shift = 0;
	Sys_Queue_Clear(irq);

	if(svRecvData.MediaState == ISFM_RET_GOVER){
		Sys_Queue_AddFunc(GameOver2, 20);
		return;
	}
	updatePanelInfo();

	shift = SetByteBuf(CMD_GAME2, shift);
	shift = SetByteBuf(OSTM_CMD_SCORE, shift);
	shift = SetPanelBuf(shift);
	shift = SetSymbBuf((Uint8*)sCurSymbArrGame2, 15, shift);

	SndSysBuf(shift);

	Sys_Queue_AddFunc(ProcScore2, 20);
}

void ReelGame2(Uint8 irq){
	int shift = 0;
	Sys_Queue_Clear(irq);

	if(svRecvData.MediaState == ISFM_RET_SCORE){
		Sys_Queue_AddFunc(ProcScore2, 20);
		return;
	}

	updatePanelInfo();

	shift = SetByteBuf(CMD_GAME2, shift);
	shift = SetByteBuf(OSTM_CMD_REEL, shift);
	shift = SetPanelBuf(shift);
	shift = SetSymbBuf((Uint8*)sCurSymbArrGame2, 15, shift);

	SndSysBuf(shift);
	Sys_Queue_AddFunc(ReelGame2, 20);
}

void SetSymbol2(Uint8 irq){
	Sys_Queue_Clear(irq);
	for(int i =0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			sCurSymbArrGame2[i][j] = rand()%11;
		}
	}
	Sys_Queue_AddFunc(ReelGame2, 2);
}

void GameOver2(Uint8 irq){
	int shift = 0;
	Uint32 code;

	Sys_Queue_Clear(irq);

	code = getKeyCode();

	if(code == 'E'){
		Sys_Queue_AddFunc(SetSymbol2, 2);
		return;
	}

	updatePanelInfo();

	shift = SetByteBuf(CMD_GAME2, shift);
	shift = SetByteBuf(OSTM_CMD_GOVER, shift);
	shift = SetPanelBuf(shift);
	shift = SetSymbBuf((Uint8*)sCurSymbArrGame2, 15, shift);

	SndSysBuf(shift);
	Sys_Queue_AddFunc(GameOver2, 20);
}

void WaitLoadGame2(Uint8 irq){
	Sys_Queue_Clear(irq);

	if(svRecvData.MediaState == ISFM_RET_INIT){
		Sys_Queue_AddFunc(GameOver2, 2);
		return;
	}
	Sys_Queue_AddFunc(WaitLoadGame2, 20);
}

void RunGame2 (Uint8 irq){
	int shift = 0;

	Sys_Queue_Clear(irq);

	swp_GameParams.currentLine = 5;
	swp_GameParams.currentBet = 10;

	sCurSymbArrGame2[0][2] = 7;

	shift = SetByteBuf(CMD_GAME2, shift);
	shift = SetByteBuf(OSTM_CMD_LOAD, shift);
	SndSysBuf(shift);

	printf("run g1\n");
	fflush(stdout);

	Sys_Queue_AddFunc(WaitLoadGame2, 20);
}



