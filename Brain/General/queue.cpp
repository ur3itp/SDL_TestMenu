/*
 * queue.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: serg
 */

#include "queue.h"

static struct{
	pSfunc pFuncQueue;
	Uint32 Delay;
}sArrayQueue[QUEUE_MAX];

void Sys_Queue_Clear(void){
	int i = 0;
	while(i < QUEUE_MAX){
		sArrayQueue[i].pFuncQueue = NULL;
		sArrayQueue[i].Delay = 0;
		i++;
	}
}

void Sys_Queue_Clear(int i){
	sArrayQueue[i].pFuncQueue = NULL;
	sArrayQueue[i].Delay = 0;
}

void Sys_Queue_AddFunc(pSfunc pf, int TimeOut){
	int i = 0;
	while(i < QUEUE_MAX){
		if(sArrayQueue[i].pFuncQueue == NULL){
			sArrayQueue[i].pFuncQueue = pf;
			sArrayQueue[i].Delay = TimeOut;
			break;
		}
		i++;
	}
	if(i == QUEUE_MAX){
		printf("queue cnt error!");
		fflush(stdout);
	}
}

void Sys_Queue_TestFunc(bool update){
	int i =0;
	while(i < QUEUE_MAX){
		if(sArrayQueue[i].Delay > 0 && update){
			sArrayQueue[i].Delay--;
		}
		if(sArrayQueue[i].pFuncQueue != NULL && sArrayQueue[i].Delay == 0){
			sArrayQueue[i].pFuncQueue(i);
			break;
		}
		i++;
	}
}
