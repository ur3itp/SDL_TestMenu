/*
 * game1.h
 *
 *  Created on: May 1, 2020
 *      Author: serg
 */

#ifndef GAMES_BURNINGHOT20_MGAME1_H_
#define GAMES_BURNINGHOT20_MGAME1_H_

#include "../../global.h"
#include "../games.h"

void parse_game1(Uint8 *pBuf, Uint16 Length);
Uint32 Load_Game1(void);
Uint32 Game1(void);

#endif /* GAMES_BURNINGHOT20_MGAME1_H_ */
