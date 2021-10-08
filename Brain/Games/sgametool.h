/*
 * sgametool.h
 *
 *  Created on: May 6, 2020
 *      Author: serg
 */

#ifndef BRAIN_GAMES_SGAMETOOL_H_
#define BRAIN_GAMES_SGAMETOOL_H_

#include "../sys_global.h"

typedef struct{
	Uint8 	Lang;
	Uint16	Denom;
	Uint32	Credit;
	Uint16	Bet;
	Uint8	Lines;
}stPanelInfo;

#define OSTM_CMD_LOAD	0x02
#define OSTM_CMD_GOVER	0x04
#define OSTM_CMD_REEL	0x05
#define OSTM_CMD_SCORE	0x06


#define ISFM_RET_LOAD	0x06
#define ISFM_RET_INIT	0x07
#define ISFM_RET_GOVER	0x08
#define	ISFM_RET_REEL	0x09
#define	ISFM_RET_SCORE	0x0A
#define ISFM_RET_TAKE	0x0B
#define ISFM_RET_DOUBLE	0x0C
#define ISFM_RET_HELP	0x0D
#define ISFM_RET_EXIT	0x5A

extern stPanelInfo svPanelInfo;


void updatePanelInfo(void);
int SetPanelBuf(int shift);
int SetSymbBuf(Uint8 *pbuf, int size, int shift);

#endif /* BRAIN_GAMES_SGAMETOOL_H_ */
