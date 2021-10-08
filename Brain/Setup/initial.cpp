/**
  ******************************************************************************
  * File Name          : initial.c
  * Description        : main initial setup 
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "initial.h"
#include "../General/utility.h"
#include "setup.h"
#include "../General/swap.h"

const char *pTheorYield[] = {"88%-90%", "90%-92%", "92%-94%", "95%-96%", "96%-97%"};
const char *pSetupProt[] = {"DOOR", "PASSWORD", "DOOR+PASSWORD", "NONE"};
const char *pAlarmSound[] = {"DOOR", "ERROR", "DOOR + ERROR", "QUIET"};
const char tBarInitial[] = "MACHINE SETUP > INITIAL SETUP";
static byte initPage =1;


static void initialBar(){
	sprintf((char*)SetupForm.tBar[1][1], "");
	sprintf((char*)SetupForm.tBar[1][0], "%s", tBarInitial);
	sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",initPage, 4);
}

static void initialKey(){
	if(eAudit != _audit){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
//		sprintf((char*)SetupForm.tKey[1][3],"");
		sprintf((char*)SetupForm.tKey[1][4],"NextPage");
	} else {		
		sprintf((char*)SetupForm.tKey[1][0],"More");
		sprintf((char*)SetupForm.tKey[1][1],"Less");
		sprintf((char*)SetupForm.tKey[1][2],"Prev Iteam");
		sprintf((char*)SetupForm.tKey[1][3],"Next Iteam");
		sprintf((char*)SetupForm.tKey[1][4],"NextPage");
	}
}

void initialButton(uint code){
	if(code == 1){
		eAudit = _machine;
	}
}

uint updateMachineSetupInitial(){
	char ss[100];
	char sb[20];
	uint denom;
	
	const char modGrey[] = "<color=grey>" ;
	const char modYellow[] = "<color=grey>" ;	
	const char modGreen[] = "<color=green>" ;
	const char modClose[] = "</color>";
	
	initialBar();
	initialKey();
//	memset(tRaw, 0, sizeof(tRaw));
	
	denom = swp_FixedParams.MainCoin / swp_FixedParams.Tokenisation;
	
	formatMoney(denom, sb);
	sprintf(ss, "%sDENOMINATION: 1 CREDIT = %s %s%s", modGreen, sb, ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], modClose);
	addstr((char*)SetupForm.tRaw[1], ss, 40, CENTERE);
	
	sprintf((char*)SetupForm.tRaw[4], "CURRENCY");
	addstr((char*)SetupForm.tRaw[4], ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency], 55, CENTERE);
	
	sprintf((char*)SetupForm.tRaw[6], "MAIN COIN");
	formatMoney(swp_FixedParams.MainCoin, sb);
	sprintf(ss, "1 COIN = %s %s", sb, ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[6], ss, 55, CENTERE);
	
	sprintf((char*)SetupForm.tRaw[8], "TOKENISATION");
	sprintf(ss, "1 COIN = %d CREDIT", swp_FixedParams.Tokenisation);
	addstr((char*)SetupForm.tRaw[8], ss, 55, CENTERE);

	sprintf((char*)SetupForm.tRaw[11], "MAXIMUM BET");
	formatCredit(swp_FixedParams.MaximumBet, ss);
	addstr((char*)SetupForm.tRaw[11], ss, 55, LEFT);
	
	sprintf((char*)SetupForm.tRaw[13], "MAXIMUM BER PER ROW");
	formatCredit(swp_FixedParams.MaxBetPerRow, ss);
	addstr((char*)SetupForm.tRaw[13], ss, 55, LEFT);
	
	sprintf((char*)SetupForm.tRaw[16], "LA WIN LIMIT");
	addstr((char*)SetupForm.tRaw[16], "0", 55, LEFT);
		
	sprintf((char*)SetupForm.tRaw[18], "LINES MODE");
	addstr((char*)SetupForm.tRaw[18], (swp_FixedParams.selLineMode ? "FIXED" : "DEFAULT"), 55, CENTERE);
	
	sprintf((char*)SetupForm.tRaw[20], "THEORETICAL YIELD");
	addstr((char*)SetupForm.tRaw[20], pTheorYield[swp_FixedParams.TypeMaths], 55, CENTERE);
	
	sprintf((char*)SetupForm.tRaw[22], "SETUP PROTECTION");
	addstr((char*)SetupForm.tRaw[22], pSetupProt[swp_FixedParams.selSetupProtect], 55, CENTERE);
	
	sprintf((char*)SetupForm.tRaw[24], "ALARM SOUND");
	addstr((char*)SetupForm.tRaw[24], pAlarmSound[swp_FixedParams.selAlarmSound], 55, CENTERE);

	sprintf((char*)SetupForm.tRaw[26], "MACHINE NUMBER");
	addstr((char*)SetupForm.tRaw[26], "000.000.001", 55, CENTERE);
	
	return 3;
}



