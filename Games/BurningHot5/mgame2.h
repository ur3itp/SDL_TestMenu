/*
 * mgame2.h
 *
 *  Created on: May 5, 2020
 *      Author: serg
 */

#ifndef GAMES_BURNINGHOT5_MGAME2_H_
#define GAMES_BURNINGHOT5_MGAME2_H_

#include "../../global.h"
#include "../games.h"

#define SIZE_SYMBOL	143

int parse_game2(Uint8 *pBuf, int Length);
Uint32 Load_Game2(void);
Uint32 Game2(void);



#endif /* GAMES_BURNINGHOT5_MGAME2_H_ */
