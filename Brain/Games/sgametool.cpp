/*
 * sgametool.cpp
 *
 *  Created on: May 6, 2020
 *      Author: serg
 */

#include "sgametool.h"

#include "../General/swap_vars.h"
#include "../sys_main.h"

extern ts_TxPipeBuf T_TxPipeBuf;

stPanelInfo svPanelInfo;

void updatePanelInfo(void){
	svPanelInfo.Credit  = swp_GlobalParams.Credit;
	svPanelInfo.Denom	= swp_GlobalParams.CurrentDenom;
	svPanelInfo.Lang	= swp_GlobalParams.Language;
	svPanelInfo.Bet		= swp_GameParams.currentBet;
	svPanelInfo.Lines 	= swp_GameParams.currentLine;
}

int SetPanelBuf(int shift){

	Uint8 *p = (Uint8*)&svPanelInfo;

	for(uint i = 0; i < sizeof(stPanelInfo); i++){
		T_TxPipeBuf.pBuf[shift++] = p[i];
	}
	return shift;
}

int SetSymbBuf(Uint8 *pbuf, int size, int shift){
	for(uint i = 0; i < size; i++){
		T_TxPipeBuf.pBuf[shift++] = pbuf[i];
	}
	return shift;
}
