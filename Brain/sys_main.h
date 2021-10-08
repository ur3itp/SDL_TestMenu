/*
 * commander.h
 *
 *  Created on: Mar 14, 2020
 *      Author: lot
 */

#ifndef LOCALGAMECONTROLLER_COMMANDER_H_
#define LOCALGAMECONTROLLER_COMMANDER_H_

#include "sys_global.h"

//---------------link type data----------------------
#define SIZE_PIPE_RX  4096
#define SIZE_PIPE_TX  8192
typedef struct{
	Uint8 	*pBuf;
	Uint16 	Length;
	Uint32	Set;
	Uint32	Get;
}ts_RxPipeBuf;

typedef struct{
	Uint8 *pBuf;
	Uint16 Length;
	Uint32 Set;
	Uint32 Get;
}ts_TxPipeBuf;
//---------------------------------------------------

typedef struct{
	Uint8 MediaState;
	Uint8 Packet;
	Uint16 Delay;
}stRecvData;

int BrainInit(void);
Uint32 BrainUpdate(void);
void Loading(Uint32 _from, Uint32 _to);
int SetByteBuf(Uint8 cmd, int shift);
void SndSysBuf(Uint32 Length);

#endif /* LOCALGAMECONTROLLER_COMMANDER_H_ */
