/*
 * inout.h
 *
 *  Created on: Apr 18, 2020
 *      Author: lot
 */

#ifndef BRAIN_HARDWARE_INOUT_H_
#define BRAIN_HARDWARE_INOUT_H_

#include"../sys_global.h"

extern	Uint8 PIN_HOLD1;
extern	Uint8 PIN_HOLD2;
extern	Uint8 PIN_HOLD3;
extern	Uint8 PIN_HOLD4;
extern	Uint8 PIN_HOLD5;
extern 	Uint8 SIG_QUIT;

Uint32 getKeyCode(void);
void ProgramIsRunning(void);

#endif /* BRAIN_HARDWARE_INOUT_H_ */
