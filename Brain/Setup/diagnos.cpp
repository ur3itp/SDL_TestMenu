/**
  ******************************************************************************
  * File Name          : diagnos.cpp
  * Description        : Parcel diagnostic Setup
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "setup.h"
#include "../HARDWARE/inout.h"
#include "../General/utility.h"
#include "../General/swap_vars.h"
//#include "pkeylamp.h"
#include "diagnos.h"

const char tBarDiagnos1[] = "DIAGNOSTIC > PROGRAM VERSIONS";
const char tBarDiagnos2[] = "DIAGNOSTIC > BUTTON AND LAMP TEST";
const char tBarDiagnos3[] =	"DIAGNOSTIC > VIDEO TEST";
const char tBarDiagnos4[] =	"DIAGNOSTIC > AUDIO TEST";
const char tBarDiagnos5[] =	"DIAGNOSTIC > MACHINE SELFTEST";
const char tBarDiagnos6[] = "DIAGNOSTIC > TOUCH SCREEN TEST";

static byte sndTrack=0;

byte diagnosPage=1;																	

static void diagnosBar(){
//	memset(tBar, 0, sizeof(tBar));
	switch(eDiagnos){
		case _diagnos_prgver:	
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarDiagnos1);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",diagnosPage, NUMPAGEPRGVER);
			break;
		case _diagnos_keytest:	
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarDiagnos2);
			sprintf((char*)SetupForm.tBar[1][2],"Page 1/1");
			break;
		case _diagnos_video:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarDiagnos3);
			sprintf((char*)SetupForm.tBar[1][2],"Page 1/1");
			break;
		case _diagnos_audio:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarDiagnos4);
			sprintf((char*)SetupForm.tBar[1][2],"Page 1/1");
			break;
		case _diagnos_self:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarDiagnos5);
			sprintf((char*)SetupForm.tBar[1][2],"Page 1/1");
			break;
		case _diagnos_touch:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarDiagnos6);
			sprintf((char*)SetupForm.tBar[1][2],"Page 1/1");
			break;
		default: break;
	}
}	

static void diagnosKey(){
	if(eDiagnos == _diagnos_prgver){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
		sprintf((char*)SetupForm.tKey[1][3],"Prev Page");
		sprintf((char*)SetupForm.tKey[1][4],"Next Page");
		return;
	}
	if(eDiagnos == _diagnos_keytest){
		sprintf((char*)SetupForm.tKey[1][0],"Back 1");
		sprintf((char*)SetupForm.tKey[1][1],"Back 2");
//		sprintf((char*)SetupForm.tKey[1][2],"");
//		sprintf((char*)SetupForm.tKey[1][3],"");
//		sprintf((char*)SetupForm.tKey[1][4],"");
		return;
	}
	if(eDiagnos == _diagnos_video || eDiagnos == _diagnos_touch){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
//		sprintf((char*)SetupForm.tKey[1][3],"");
//		sprintf((char*)SetupForm.tKey[1][4],"");
		return;
	}		
	if(eDiagnos == _diagnos_audio){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
		sprintf((char*)SetupForm.tKey[1][1],"Off");
		sprintf((char*)SetupForm.tKey[1][2],(sndTrack != 1) ? "1kHz" : "off 1kHz");
		sprintf((char*)SetupForm.tKey[1][3],(sndTrack != 2) ? "10kHz" : "off 10kHz");
		sprintf((char*)SetupForm.tKey[1][4],(sndTrack != 3) ? "Alarm" : "off Alarm");
		return;
	}			
	if(eDiagnos == _diagnos_self){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
//		sprintf((char*)SetupForm.tKey[1][3],"");
		sprintf((char*)SetupForm.tKey[1][4],"Test");
		return;
	}			
}

static void updatePage(uint code, uint max){
	if(code == 4){
			diagnosPage --;
			if(diagnosPage == 0){
				diagnosPage = max;		
			}
		}
		if(code == 5){
			diagnosPage++;
			if(diagnosPage > max){
				diagnosPage = 1;
			}
		}
}

void diagnosButton(uint code){
	if(code == 1){
		eAudit = _diagnostic;		
		diagnosPage = 1;
		sndTrack = 0;	
	}
	switch(eDiagnos){
		case _diagnos_prgver:
			updatePage(code, NUMPAGEPRGVER);
			break;
		case _diagnos_audio:
			if(code == 2)				sndTrack = 0x80;
			if(code == 3)				sndTrack = 1;
			if(code == 4)				sndTrack = 2;			
			if(code == 5)				sndTrack = 3;			
			break;
		default: break;
	}	
}

void updateDiagnosVer(){
	
	diagnosBar();
	diagnosKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	switch(diagnosPage){
		case 1:
			sprintf((char*)SetupForm.tRaw[1], "MACHINE NUMBER");
			addstr((char*)SetupForm.tRaw[1], ConstSystemInfo.pstrMachineNumber, 75, LEFT);

			sprintf((char*)SetupForm.tRaw[3], "MACHINE");
			addstr((char*)SetupForm.tRaw[3], ConstSystemInfo.pstrMachine, 75, LEFT);

			sprintf((char*)SetupForm.tRaw[5], "MACHINE VERSION");
			addstr((char*)SetupForm.tRaw[5], ConstSystemInfo.pstrMachineVersion, 75, LEFT);

			sprintf((char*)SetupForm.tRaw[7], "EEPROM CONFIGURATION");
			addstr((char*)SetupForm.tRaw[7], ConstSystemInfo.pstrEepromConf, 75, LEFT);
			addstr((char*)SetupForm.tRaw[9], ConstSystemInfo.pstrMachineSha1, 75, LEFT);
			addstr((char*)SetupForm.tRaw[11], ConstSystemInfo.pstrMachineSha2, 75, LEFT);
		
			sprintf((char*)SetupForm.tRaw[13], "KERNEL VERSION");
			addstr((char*)SetupForm.tRaw[13], ConstSystemInfo.pstrKernelVer, 75, LEFT);
		
			sprintf((char*)SetupForm.tRaw[15], "MAINBOARD VERSION");
			addstr((char*)SetupForm.tRaw[15], ConstSystemInfo.pstrBoardVer, 75, LEFT);

			sprintf((char*)SetupForm.tRaw[17], "MAINBOARD SERIAL NUMBER");
			addstr((char*)SetupForm.tRaw[17], ConstSystemInfo.pstrBoardNumber, 75, LEFT);
		
			sprintf((char*)SetupForm.tRaw[19], "MAINBOARD BOOT ID");
			addstr((char*)SetupForm.tRaw[19], ConstSystemInfo.pstrBootId, 75, LEFT);
			
			sprintf((char*)SetupForm.tRaw[21], "BACKPLAIN VERSION");
			addstr((char*)SetupForm.tRaw[21], ConstSystemInfo.pstrBackPlainVer, 75, LEFT);

			sprintf((char*)SetupForm.tRaw[23], "PROGRAM ROM CRC");
			addstr((char*)SetupForm.tRaw[23], ConstSystemInfo.pstrRomCrc, 75, LEFT);

			sprintf((char*)SetupForm.tRaw[25], "GAME SELECTOR");
			addstr((char*)SetupForm.tRaw[25], ConstSystemInfo.pstrGameSelector, 75, LEFT);
			break;
		case 2:
			sprintf((char*)SetupForm.tRaw[1], "GAME");
			addstr((char*)SetupForm.tRaw[1], ConstSystemInfo.pstrGameLadyCharm, 75, LEFT);
			
			break;
		default: break;
	}
}

void strSwitch(int state, char* text){
	if(state)		sprintf(text,"<color=yellow>ON</color>");
		else			sprintf(text,"<color=yellow>OFF</color>");
}

void updateDiagnosTest(){
	char ss[100];
	
	diagnosBar();
	diagnosKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	sprintf(ss, "START");
	addstr((char*)SetupForm.tRaw[1], ss, 25, RAIGHT);
//	strSwitch(PIN_START, ss);
	addstr((char*)SetupForm.tRaw[1], ss, 50, RAIGHT);
	
	sprintf(ss, "AUTOSTART");
	addstr((char*)SetupForm.tRaw[3], ss, 25, RAIGHT);
//	strSwitch(PIN_AUTOSTART, ss);
	addstr((char*)SetupForm.tRaw[3], ss, 50, RAIGHT);
	
	sprintf(ss, "INFO");
	addstr((char*)SetupForm.tRaw[5], ss, 25, RAIGHT);
//	strSwitch(PIN_INFO, ss);
	addstr((char*)SetupForm.tRaw[5], ss, 50, RAIGHT);

	sprintf(ss, "HOLD 1");
	addstr((char*)SetupForm.tRaw[7], ss, 25, RAIGHT);
	strSwitch(PIN_HOLD1, ss);
	addstr((char*)SetupForm.tRaw[7], ss, 50, RAIGHT);
	
	sprintf(ss, "HOLD 2");
	addstr((char*)SetupForm.tRaw[9], ss, 25, RAIGHT);
	strSwitch(PIN_HOLD2, ss);
	addstr((char*)SetupForm.tRaw[9], ss, 50, RAIGHT);

	sprintf(ss, "HOLD 3");
	addstr((char*)SetupForm.tRaw[11], ss, 25, RAIGHT);
	strSwitch(PIN_HOLD3, ss);
	addstr((char*)SetupForm.tRaw[11], ss, 50, RAIGHT);

	sprintf(ss, "HOLD 4");
	addstr((char*)SetupForm.tRaw[13], ss, 25, RAIGHT);
	strSwitch(PIN_HOLD4, ss);
	addstr((char*)SetupForm.tRaw[13], ss, 50, RAIGHT);
	
	sprintf(ss, "HOLD 5");
	addstr((char*)SetupForm.tRaw[15], ss, 25, RAIGHT);
	strSwitch(PIN_HOLD5, ss);
	addstr((char*)SetupForm.tRaw[15], ss, 50, RAIGHT);
	
	sprintf(ss, "BETONE");
	addstr((char*)SetupForm.tRaw[17], ss, 25, RAIGHT);
//	strSwitch(PIN_BETONE, ss);
	addstr((char*)SetupForm.tRaw[17], ss, 50, RAIGHT);

	sprintf(ss, "MAXBET");
	addstr((char*)SetupForm.tRaw[19], ss, 25, RAIGHT);
//	strSwitch(PIN_MAXBET, ss);
	addstr((char*)SetupForm.tRaw[19], ss, 50, RAIGHT);

	sprintf(ss, "CASHOUT");
	addstr((char*)SetupForm.tRaw[21], ss, 25, RAIGHT);
//	strSwitch(PIN_CASHOUT, ss);
	addstr((char*)SetupForm.tRaw[21], ss, 50, RAIGHT);

	sprintf(ss, "SERVICE");
	addstr((char*)SetupForm.tRaw[23], ss, 25, RAIGHT);
//	strSwitch(PIN_SERVICE, ss);
	addstr((char*)SetupForm.tRaw[23], ss, 50, RAIGHT);

	sprintf(ss, "GAMESELECT");
	addstr((char*)SetupForm.tRaw[25], ss, 25, RAIGHT);
//	strSwitch(PIN_GAMESELECT, ss);
	addstr((char*)SetupForm.tRaw[25], ss, 50, RAIGHT);
	
	sprintf(ss, "<color=yellow>Press all buttons shown above</color>");
	addstr((char*)SetupForm.tRaw[27], ss, 25, RAIGHT);
	sprintf(ss, "<color=yellow>To go back, press Back 1 and Back 2 simultanously</color>");
	addstr((char*)SetupForm.tRaw[28], ss, 17, RAIGHT);
}
uint updateDiagnosVideo(){
	diagnosBar();
	diagnosKey();	
	return 0x01;
}
uint updateDiagnosSound(byte *melody){
	uint result;
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	diagnosBar();
	diagnosKey();	
	
	switch(sndTrack){
		case 1: 		*melody = 0x02; result = 0x02; break;
		case 2:			*melody = 0x03; result = 0x02; break;
		case 3:			*melody = 0x04; result = 0x02; break;
		case 0x80:		*melody = 0x05; result = 0x02; break;
		default:		 result = 0; break;
	}
	return result;
}	

void updateDiagnosSelf(){
	char ss[100];
	
	diagnosBar();
	diagnosKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	sprintf((char*)SetupForm.tRaw[2], "Static RAM test.................................");
	sprintf(ss,"SUCCESFUL");
	addstr((char*)SetupForm.tRaw[2], ss, 50, RAIGHT);

	sprintf((char*)SetupForm.tRaw[4], "Program ROM test................................");
	sprintf(ss,"SUCCESFUL");
	addstr((char*)SetupForm.tRaw[4], ss, 50, RAIGHT);

	sprintf((char*)SetupForm.tRaw[6], "Serial number test..............................");
	sprintf(ss,"SUCCESFUL");
	addstr((char*)SetupForm.tRaw[6], ss, 50, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[8], "Reel time clock test............................");
	sprintf(ss,"SUCCESFUL");
	addstr((char*)SetupForm.tRaw[8], ss, 50, RAIGHT);

	sprintf((char*)SetupForm.tRaw[10], "Configuration EEPROM test......................");
	sprintf(ss,"SUCCESFUL");
	addstr((char*)SetupForm.tRaw[10], ss, 50, RAIGHT);

	sprintf((char*)SetupForm.tRaw[14], "Selftest completed");
}

void updateDiagnosTouch(){
	diagnosBar();
	diagnosKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
}
