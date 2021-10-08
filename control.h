/*
 * global.h
 *
 *  Created on: Feb 8, 2020
 *      Author: serg
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "global.h"

typedef enum{
	MG_INIT = 0,
	MG_GAMEOVER,
	MG_INGAME,
	MG_INDOUBLE
}E_MGstate;
typedef enum{
	MG_BUSY = 0,
	MG_READY,
}E_MGstatus;

typedef struct{
	Uint8 	State;
	Uint8 	Game;
	Uint32 	Credit;
	Uint8	Exten;
	void 	*pExten;
}T_RXparam;

typedef struct{
	Uint16 	Bet;
	Uint8 	Line;
	Uint8	Exten;
	void	*pExten;
}T_OverGame;


typedef struct{
	Uint8 State;
	Uint8 Status;
	Uint8 Game;
	Uint8 Exten;
}T_MGparam;

//---------------link type data----------------------
#define SIZE_LINK_RX	8192
#define SIZE_LINK_TX 	4096
typedef struct{
	Uint8 	*pBuf;
	Uint16 	Length;
	Uint32	Set;
	Uint32	Get;
}ts_RxLinkBuf;

typedef struct{
	Uint8 *pBuf;
	Uint16 Length;
	Uint32	Set;
	Uint32	Get;
}ts_TxLinkBuf;
//---------------------------------------------------
RET_STATE InitNet(void);
void MediaUpdate (void);

#endif /* CONTROL_H_ */
