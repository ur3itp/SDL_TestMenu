/*
 * dosmode.h
 *
 *  Created on: Mar 12, 2020
 *      Author: lot
 */

#ifndef SETUP_DOSMODE_H_
#define SETUP_DOSMODE_H_

#include "../global.h"
#include "rawmake.h"

RET_STATE InitSetup(void);

void parse_boot(Uint8 *pBuf, Uint16 Length);
void controlDos(Uint8 *pBuf);
void BootDos(void);
void SetupDos(void);

#endif /* SETUP_DOSMODE_H_ */
