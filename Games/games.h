/*
 * games.h
 *
 *  Created on: May 1, 2020
 *      Author: serg
 */

#ifndef GAMES_GAMES_H_
#define GAMES_GAMES_H_

#include "../global.h"

#define IMFS_CMD_LOAD	0x02
#define IMFS_CMD_GOVER	0x04
#define IMFS_CMD_REEL	0x05
#define IMFS_CMD_SCORE	0x06

#define OMTS_RET_LOAD	0x06
#define OMTS_RET_INIT	0x07
#define OMTS_RET_OVER	0x08
#define	OMTS_RET_REEL	0x09
#define	OMTS_RET_SCORE	0x0A
#define OMTS_RET_TAKE	0x0B
#define OMTS_RET_DOUBLE	0x0C
#define OMTS_RET_HELP	0x0D
#define OMTS_RET_EXIT	0x5A

typedef struct{
	Uint8 	Lang;
	Uint16	Denom;
	Uint32	Credit;
	Uint16	Bet;
	Uint8	Lines;
}mtPanelInfo;
extern mtPanelInfo mvPanelInfo;

typedef enum {IDLE_ROLL, START_ROLL, SPEED_ROLL, SLOWLY_ROLL, SWAP_ROLL, STOP_ROLL, END_ROLL} mtEnumRoll ;

typedef struct{
	mtEnumRoll 		mvStateRoll;
	Sint16 			roll_shift;
	Uint16			roll_move;
	Uint8			roll_ix;
} mtRoll;

extern Uint8 LoadCounter;

int parse_interface(Uint8 *pbuf, int shift);
void draw_panel (int fix);

#endif /* GAMES_GAMES_H_ */
