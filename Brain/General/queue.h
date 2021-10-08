/*
 * queue.h
 *
 *  Created on: Mar 24, 2020
 *      Author: serg
 */

#ifndef BRAIN_TOOL_QUEUE_H_
#define BRAIN_TOOL_QUEUE_H_

#include "../sys_global.h"

#define QUEUE_MAX 8

void Sys_Queue_Clear(void);
void Sys_Queue_Clear(int i);
void Sys_Queue_AddFunc(pSfunc pf, int TimeOut);
void Sys_Queue_TestFunc(bool update);

#endif /* BRAIN_TOOL_QUEUE_H_ */
