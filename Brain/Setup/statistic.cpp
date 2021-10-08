/**
  ******************************************************************************
  * File Name          : statistic.c
  * Description        : setup statistic log
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../General/utility.h"
#include "setup.h"
#include "../General/swap_vars.h"
#include "../General/swap.h"
#include "statistic.h"

const char tBarStatistic[]  =   "GAME STATISTIC > ";
const char tNameTotal[] = 	"TOTAL";

const char tLabel1[] = "Statistics";
const char tLabel2[] = "Total";
const char tLabel3[] = "For Bet";

static byte statPage=1;																	
static byte maxPage;

static void statisticBar(){

//	memset(tBar, 0, sizeof(tBar));
	switch(eStatistic){
		case _stat_total:	
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarStatistic, tNameTotal);
			sprintf((char*)SetupForm.tBar[1][1],"Page %d/%d",statPage, maxPage);
			break;
	 default:
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarStatistic, DescriptGame[NumberGame].pNameGame);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",statPage, maxPage);
			break;
	}
}

static void statisticKey(){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf(tKey[1],"");
//		sprintf(tKey[2],"");
		if(maxPage > 1){
			sprintf((char*)SetupForm.tKey[1][3],"Prev Page");
			sprintf((char*)SetupForm.tKey[1][4],"Next Page");
		} else {
//			sprintf(tKey[3],"");
//			sprintf(tKey[4],"");
		}
}

static void updatePage(uint code){
	if(code == 4){
			statPage --;
			if(statPage == 0){
				statPage = maxPage;		
			}
		}
		if(code == 5){
			statPage++;
			if(statPage > maxPage){
				statPage = 1;
			}
		}
}

void statisticButton(uint code){
	ushort bets[15];	
	if(code == 1){
		if(NumberGame < 10){
			eAudit = _statistic1;		
		} else {
			eAudit = _statistic2;		
		}
		statPage = 1;		
	}
	switch(eStatistic){
		case _stat_total:
			maxPage = 2;//sizeof(swp_stisticGame) / sizeof(stisticGame);
			updatePage(code);
			break;
		default:
			getArrBets(bets, NumberGame); 
			maxPage = 1 + bets[0]; // bet[0] - amount element in array
			updatePage(code);
			break;	
	}
}

void updateStatTotal(){
	tagStisticGame statistic;
	char ss[100];
	uint count, index;
	uint procent;
	statisticBar();
	statisticKey();
//	memset(tRaw, 0, sizeof(tRaw));
	
	sprintf((char*)SetupForm.tRaw[2], "GAME");
	addstr((char*)SetupForm.tRaw[2], "BET", 32, LEFT);
	addstr((char*)SetupForm.tRaw[2], "%", 38, LEFT);
	addstr((char*)SetupForm.tRaw[2], "WIN", 53, LEFT);
	addstr((char*)SetupForm.tRaw[2], "%", 59, LEFT);
	addstr((char*)SetupForm.tRaw[2], "GAMES PLAYED", 74, LEFT);
	addstr((char*)SetupForm.tRaw[2], "%", 80, LEFT);

	memset(ss, 0, sizeof(ss));
	for(int i=0; i<80; i++)
		ss[i]='-';
	sprintf((char*)SetupForm.tRaw[3], "%s", ss);
	
	if(statPage == 1){
		count = 15;
		index = 0;
	} else {
		count = 5;
		index = 15;	
	}

	for(uint i=0; i < count; i++){
			getStatistic(&statistic, index);

			sprintf((char*)SetupForm.tRaw[4+i], "%s", DescriptGame[index].pNameGame);
			formatCredit(statistic.TBetGame, ss);
			printf("point1 = %d\n", swp_RootParams.TotalBet);
			fflush(stdout);

			addstr((char*)SetupForm.tRaw[4+i], ss, 32, LEFT);
			procent = (statistic.TBetGame * 100) / swp_RootParams.TotalBet;
			printf("point2\n");
			fflush(stdout);

			formatMoney(procent, ss);

			printf("point3\n");
			fflush(stdout);

			addstr((char*)SetupForm.tRaw[4+i], ss, 39, LEFT);
			formatCredit(statistic.TWinGame, ss);
			addstr((char*)SetupForm.tRaw[4+i], ss, 53, LEFT);
			procent = (statistic.TWinGame * 100) / swp_RootParams.TotalWon;
			formatMoney(procent, ss);
			addstr((char*)SetupForm.tRaw[4+i], ss, 60, LEFT);
			formatCredit(statistic.TCntGame, ss);
			addstr((char*)SetupForm.tRaw[4+i], ss, 74, LEFT);
			procent = (statistic.TCntGame * 100) / swp_RootParams.TotalGames;
			formatMoney(procent, ss);
			addstr((char*)SetupForm.tRaw[4+i], ss, 81, LEFT);
		  index++;
	}		
}

void updateStatGame(){
	tagStisticGame statistic;		
	char ss[100];
	char st[100];
	uint procent;
	uint j =0;
	
	uint AnyWin =0, NoWin =0, ScatterWin =0;
	uint LineGame[5] ={0};
	uint TotalLinesGames =0;
	uint procLinePlay[5];
	uint GamePlay =0, GameBet =0, GameWon =0;
	uint procGame;
	uint GamblPlay =0, GamblIn =0, GamblOut =0, GamblAll =0;
	uint procYield; 
	
	statisticBar();
	statisticKey();
//	memset(tRaw, 0, sizeof(tRaw));

	getStatistic(&statistic, NumberGame);
	if(statPage == 1){	
		sprintf((char*)SetupForm.tRaw[2], "Denom");
		addstr((char*)SetupForm.tRaw[2], "B/L", 11, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Games", 22, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Total bet", 38, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Total Win", 54, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Theo%", 61, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Actua%", 68, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Bet%", 74, LEFT);
		addstr((char*)SetupForm.tRaw[2], "Win%", 80, LEFT);
	
		memset(ss, 0, sizeof(ss));
		for(int i=0; i<80; i++)
			ss[i]='-';
		sprintf((char*)SetupForm.tRaw[3], "%s", ss);
	
		sprintf((char*)SetupForm.tRaw[4], "Total");
		formatCredit(statistic.TCntGame, ss);
		addstr((char*)SetupForm.tRaw[4], ss, 22, LEFT);
		formatCredit(statistic.TBetGame, ss);
		addstr((char*)SetupForm.tRaw[4], ss, 38, LEFT);
		formatCredit(statistic.TWinGame, ss);
		addstr((char*)SetupForm.tRaw[4], ss, 54, LEFT);
		procent = (statistic.TWinGame * 10000) / statistic.TBetGame;
		formatMoney(procent, ss);
		addstr((char*)SetupForm.tRaw[4], ss, 68, LEFT);

		memset(ss, 0, sizeof(ss));
		for(int i=0; i<80; i++)
			ss[i]='-';
		sprintf((char*)SetupForm.tRaw[5], "%s", ss);
	
		for(int i=0; i < DescriptGame[NumberGame].pBetSeries[0] - 1; i++ ){	
			formatMoney(swp_FixedParams.fixMoneyDenom ,ss);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 5, LEFT);
			sprintf(ss,"%d", DescriptGame[NumberGame].pBetSeries[i+1]);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 11, LEFT);
			sprintf(ss, "%d", statistic.ArrCntGame[i]);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 22, LEFT);
			sprintf(ss, "%d", statistic.ArrBetGame[i]);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 38, LEFT);
			sprintf(ss, "%d", statistic.ArrWinGame[i]);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 54, LEFT);
			addstr((char*)SetupForm.tRaw[6 + j], "92,19%", 61, RAIGHT);
			procent = (statistic.ArrWinGame[i] * 10000) / statistic.ArrBetGame[i];
			formatMoney(procent, ss);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 68, LEFT);
			procent = (statistic.ArrBetGame[i] * 10000) / statistic.TBetGame;
			formatMoney(procent, ss);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 74, LEFT);
			procent = (statistic.ArrWinGame[i] * 10000) / statistic.TWinGame;
			formatMoney(procent, ss);
			addstr((char*)SetupForm.tRaw[6 + j], ss, 80, LEFT);
			j++;
		}

		memset(ss, 0, sizeof(ss));
		for(int i=0; i<80; i++)
			ss[i]='-';
		sprintf((char*)SetupForm.tRaw[6 + j++], "%s", ss);
		
		sprintf((char*)SetupForm.tRaw[6 + j++], "Denom  = Denomination");
		sprintf((char*)SetupForm.tRaw[6 + j++], "B/L    = Bet Per Line");
		sprintf((char*)SetupForm.tRaw[6 + j++], "Theo%%  = Theoretical Yield for that Denom");
		sprintf((char*)SetupForm.tRaw[6 + j++], "Actua%% = Actual yield");
		sprintf((char*)SetupForm.tRaw[6 + j++], "Bet%%   = Percentage of Total Bet bet with this config");
		sprintf((char*)SetupForm.tRaw[6 + j],   "Win%%   = Percentage of Total Win won with this config");
		return;
	}
	
	if(statPage == 2){
		for(int i=0; i < DescriptGame[NumberGame].pBetSeries[0]-1; i++){
			AnyWin += statistic.ArrAnyWin[i];  
			NoWin += statistic.ArrNoWin[i];  
			ScatterWin += statistic.ArrScaterWin[i];
		
			LineGame[0] += statistic.ArrLinesPlay[0][i];
			LineGame[1] += statistic.ArrLinesPlay[1][i];
			LineGame[2] += statistic.ArrLinesPlay[2][i];
			LineGame[3] += statistic.ArrLinesPlay[3][i];
			LineGame[4] += statistic.ArrLinesPlay[4][i];

			GamePlay += statistic.ArrCntGame[i];
			GameBet += statistic.ArrBetGame[i];
			GameWon += statistic.ArrWinGame[i];
			
			GamblPlay += statistic.ArrGamblPlay[i];
			GamblIn += statistic.ArrGamblIn[i];
			GamblOut += statistic.ArrGamblOut[i];
		}
		TotalLinesGames = LineGame[0] + LineGame[1] + LineGame[2] + LineGame[3] + LineGame[4];
		GamblAll = GamblOut + GameWon;
		for(int i=0; i < 5; i++){
			procLinePlay[i] = LineGame[i] * 10000 /	TotalLinesGames;
		}
		procGame = GameWon * 10000 / GameBet;
		procYield = GamblAll * 10000 / GameBet;  

		sprintf(ss, "%s %s %s", DescriptGame[NumberGame].pNameGame, tLabel1, tLabel2);		

	} else {
			AnyWin = statistic.ArrAnyWin[statPage - 3];  
			NoWin = statistic.ArrNoWin[statPage - 3];  
			ScatterWin = statistic.ArrScaterWin[statPage - 3];
		
			LineGame[0] = statistic.ArrLinesPlay[0][statPage - 3];
			LineGame[1] = statistic.ArrLinesPlay[1][statPage - 3];
			LineGame[2] = statistic.ArrLinesPlay[2][statPage - 3];
			LineGame[3] = statistic.ArrLinesPlay[3][statPage - 3];
			LineGame[4] = statistic.ArrLinesPlay[4][statPage - 3];

			GamePlay = statistic.ArrCntGame[statPage - 3];
			GameBet = statistic.ArrBetGame[statPage - 3];
			GameWon = statistic.ArrWinGame[statPage - 3];
			
			GamblPlay = statistic.ArrGamblPlay[statPage - 3];
			GamblIn = statistic.ArrGamblIn[statPage - 3];
			GamblOut = statistic.ArrGamblOut[statPage - 3];
		
		TotalLinesGames = LineGame[0] + LineGame[1] + LineGame[2] + LineGame[3] + LineGame[4];
		GamblAll = GamblOut + GameWon;
		for(int i=0; i < 5; i++){
			procLinePlay[i] = LineGame[i] * 10000 /	TotalLinesGames;
		}
		procGame = GameWon * 10000 / GameBet;
		procYield = GamblAll * 10000 / GameBet;  
		
		sprintf(ss, "%s %s %s %d", DescriptGame[NumberGame].pNameGame, tLabel1, tLabel3, DescriptGame[NumberGame].pBetSeries[statPage - 2]);
	}		
	
	sprintf((char*)SetupForm.tRaw[0], "Hit rate");
	addstr((char*)SetupForm.tRaw[0], ss, 40, CENTERE);
	sprintf((char*)SetupForm.tRaw[1], "--------");
	
	addstr((char*)SetupForm.tRaw[2], "Any win combination", 3, RAIGHT);
	sprintf(ss, "%d", AnyWin);
	addstr((char*)SetupForm.tRaw[2], ss, 45, LEFT);
	formatMoney(AnyWin * 10000 / (AnyWin + NoWin), st);
	sprintf(ss, "Lines (%s%%)", st);
	addstr((char*)SetupForm.tRaw[2], ss, 46, RAIGHT);

	addstr((char*)SetupForm.tRaw[3], "No win", 3, RAIGHT);
	sprintf(ss, "%d", NoWin);
	addstr((char*)SetupForm.tRaw[3], ss, 45, LEFT);
	formatMoney(NoWin * 10000 / (AnyWin + NoWin), st);
	sprintf(ss, "Lines (%s%%)", st);
	addstr((char*)SetupForm.tRaw[3], ss, 46, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[4], "Scatter win", 3, RAIGHT);
	sprintf(ss, "%d", ScatterWin);
	addstr((char*)SetupForm.tRaw[4], ss, 45, LEFT);
	addstr((char*)SetupForm.tRaw[4], "Combinations", 46, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[6], "Line statistic");
	sprintf((char*)SetupForm.tRaw[7], "-------------");
	
	for(int i=0; i < DescriptGame[NumberGame].pLineSeries[0]-1; i++){
		sprintf(ss,"%d lines played", DescriptGame[NumberGame].pLineSeries[i+1]);
		addstr((char*)SetupForm.tRaw[8 + i], ss, 3, RAIGHT);
		sprintf(ss, "%d", LineGame[i]);
		addstr((char*)SetupForm.tRaw[8 + i], ss, 45, LEFT);
		formatMoney( procLinePlay[i], st);
		sprintf(ss, "Gamess (%s%%)", st);
		addstr((char*)SetupForm.tRaw[8 + i], ss, 46, RAIGHT);
	}
	addstr((char*)SetupForm.tRaw[13], "Total lines played", 3, RAIGHT);
	sprintf(ss, "%d", TotalLinesGames);
	addstr((char*)SetupForm.tRaw[13], ss, 45, LEFT);
	addstr((char*)SetupForm.tRaw[13], "Lines", 46, RAIGHT);
	
	
	sprintf((char*)SetupForm.tRaw[15], "Game statistic");
	sprintf((char*)SetupForm.tRaw[16], "--------------");
	
	addstr((char*)SetupForm.tRaw[17], "Games Played", 3, RAIGHT);
	sprintf(ss, "%d", GamePlay);
	addstr((char*)SetupForm.tRaw[17], ss, 45, LEFT);
	addstr((char*)SetupForm.tRaw[17], "Games", 46, RAIGHT);

	addstr((char*)SetupForm.tRaw[18], "Total bet", 3, RAIGHT);
	sprintf(ss, "%d", GameBet);
	addstr((char*)SetupForm.tRaw[18], ss, 45, LEFT);
	formatMoney(GameBet * swp_FixedParams.fixMoneyDenom, st);
	sprintf(ss, "Credits / %s %s", ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], st);
	addstr((char*)SetupForm.tRaw[18], ss, 46, RAIGHT);
		
	addstr((char*)SetupForm.tRaw[19], "Total won", 3, RAIGHT);
	sprintf(ss, "%d", GameWon);
	addstr((char*)SetupForm.tRaw[19], ss, 45, LEFT);
	formatMoney(GameWon * swp_FixedParams.fixMoneyDenom, st);
	sprintf(ss, "Credits / %s %s", ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], st);
	addstr((char*)SetupForm.tRaw[19], ss, 46, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[20], "Theoretical yield", 3, RAIGHT);
	addstr((char*)SetupForm.tRaw[20], "92,19 %", 47, LEFT);
	
	addstr((char*)SetupForm.tRaw[21], "Total yield", 3, RAIGHT);
//  formatMoney(swp_stisticGame[NumberGame].TWinGame * 100 / swp_stisticGame[NumberGame].TBetGame, st);
  formatMoney(procGame, st);
	sprintf(ss, "%s %%", st);
	addstr((char*)SetupForm.tRaw[21],ss, 47, LEFT);
	
	sprintf((char*)SetupForm.tRaw[23], "Gambler statistic");
	sprintf((char*)SetupForm.tRaw[24], "-----------------");
	
	addstr((char*)SetupForm.tRaw[25], "Gambler Played", 3, RAIGHT);
	sprintf(ss, "%d", GamblPlay);
	addstr((char*)SetupForm.tRaw[25], ss, 45, LEFT);
	addstr((char*)SetupForm.tRaw[25], "Games", 46, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[26], "Gamble In", 3, RAIGHT);
	sprintf(ss, "%d", GamblIn);
	addstr((char*)SetupForm.tRaw[26], ss, 45, LEFT);
	formatMoney(GamblIn * swp_FixedParams.fixMoneyDenom, st);
	sprintf(ss, "Credits / %s %s", ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], st);
	addstr((char*)SetupForm.tRaw[26], ss, 46, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[27], "Gamble Out", 3, RAIGHT);
	sprintf(ss, "%d", GamblOut);
	addstr((char*)SetupForm.tRaw[27], ss, 45, LEFT);
	formatMoney(GamblOut * swp_FixedParams.fixMoneyDenom, st);
	sprintf(ss, "Credits / %s %s", ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], st);
	addstr((char*)SetupForm.tRaw[27], ss, 46, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[28], "Total won including gambler", 3, RAIGHT);
	sprintf(ss, "%d", GamblAll);
	addstr((char*)SetupForm.tRaw[28], ss, 45, LEFT);
	formatMoney(GamblAll * swp_FixedParams.fixMoneyDenom, st);
	sprintf(ss, "Credits / %s %s", ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], st);
	addstr((char*)SetupForm.tRaw[28], ss, 46, RAIGHT);

	addstr((char*)SetupForm.tRaw[29], "Total yield including gambler", 3, RAIGHT);
//  formatMoney(swp_stisticGame[NumberGame].TWinGame * 100 / swp_stisticGame[NumberGame].TBetGame, st);
  formatMoney(procYield, st);
	sprintf(ss, "%s %%", st);
	addstr((char*)SetupForm.tRaw[29],ss, 47, LEFT);
	
}


