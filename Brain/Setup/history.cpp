/**
  ******************************************************************************
  * File Name          : history.c
  * Description        : setup history
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../General/utility.h"
#include "history.h"
#include "setup.h"
#include "../General/swap.h"

const char tGame[] = "GAME HISTORY > ";
const char tGame0[] = "No Game";
const char tGame1[] = "Game1";
const char tGame2[] = "Game2";
const char tGame3[] = "Game3";
const char tGame4[] = "Game4";
const char *pTGame[] = {tGame0, tGame1, tGame2, tGame3, tGame4};


static byte historyPage=1;																	
static byte maxPage;

void HistoryInit(void){
	historyPage=1;
}

static void historyBar(byte name){
//	memset(tBar, 0, sizeof(tBar));
	sprintf((char*)SetupForm.tBar[1][0], "%s%s", tGame, pTGame[name]);
	sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",historyPage, maxPage);
}

static void historyKey(){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
		if(maxPage > 1){
			sprintf((char*)SetupForm.tKey[1][3],"Past");
			sprintf((char*)SetupForm.tKey[1][4],"Future");
		} else {
//			sprintf((char*)SetupForm.tKey[1][3],"");
//			sprintf((char*)SetupForm.tKey[1][4],"");
		}
}


void histotyButton(uint code){
	
	if(code == 1){
		eAudit = _audit;
		historyPage = 1;		
	}

	if(code == 4){
			historyPage--;					
			if(historyPage == 0){
				historyPage = maxPage;		
			}
	}
	if(code == 5){
			historyPage++;
			if(historyPage > maxPage){
				historyPage = 1;
			}
	}
}

void historyUpdate(){
	tagHistory history;	
	char ss[100];
		
	getHistory(&history, swp_Position.historyPage);
	maxPage = (history.status == 0) ? swp_Position.historyPage : 200;	

	byte pos = swp_Position.historyPage ;
	byte page = historyPage;

//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	if((pos == 0 && maxPage == 0)){	
			addstr((char*)SetupForm.tRaw[3], "History has no records", 40, CENTERE);
			historyBar(0);
			historyKey();
			return;
	}
	while(page--){
		if(pos == 0)
				pos = 200;
		pos --;			
	}
	
	getHistory(&history, pos);
	historyBar(history.name);
	historyKey();
	
	sprintf((char*)SetupForm.tRaw[3], "Game 						  %d", history.name);
	sprintf((char*)SetupForm.tRaw[4], "Phase		      		%d / %d", history.maxPhase, history.curPhase);

	getStrDate(ss, sizeof(ss), &history.datetime);
	sprintf((char*)SetupForm.tRaw[6], "Date 		    %s", ss);
	getStrTime(ss, sizeof(ss), &history.datetime);
	sprintf((char*)SetupForm.tRaw[7], "Time 		   %s", ss);
	
	sprintf((char*)SetupForm.tRaw[9],"Credit bef. 	          %d", history.credit);
	sprintf((char*)SetupForm.tRaw[10],"Bet 	                %d", history.bet);
	sprintf((char*)SetupForm.tRaw[11],"Win 	                %d", history.win);
	sprintf((char*)SetupForm.tRaw[12],"TWin 	                %d", history.twin);

	sprintf((char*)SetupForm.tRaw[14],"Gambles 		          %d", history.gambles);
	sprintf((char*)SetupForm.tRaw[15],"Gamble in		          %d", history.gamblIn);
	sprintf((char*)SetupForm.tRaw[16],"Gamble out	          %d", history.gamblOut);
	
	sprintf((char*)SetupForm.tRaw[18], "SINCE LAST GAME");
	sprintf((char*)SetupForm.tRaw[19],"Coin in	            	%d", history.coinIn);
	sprintf((char*)SetupForm.tRaw[20],"Bill in		            %d", history.billIn);
	sprintf((char*)SetupForm.tRaw[21],"Remote in	            %d", history.remoteIn);

	sprintf((char*)SetupForm.tRaw[24],"Collected		          %d", history.collect);
}

