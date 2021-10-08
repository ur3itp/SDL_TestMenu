/*
 * commander.cpp
 *
 *  Created on: Mar 14, 2020
 *      Author: lot
 */

#include "sys_main.h"
#include "./HARDWARE/inout.h"
#include "./General/queue.h"
#include "./General/swap.h"
#include "./General/swap_vars.h"
#include "./Setup/startup.h"
#include "../control.h"
#include "./Setup/setup.h"
#include "./sMenu/s_menu.h"
#include "./Games/Game1/burning20.h"
#include "./Games/Game2/burning5.h"

Uint32 CurrentTime;
Uint32 TimeMs = 0;

pSfunc pPrgm[10] = {RunSetup, RunMenu, RunGame1, RunGame2};

ts_RxPipeBuf T_RxPipeBuf;
ts_TxPipeBuf T_TxPipeBuf;

stRecvData svRecvData;

void LinkReceive(Uint8 *pBuf, Uint16 Length);

// external call
void PipeReceive(Uint8 *pBuf, Uint16 Length){
	Uint16 i =0;
	while(i < Length){
		T_RxPipeBuf.pBuf[i] = pBuf[i];
		i++;
	}
	T_RxPipeBuf.Length = Length;
	T_RxPipeBuf.Set++;
}
void PipeSend(Uint8 *pBuf, Uint16 Length){
	LinkReceive(pBuf, Length);
}


void SndSysBuf(Uint32 Length){
	T_TxPipeBuf.Length = Length;
	T_TxPipeBuf.Set++;
}


int BrainInit(void){
	int res;
	StateNvRam = TestBoardInit();

	T_RxPipeBuf.pBuf = new Uint8[SIZE_PIPE_RX];
	T_TxPipeBuf.pBuf = new Uint8[SIZE_PIPE_TX];
	T_RxPipeBuf.Get = 0;
	T_RxPipeBuf.Set = 0;
	T_TxPipeBuf.Get = 0;
	T_TxPipeBuf.Set = 0;

	Sys_Queue_Clear();
	Sys_Queue_AddFunc(&startup, 0);

	res = SetupConstructor();

	MenuInit();

	return res;
}

void EventSend(bool tick){
	Uint8 cmd;
	static Uint8 TimeSend = 0;
	// 50 ms
	if(true == tick){
		TimeSend++;
		svRecvData.Delay++;
	}

	if(T_TxPipeBuf.Set > T_TxPipeBuf.Get){
		PipeSend(T_TxPipeBuf.pBuf, T_TxPipeBuf.Length);
		T_TxPipeBuf.Get++;
		svRecvData.Packet = CMD_DATA;
		svRecvData.Delay = 0;
		TimeSend = 0;
//			printf("send %d %d %d\n", T_TxPipeBuf.Set, T_TxPipeBuf.Get, T_TxPipeBuf.pBuf[0]);
//			fflush(stdout);
	}
	else{
		if(TimeSend >= 50){
			TimeSend = 0;
			cmd = CMD_SYNC;
			PipeSend(&cmd, sizeof(cmd));
			svRecvData.Packet = cmd;
			svRecvData.Delay = 0;
//				printf("send %d %d %d\n", T_TxPipeBuf.Set, T_TxPipeBuf.Get, cmd);
//				fflush(stdout);
		}
	}
}

void EventRecv(void){
	int x = 0;
	Uint8 ack;

	if(T_RxPipeBuf.Set > T_RxPipeBuf.Get){
		ack = T_RxPipeBuf.pBuf[x++];

		if(ack == CMD_ACK){
			svRecvData.MediaState = T_RxPipeBuf.pBuf[x++];
		}
		T_RxPipeBuf.Get++;
	}
}

Uint32  BrainUpdate(void){
	bool tick = false;
	CurrentTime = SDL_GetTicks();
	if(CurrentTime != TimeMs){
		tick = true;
		TimeMs = CurrentTime;
	}
	Sys_Queue_TestFunc(tick);
	EventSend(tick);
	EventRecv();
	ProgramIsRunning();
	return SIG_QUIT;
}

void Loading(Uint32 _from, Uint32 _to){

	static Uint32 _undo = 0;;

	if(_to != xxxNONE){
		_undo = _from;
	}

	switch(_from){
		case xxxSTARTUP :
			if(StateNvRam == 0){
				Sys_Queue_AddFunc(sMenu, 2000);
//				return;
			}
			if(StateNvRam ==  3 || StateNvRam == 4){
				Sys_Queue_AddFunc(WaitToSetup, 10);
//				return;
			}
			break;
		case xxxSETUP:
			if(NULL != pPrgm[_undo] && _undo < 11){
				Sys_Queue_AddFunc( pPrgm[_undo], 2);
			}
			break;
		case xxxMENU:
			if(NULL != pPrgm[_to] && _to < 12){
				Sys_Queue_AddFunc( pPrgm[_to], 2);
			}
			break;
	}

}

int SetByteBuf(Uint8 cmd, int shift){
	T_TxPipeBuf.pBuf[shift++] = cmd;
	return shift;
}


