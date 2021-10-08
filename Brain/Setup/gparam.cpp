/**
  ******************************************************************************
  * File Name          : gparam.c
  * Description        : Parcel game setup 
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../General/swap.h"
#include "gparam.h"
#include "setup.h"
#include "../General/utility.h"

const char tBarGParam[] = "GAME SETUP > ";
const char tBarGparam1[] = "All games setup";

static byte cursor = 0;

static void gparamBar(){
//	memset(tBar, 0, sizeof(tBar));
	sprintf((char*)SetupForm.tBar[1][2], "Page 1/1");
	switch(eGparam){
		case _gparam_total:	
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarGParam, tBarGparam1);
			break;
		case _gparam_game:		
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarGParam, DescriptGame[NumberGame].pNameGame);
			break;
		default:	break;
	}
}

static void gparamKey(){
	sprintf((char*)SetupForm.tKey[1][0],"Back");
	sprintf((char*)SetupForm.tKey[1][1],"More");
	sprintf((char*)SetupForm.tKey[1][2],"Less");
	sprintf((char*)SetupForm.tKey[1][3],"Prev Iteam");
	sprintf((char*)SetupForm.tKey[1][4],"Next Iteam");
}		

void gparamButton(uint code){
	byte i;
	switch(eGparam){
		case _gparam_total:		
			switch(code){
				case 1:
					eAudit = _setup;
					cursor = 0;
					saveFixedParams();
					break;
				case 2:
						switch(cursor){
							case 0:
								if(swp_FixedParams.AutoPlayInFeature == 0){
										swp_FixedParams.AutoPlayInFeature = 1;
								} else {
									swp_FixedParams.AutoPlayInFeature = 0;
								}
							break;
							case 1:
								for(i = 0; i < sizeof(ConstGameParams.tableReelTime) ; ){
									if(ConstGameParams.tableReelTime[i++] == swp_FixedParams.ReelTime){
										break;
									}
								}
								if(i == sizeof(ConstGameParams.tableReelTime)){
									i = 0;
								}
								swp_FixedParams.ReelTime = ConstGameParams.tableReelTime[i];	
								break;
							case 2:
								for(i = 0; i < sizeof(ConstGameParams.tableGambleMult); ){
									if(ConstGameParams.tableGambleMult[i++] == swp_FixedParams.GambleMult){
										break;
									}
								}
								if(i == sizeof(ConstGameParams.tableGambleMult)){
									i = 0;
								}
								swp_FixedParams.GambleMult = ConstGameParams.tableGambleMult[i];	
								break;
							case 3:
								if(swp_FixedParams.edBellWinHigh == 0){
									swp_FixedParams.edBellWinHigh = 1;
								} else {
									swp_FixedParams.edBellWinHigh = 0;
								}
								break;
						}
					break;
				case 3:
					switch(cursor){
						case 0:
							if(swp_FixedParams.AutoPlayInFeature == 0){
								swp_FixedParams.AutoPlayInFeature = 1;
							} else {
								swp_FixedParams.AutoPlayInFeature = 0;
							}
							break;
						case 1:
							for(i = 0; i < sizeof(ConstGameParams.tableReelTime); i++){
								if(ConstGameParams.tableReelTime[i] == swp_FixedParams.ReelTime){
									break;
								}
							}
							if(i == 0){
								i = sizeof(ConstGameParams.tableReelTime);
							}								
							i--;
							swp_FixedParams.ReelTime = ConstGameParams.tableReelTime[i];								
							break;
						case 2:
							for(i = 0; i < sizeof(ConstGameParams.tableGambleMult); i++){
								if(ConstGameParams.tableGambleMult[i] == swp_FixedParams.GambleMult){
									break;
								}
							}				
							if(i == 0){
								i = sizeof(ConstGameParams.tableGambleMult);
							}								
							i--;
							swp_FixedParams.GambleMult = ConstGameParams.tableGambleMult[i];								
							break;
						case 3:
							if(swp_FixedParams.edBellWinHigh == 0){
								swp_FixedParams.edBellWinHigh = 1;
							} else {
								swp_FixedParams.edBellWinHigh = 0;
							}
							break;
					}
					break;
				case 4:
					if(cursor > 0) cursor--;
					break;
				case 5:
					cursor++;
					if(cursor > 3) cursor = 3; 
					break;
			}
			break;
		case _gparam_game:
			switch(code){
				case 1:
					eAudit = _setup;
					cursor = 0;
					readSetupGames(&swp_SetupGames, swp_Position.currentGame);
					break;
				case 2:
						switch(cursor){
							case 0:
									for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; ){
										if(DescriptGame[NumberGame].pBetSeries[i++] == swp_SetupGames.minBet){
											break;
										}
									}
									if(i == DescriptGame[NumberGame].pBetSeries[0] || DescriptGame[NumberGame].pBetSeries[i] > swp_SetupGames.maxBet){
											i = 1;
									}
									swp_SetupGames.minBet = DescriptGame[NumberGame].pBetSeries[i];
									if(swp_SetupGames.defBet < swp_SetupGames.minBet)
											swp_SetupGames.defBet = swp_SetupGames.minBet;
								break;	
							case 1:
									for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; ){
										if(DescriptGame[NumberGame].pBetSeries[i++] == swp_SetupGames.maxBet){
											break;
										}
									}
									if(i == DescriptGame[NumberGame].pBetSeries[0]){
										i = DescriptGame[NumberGame].pBetSeries[0] - 1;
									}
									swp_SetupGames.maxBet = DescriptGame[NumberGame].pBetSeries[i];
								break;
							case 2:
									for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; ){
										if(DescriptGame[NumberGame].pLineSeries[i++] == swp_SetupGames.minLine){
											break;
										}
									}
									if(i == DescriptGame[NumberGame].pLineSeries[0] || DescriptGame[NumberGame].pLineSeries[i] > swp_SetupGames.maxLine){
										i = 1;
									}
									swp_SetupGames.minLine = DescriptGame[NumberGame].pLineSeries[i];
									if(swp_SetupGames.defLine < swp_SetupGames.minLine)
											swp_SetupGames.defLine = swp_SetupGames.minLine;
								break;	
							case 3: 		
									for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; ){
										if(DescriptGame[NumberGame].pLineSeries[i++] == swp_SetupGames.maxLine){
											break;
										}
									}
									if(i == DescriptGame[NumberGame].pLineSeries[0]){
										i = DescriptGame[NumberGame].pLineSeries[0] - 1;
									}
									swp_SetupGames.maxLine = DescriptGame[NumberGame].pLineSeries[i];
								break;
							case 4:
									for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; ){
										if(DescriptGame[NumberGame].pBetSeries[i++] == swp_SetupGames.defBet){
											break;
										}
									}
									if(i == DescriptGame[NumberGame].pBetSeries[0] || DescriptGame[NumberGame].pBetSeries[i] > swp_SetupGames.maxBet){
											for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; i++){
												if(DescriptGame[NumberGame].pBetSeries[i] == swp_SetupGames.minBet){
													break;
												}
											}
									}
									swp_SetupGames.defBet = DescriptGame[NumberGame].pBetSeries[i];
								break;
							case 5:
									for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; ){
										if(DescriptGame[NumberGame].pLineSeries[i++] == swp_SetupGames.defLine){
											break;
										}
									}
									if(i == DescriptGame[NumberGame].pLineSeries[0]|| DescriptGame[NumberGame].pLineSeries[i] > swp_SetupGames.maxLine){
											for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; i++ ){
												if(DescriptGame[NumberGame].pLineSeries[i] == swp_SetupGames.minLine){
													break;
												}
											}
									}
									swp_SetupGames.defLine = DescriptGame[NumberGame].pLineSeries[i];								
							}
					break;		
				case 3:
						switch(cursor){
							case 0:
									for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; i++){
										if(DescriptGame[NumberGame].pBetSeries[i] == swp_SetupGames.minBet){
											break;
										}
									}
									if(i > 1){
										i--;
									}
									swp_SetupGames.minBet = DescriptGame[NumberGame].pBetSeries[i];
								break;	
							case 1:
									for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; i++){
										if(DescriptGame[NumberGame].pBetSeries[i] == swp_SetupGames.maxBet){
											break;
										}
									}
									if(DescriptGame[NumberGame].pBetSeries[i] > swp_SetupGames.minBet ){
											i--;
									}
									swp_SetupGames.maxBet = DescriptGame[NumberGame].pBetSeries[i];
									if(swp_SetupGames.defBet > swp_SetupGames.maxBet)
											swp_SetupGames.defBet = swp_SetupGames.maxBet;									
								break;
							case 2:
									for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; i++){
										if(DescriptGame[NumberGame].pLineSeries[i] == swp_SetupGames.minLine){
											break;
										}
									}
									if(i > 1){
										i--;
									}
									swp_SetupGames.minLine = DescriptGame[NumberGame].pLineSeries[i];
								break;	
							case 3: 		
									for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; i++){
										if(DescriptGame[NumberGame].pLineSeries[i] == swp_SetupGames.maxLine){
											break;
										}
									}
									if(DescriptGame[NumberGame].pLineSeries[i] > swp_SetupGames.minLine){
										i--;
									}
									swp_SetupGames.maxLine = DescriptGame[NumberGame].pLineSeries[i];
									if(swp_SetupGames.defLine > swp_SetupGames.maxLine)
											swp_SetupGames.defLine = swp_SetupGames.maxLine;									
								break;
							case 4:
									for(i = 1; i < DescriptGame[NumberGame].pBetSeries[0] ; i++){
										if(DescriptGame[NumberGame].pBetSeries[i] == swp_SetupGames.defBet){
											break;
										}
									}
									if(DescriptGame[NumberGame].pBetSeries[i] > swp_SetupGames.minBet){
										i--;
									}
									swp_SetupGames.defBet = DescriptGame[NumberGame].pBetSeries[i];
								break;
							case 5:
									for(i = 1; i < DescriptGame[NumberGame].pLineSeries[0] ; ){
										if(DescriptGame[NumberGame].pLineSeries[i++] == swp_SetupGames.defLine){
											break;
										}
									}
									if(DescriptGame[NumberGame].pLineSeries[i] > swp_SetupGames.minLine){
										i--;
									}
									swp_SetupGames.defLine = DescriptGame[NumberGame].pLineSeries[i];								
							}
					break;
				case 4:
					if(cursor > 0) cursor--;
					break;
				case 5:
					cursor++;
					if(cursor > 5) cursor = 5; 
					break;
			}
		if(code == 3 || code == 2)
				saveSetupGames(&swp_SetupGames, NumberGame);
		break;
	}		
}

void updateGparamTotal(){
	char ss[50];
			
	gparamBar();
	gparamKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	addstr((char*)SetupForm.tRaw[2], "AUTOPLAY IN FEATURE", 10, RAIGHT);
	sprintf(ss,"%s", (swp_FixedParams.AutoPlayInFeature) ? "ON" : "OFF");
	addstr((char*)SetupForm.tRaw[2], ss, 70, LEFT);
	
	addstr((char*)SetupForm.tRaw[4], "REEL RUNNING TIME", 10, RAIGHT);
	sprintf(ss,"%d", swp_FixedParams.ReelTime);
	addstr((char*)SetupForm.tRaw[4], ss, 70, LEFT);
	
	addstr((char*)SetupForm.tRaw[6], "MAX GAMBLE MULTIPLER", 10, RAIGHT);
	sprintf(ss,"%d", swp_FixedParams.GambleMult);
	addstr((char*)SetupForm.tRaw[6], ss, 70, LEFT);
	
	addstr((char*)SetupForm.tRaw[8], "BELL AT HIGH WIN", 10, RAIGHT);
	sprintf(ss,"%s", (swp_FixedParams.edBellWinHigh) ? "ON" : "OFF");
	addstr((char*)SetupForm.tRaw[8], ss, 70, LEFT);

	addstr((char*)SetupForm.tRaw[2 + cursor *2], "<color=yellow><</color>", 71, RAIGHT);
}

void updateGparamGame(){
	char ss[100];
	readSetupGames(&swp_SetupGames, NumberGame);	
	
	gparamBar();
	gparamKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	addstr((char*)SetupForm.tRaw[2], DescriptGame[NumberGame].pNameGame, 40, CENTERE);
	
	addstr((char*)SetupForm.tRaw[6], "MIN BET", 3, RAIGHT);
	sprintf(ss,"%d", swp_SetupGames.minBet);
	addstr((char*)SetupForm.tRaw[6], ss, 70, LEFT);
	
	addstr((char*)SetupForm.tRaw[8], "MAX BET", 3, RAIGHT);
	sprintf(ss,"%d", swp_SetupGames.maxBet);
	addstr((char*)SetupForm.tRaw[8], ss, 70, LEFT);
	
	addstr((char*)SetupForm.tRaw[10], "MIN LINE", 3, RAIGHT);
	sprintf(ss,"%d", swp_SetupGames.minLine);
	addstr((char*)SetupForm.tRaw[10], ss, 70, LEFT);

	addstr((char*)SetupForm.tRaw[12], "MAX LINE", 3, RAIGHT);
	sprintf(ss,"%d", swp_SetupGames.maxLine);
	addstr((char*)SetupForm.tRaw[12], ss, 70, LEFT);

	addstr((char*)SetupForm.tRaw[14], "DEFAULT BET", 3, RAIGHT);
	sprintf(ss,"%d", swp_SetupGames.defBet);
	addstr((char*)SetupForm.tRaw[14], ss, 70, LEFT);

	addstr((char*)SetupForm.tRaw[16], "DEFAULT LINE", 3, RAIGHT);
	sprintf(ss,"%d", swp_SetupGames.defLine);
	addstr((char*)SetupForm.tRaw[16], ss, 70, LEFT);

	addstr((char*)SetupForm.tRaw[6 + cursor *2], "<color=yellow><</color>", 71, RAIGHT);
	
	memset(ss, 0, sizeof(ss));
	for(int i=0; i<80; i++)
			ss[i]='-';
	sprintf((char*)SetupForm.tRaw[18], "%s", ss);

	sprintf((char*)SetupForm.tRaw[19], "Full range bets");
	sprintf((char*)SetupForm.tRaw[20], "[");
	for(int i=1; i < DescriptGame[NumberGame].pBetSeries[0]; i++){
		sprintf(ss, " %d,", DescriptGame[NumberGame].pBetSeries[i]);
		strcat((char*)SetupForm.tRaw[20], ss);
	}
	strcat((char*)SetupForm.tRaw[20], " ]");
	
	sprintf((char*)SetupForm.tRaw[22], "Full range lines");
	sprintf((char*)SetupForm.tRaw[23], "[");
	for(int i=1; i < DescriptGame[NumberGame].pLineSeries[0]; i++){
		sprintf(ss, " %d,", DescriptGame[NumberGame].pLineSeries[i]);
		strcat((char*)SetupForm.tRaw[23], ss);
	}
	strcat((char*)SetupForm.tRaw[23], " ]");
	
}

