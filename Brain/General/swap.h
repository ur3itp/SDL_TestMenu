/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SWAP_H
#define __SWAP_H

  /* Includes ------------------------------------------------------------------*/
#include "swap_vars.h"
	 
typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

//#define BASE_ADR_NVRAM					0x64000000
#define NVRAM_SIZE							128*1024
#define NVRAM_SIZE_PAGE				(NVRAM_SIZE / 2)
#define BASE_ADR_NVRAM_PAGE1		0
#define BASE_ADR_NVRAM_PAGE2	    NVRAM_SIZE_PAGE

#define MAX_RECORD_HISTORY			200
#define MAX_RECORD_EVENT				100
#define	MAX_AMOUNT_GAMES				20	 
	 
typedef enum {_eventMachine, _eventBill, _eventCoin, _eventRemotein, _eventHandpay, _eventJackpot} etagEvent; 	 

void saveFixedParams(void);
void saveSetupGames(tagSetupGames *setupGames, uint ngame);
void saveSystemParams(void);
void readSetupGames(tagSetupGames *setupGames, uint ngame);

void getEvent(etagEvent eventName, tagEvent *event, uint position);
void getHistory(tagHistory *history, uint position);
void getArrBets(ushort *pbet, uint game);
void getStatistic(tagStisticGame *statistic, uint position);
uint startUpNvramPage(void);
	
int TestBoardInit(void);

#endif /* __SWAP_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

