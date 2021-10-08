/**
  ******************************************************************************
  * File Name          : audit.c
  * Description        : Parsing pipe form
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../General/utility.h"
#include "audit.h"
#include "../HARDWARE/pservice.h"

const char tBar_Audit[3][10] = {"", "AUDIT", ""};										
const char tKey_Audit[6][5][10] = {
													{"","","","Down","Enter"},
													{"","Up","","Down","Enter"},
													{"","Up","","","Enter"},
													{"Back","","","Down","Enter"},
													{"Back","Up","","Down","Enter"},
													{"Back","Up","","","Enter"}};

const char *pMenuAudit[9] ={"ATTENDANT", "ACCOUNTING", "DIAGNOSTIC", "EVENT_LOG",
													"GAME HISTORY", "GAME STATISTIC", "GAME SETUP", "MACHINE SETUP", "CALIBRATION"};
const char *pMenuAttendant[4] = {"REMOTE IN", "HANDPAY CREDIT", 
													"OUT OF SERVICE: INACTIVE", "OUT OF SERVICE: ACTIVE"};
const char *pMenuAccount[5] = {"MASTER ACCOUNTING", "PERIODIC ACCOUNTING", "HARD METER COPY",
													"SECURITY ACCOUNTING", "PERIODIC METER CLEAR"};
const char *pMenuDiagnos[6] = {"PROGRAM VERSIONS", "BUTTON AND LAMP TEST", "VIDEO TEST", "AUDIO TEST", "MACHINE SELFTEST",
													"TOUCH SCREEN TEST"};
const char *pMenuEvent[5] = {"MACHINE EVENTS", "BILL ACCEPTOR EVENTS", "REMOTE IN EVENTS", "HANDPAY EVENTS",
													"JACKPOT EVENTS" };
const char *pMenuStat1[12] = {"TOTAL", "game1", "game2", "game3", "game4", "game5", "game6",
													"game7", "game8", "game9", "game10", ">>>"};
const char *pMenuStat2[11] = {"<<<", "game11", "game12", "game13", "game14", "game15", "game16",
													"game17", "game18", "game19", "game20"};
const char setupIteam1[] = "All games setup";
const char setupIteam2[] = "game1";
const char *pMenuSetup[] = {setupIteam1, setupIteam2};
const char *pMenuMachine[] = {"LIMIT SETUP", "PARAMETER SETUP" , "BILL ACCEPTOR SETUP", "COIN ACCEPTOR SETUP", "INITIAL SETUP", "JACKPOT SETUP", "GAMES ENABLE / DISABLE"};
const char *pMenuCalibr[] = {"CLOCK SETUP", "TOUCH SCREEN CALIBRATION", "PASSWORD SETUP"};
static const char modL[] = "<color=yellow>" ;
static const char modR[] = "</color>";
													
byte cursorL=0, cursorR =0;
													
void auditInit(){
	cursorL = 0;
	cursorR = 0;
}
													
void auditBar()
{
	for(int i=0; i < 3; i++)
	{
		sprintf((char*)SetupForm.tBar[1][i], "%s",  tBar_Audit[i]);
	}	
}
static void auditKey()
{
	uint count;
	if(TypeSetup == 0) count = AUDITSHORT;
	if(TypeSetup == 1) count = AUDITLONG;
	
	byte index=0;
	switch(eAudit){
		case _audit:
			cursorR = 0;
			if(cursorL ==0)							index = 0;
			if(cursorL >0) 							index = 1;
			if(cursorL >= count-1){
				index = 2;
				cursorL = count-1;
			}				
			break;
		case _attendant:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == ATTENDADMIN-1)			index = 5;
			break;
		case _accounting:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0)							index = 4;
			if(cursorR == ACCONTADMIN-1)			index = 5;
			break;
		case _diagnostic:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == DIAGNSADMIN-1)			index = 5;
			break;
		case _eventlog:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == EVENADMIN-1)				index = 5;
			break;
		case _statistic1:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == STATADMIN1-1)				index = 5;
			break;
		case _statistic2:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == STATADMIN2-1)				index = 5;
			break;
		case _setup:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == SETUPADMIN-1)				index = 5;
			break;
		case _machine:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == MACHINEADMIN-1)			index = 5;
			break;
		case _calibrate:
			if(cursorR == 0)						index = 3;
			if(cursorR > 0) 						index = 4;
			if(cursorR == CALIBRADMIN-1)			index = 5;
			break;
		default:	break;
	}

	for(int i=0; i < 5; i++)
	{
		strcpy((char*)SetupForm.tKey[1][i], tKey_Audit[index][i]);
	}
}	

static void auditRaw()
{
	char ss[100];
	int y=0;
	uint count;
	if(TypeSetup == 0) count = AUDITSHORT;
	if(TypeSetup == 1) count = AUDITLONG;
	
	{
		for(uint i=0; i < count; i++)
		{
			if(cursorL == i)
			{
				sprintf((char*)SetupForm.tRaw[i*2+3],"%s%c%s%s", modL,'>',pMenuAudit[i],modR);
			}			
			else
			{
				sprintf((char*)SetupForm.tRaw[i*2+3],"%c%s", ' ',pMenuAudit[i]);
			}
		}
	}
	switch(eAudit){	
		case _attendant:
			for(int i=0; i < ATTENDADMIN; i++){
				if(i==2){
					y = getPService() ? 1: 0; // service
				}
				if(cursorR == i){
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuAttendant[i+y],modR);  	
				}	else {
					sprintf(ss,"%c%s", ' ',pMenuAttendant[i+y]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _accounting:
			for(int i=0; i < ACCONTADMIN; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuAccount[i],modR);  	
				}	else {
					sprintf(ss,"%c%s", ' ',pMenuAccount[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _diagnostic:
			for(int i=0; i < DIAGNSADMIN; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuDiagnos[i],modR);  	
				}	else {
					sprintf(ss,"%c%s", ' ',pMenuDiagnos[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _eventlog:
			for(int i=0; i < EVENADMIN; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuEvent[i],modR);  	
				}	else {
					sprintf(ss,"%c%s", ' ',pMenuEvent[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _statistic1:
			for(int i=0; i < STATADMIN1; i++)	{
				if(cursorR == i){
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuStat1[i],modR);  	
				}	else {
					sprintf(ss,"%c%s", ' ',pMenuStat1[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _statistic2:
			for(int i=0; i < STATADMIN2; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuStat2[i],modR);  	
				} else {
					sprintf(ss,"%c%s", ' ',pMenuStat2[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _setup:	
			for(int i=0; i < SETUPADMIN; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuSetup[i],modR);
				} else {
					sprintf(ss,"%c%s", ' ',pMenuSetup[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;
		case _machine:	
			for(int i=0; i < MACHINEADMIN; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuMachine[i],modR);
				} else {
					sprintf(ss,"%c%s", ' ',pMenuMachine[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;			
		case _calibrate:	
			for(int i=0; i < CALIBRADMIN; i++) {
				if(cursorR == i) {
					sprintf(ss,"%s%c%s%s", modL,'>',pMenuCalibr[i],modR);  	
				} else {
					sprintf(ss,"%c%s", ' ',pMenuCalibr[i]);  	
				}
				addstr((char*)SetupForm.tRaw[i*2+3], ss, 40, RAIGHT);
			}
			break;			
		default:	break;	
	}
}


void auditButton(uint code)
{
	uint count;
	if(TypeSetup == 0) count = AUDITSHORT;
	if(TypeSetup == 1) count = AUDITLONG;

	switch(code){
		case 1:
			if((eAudit == _attendant)||(eAudit == _accounting)||(eAudit == _diagnostic)||
					(eAudit == _eventlog) || (eAudit == _statistic1) || (eAudit == _statistic2) ||
					(eAudit == _setup) || (eAudit == _machine) || (eAudit == _calibrate))	eAudit = _audit;
			break;
		case 2:	
			if (eAudit == _audit) 
			{	
				if(cursorL > 0) cursorL--;
			}
			else
			{
				if(cursorR > 0)	cursorR--;
			}
			break;
		case 4:
				switch(eAudit){
					case _audit:				if(cursorL < count-1)	cursorL++; 				break;
					case _attendant:			if(cursorR < ATTENDADMIN-1)	cursorR++; 	break;
					case _accounting:			if(cursorR < ACCONTADMIN-1)	cursorR++;  break;
					case _diagnostic:			if(cursorR < DIAGNSADMIN-1)	cursorR++;  break;
					case _eventlog:				if(cursorR < EVENADMIN-1)		cursorR++;  break;
					case _statistic1:			if(cursorR < STATADMIN1-1)	cursorR++;  break;
					case _statistic2:			if(cursorR < STATADMIN2-1)	cursorR++;  break;
					case _setup:				if(cursorR < SETUPADMIN-1)	cursorR++;  break;
					case _machine:				if(cursorR < MACHINEADMIN-1)cursorR++;  break;
					case _calibrate:			if(cursorR < CALIBRADMIN-1)	cursorR++;  break;	
					default:	break;
				}
			break;
		case 5:
			switch(eAudit){
				case _audit:
					switch(cursorL){
						case 0: eAudit = _attendant;		break;
						case 1: eAudit = _accounting;		break;
						case 2: eAudit = _diagnostic;		break;
						case 3: eAudit = _eventlog;			break;
						case 4: eAudit = _history;			break;
						case 5: eAudit = _statistic1;		break;
						case 6: eAudit = _setup;			break;
						case 7: eAudit = _machine;			break;
						case 8: eAudit = _calibrate;		break;
						default: break;
					}
					break;
				case _attendant:
					eAudit = _attendant_sub;
					switch(cursorR){
						case 0: eAttendant = _remote_in;		break;
						case 1: eAttendant = _handpay;			break;
						case 2: TogglePService();
										eAudit = _attendant;	break;
						default: break;		
					}
					break;
				case _accounting:
					eAudit = _accounting_sub;
					switch(cursorR){
						case 0: eAccount = _account_master; 	break;
						case 1: eAccount = _account_period; 	break;
						case 2: eAccount = _account_meter;		break;
						case 3: eAccount = _account_security;	break;
						case 4: eAccount = _account_clear;		break;
						default: 	break;	
					}
					break;		
				case _diagnostic:
					eAudit = _diagnostic_sub;
					switch(cursorR){
						case 0:	eDiagnos = _diagnos_prgver;		break;
						case 1:	eDiagnos = _diagnos_keytest;	break;
						case 2: eDiagnos = _diagnos_video;		break;	
						case 3:	eDiagnos = _diagnos_audio;		break;
						case 4:	eDiagnos = _diagnos_self;		break;
						case 5:	eDiagnos = _diagnos_touch;		break;			
						default:	break;
					}
					break;			
				case _eventlog:	
					eAudit = _eventlog_sub;
					switch(cursorR){
						case 0:	eEvent = _event_machine;		break;
						case 1: eEvent = _event_bill;			break;
						case 2: eEvent = _event_remotein;		break;
						case 3: eEvent = _event_handpay;		break;
						case 4:	eEvent = _event_jackpot;		break;	
						default:	break;
					}
					break;
				case _statistic1:
					eAudit = _statistic_sub;
					switch(cursorR){
						case 0: eStatistic = _stat_total;							break;
//*						case 1: eStatistic = _stat_game;	NumberGame =0;			break;
//*						case 2: eStatistic = _stat_game;	NumberGame =1;			break;
//*						case 3: eStatistic = _stat_game;	NumberGame =2;			break;
//*						case 4: eStatistic = _stat_game;	NumberGame =3;			break;
//*						case 5: eStatistic = _stat_game;	NumberGame =4;			break;
//*						case 6: eStatistic = _stat_game;	NumberGame =5;			break;
//*						case 7: eStatistic = _stat_game;	NumberGame =6;			break;
//*						case 8: eStatistic = _stat_game;	NumberGame =7;			break;
//*						case 9: eStatistic = _stat_game;	NumberGame =8;			break;
//*						case 10: eStatistic = _stat_game;	NumberGame =9;			break;
						case 11: eAudit = _statistic2;		cursorR =0;				break;
						default:    break;		
					}
					break;		
				case _statistic2:
					eAudit = _statistic_sub;
					switch(cursorR){
						case 0: eAudit = _statistic1;		cursorR = 0;			break;
//*						case 1: eStatistic = _stat_game;	NumberGame =10;			break;
//*						case 2: eStatistic = _stat_game;	NumberGame =11;			break;
//*						case 3: eStatistic = _stat_game;	NumberGame =12;			break;
//*						case 4: eStatistic = _stat_game;	NumberGame =13;			break;
//*						case 5: eStatistic = _stat_game;	NumberGame =14;			break;
//*						case 6: eStatistic = _stat_game;	NumberGame =15;			break;
//*						case 7: eStatistic = _stat_game;	NumberGame =16;			break;
//*						case 8: eStatistic = _stat_game;	NumberGame =17;			break;
//*						case 9: eStatistic = _stat_game;	NumberGame =18;			break;
//*						case 10: eStatistic = _stat_game;	NumberGame =19;			break;
						default:    break;		
					}
					break;
				case _setup:		
					eAudit = _setup_sub;
					switch(cursorR){
						case 0:	eGparam = _gparam_total;								break;
//*						case 1: eGparam = _gparam_game;		NumberGame = 0;				break;
						default:	break;
					}
					break;
				case _machine:
					eAudit = _machine_sub;
					switch(cursorR){
						case 0:	eMsetting = _mset_limit;								break;
						case 1: eMsetting = _mset_params;								break;
						case 2: eMsetting = _mset_bill;									break;
						case 3: eMsetting = _mset_coin;									break;
						case 4: eMsetting = _mset_init;									break;
						case 5: eMsetting = _mset_game_onoff;							break;
						default:	break;
					}
					break;
				case _calibrate:
					break;
				default: break;
			}
	}

}


void auditUpdate(void){
	
	if((TypeSetup == 0) && (eAudit == _setup || eAudit == _machine || eAudit == _calibrate ||
			eAudit == _setup_sub || eAudit == _machine_sub || eAudit == _calibrate_sub)){
			eAudit = _audit;		
	}
	
		auditBar();
		auditKey();
		auditRaw();

}
