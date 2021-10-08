/**
  ******************************************************************************
  * File Name          : attendant.cpp
  * Description        : forma setup remote in
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../General/utility.h"
#include "attendant.h"
#include "../General/swap_vars.h"
#include "../HARDWARE/credit.h"

//const char tHandPay[6][26] = {"CURRENT HANDPAY", "CASHABLE CREDIT",
//            "   CASHABLE" , "   BANK",
//            "NONCASHABLE CREDIT",    
//            "   NONCASHABLE"};
const char tHandPay1[] =  "CURRENT HANDPAY";
const char tHandPay2[] =  "CASHABLE CREDIT";
const char tHandPay3[] = 	"   CASHABLE";
const char tHandPay4[] =	"   BANK";
const char tHandPay5[] =  "NONCASHABLE CREDIT";
const char tHandPay6[] = 	"   NONCASHABLE";					
						
const char *tBarAttendant[2][3] =   {{"ATTENDANT > REMOTE IN", "", "Page 1/1" },
                                       {"ATTENDANT > HANDPAY CREDIT", "", "Page 1/1"}};

const char *labCredits ="CREDITS";

void attendantButton(uint code){
	switch(eAttendant){
		case _remote_in:
			switch(code){
				case 1: eAudit = _attendant;					
						break;
				case 3:	RemoteInCredit(1);
						break;
				case 4: RemoteInCredit(2);
						break;
				case 5: RemoteInCredit(3);
						break;
				default: break;	
			}
			break;
		case _handpay:
			switch(code){
				case 1: eAudit = _attendant;
					break;
				case 5: HandPayCredit();
					break;
				default:
					break;
			}				
			break;
		default: break;
	}
}

void updateRemoteIn(){
	char ss[100];
	
//	memset(tBar, 0, sizeof(tBar));
	for(int i=0; i<3; i++){
		sprintf((char*)SetupForm.tBar[1][i], "%s", tBarAttendant[0][i]);
	}
//	memset(tKey, 0, sizeof(tKey));
	sprintf((char*)SetupForm.tKey[1][0],"Back");
	for(int i=0; i<3; i++){
		formatCredit(ConstGameParams.tableRemoteInCredit[swp_FixedParams.IdxRemoteinMode][i], (char*)SetupForm.tKey[0][2+i]);
		strcpy((char*)SetupForm.tKey[1][2+i],labCredits);
	}
//	memset(tRaw, 0, sizeof(tRaw));
	sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[3],ss,55,LEFT);
	sprintf(ss,"CREDITS");
	addstr((char*)SetupForm.tRaw[3],ss,75,LEFT);
	sprintf(ss,"REMOTE IN");
	addstr((char*)SetupForm.tRaw[5],ss,10,RAIGHT);
	formatMoney(var_SetupRemoteIn * swp_FixedParams.fixMoneyDenom, ss);
	addstr((char*)SetupForm.tRaw[5], ss, 55, LEFT);
	formatCredit(var_SetupRemoteIn, ss);
	addstr((char*)SetupForm.tRaw[5], ss, 75, LEFT);
	sprintf(ss,"CURRENT CREDIT");
	addstr((char*)SetupForm.tRaw[12],ss,10,RAIGHT);
	formatMoney(swp_GlobalParams.Credit * swp_FixedParams.fixMoneyDenom, ss);
	addstr((char*)SetupForm.tRaw[12], ss, 55, LEFT);
	formatCredit(swp_GlobalParams.Credit, ss);
	addstr((char*)SetupForm.tRaw[12], ss, 75, LEFT);
}		
		
void updateHandpay(){
	char ss[100];
	
	uint TotalCashable = swp_GlobalParams.Credit + var_SetupRemoteIn;
	uint TotalNonCashable = 0;
	
	for(int i=0; i<3; i++){
		sprintf((char*)SetupForm.tBar[1][i],"%s", tBarAttendant[1][i]);
	}
//	memset(tKey, 0, sizeof(tKey));
	sprintf((char*)SetupForm.tKey[1][0],"Back");
	if ( TotalCashable + TotalNonCashable > 0){
		sprintf((char*)SetupForm.tKey[1][4],"HandPay");
	}
			
//	memset(tRaw, 0, sizeof(tRaw));
	sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[3],ss,55,LEFT);
	sprintf(ss,"CREDITS");
	addstr((char*)SetupForm.tRaw[3],ss,75,LEFT);

	strcat((char*)SetupForm.tRaw[5],tHandPay1);
	formatMoney(var_SetupHandpay * swp_FixedParams.fixMoneyDenom, ss);
	addstr((char*)SetupForm.tRaw[5], ss, 55, LEFT);
	formatCredit(var_SetupHandpay, ss);
	addstr((char*)SetupForm.tRaw[5], ss, 75, LEFT);

	strcat((char*)SetupForm.tRaw[8],tHandPay2);
	formatMoney(TotalCashable * swp_FixedParams.fixMoneyDenom, ss);
	addstr((char*)SetupForm.tRaw[8], ss, 55, LEFT);
	formatCredit(TotalCashable, ss);
	addstr((char*)SetupForm.tRaw[8], ss, 75, LEFT);
	
	strcat((char*)SetupForm.tRaw[10],tHandPay3);
	formatMoney(var_SetupRemoteIn * swp_FixedParams.fixMoneyDenom, ss);
	addstr((char*)SetupForm.tRaw[10], ss, 55, LEFT);
	formatCredit(var_SetupRemoteIn, ss);
	addstr((char*)SetupForm.tRaw[10], ss, 75, LEFT);
	
	strcat((char*)SetupForm.tRaw[12],tHandPay4);
	formatMoney(swp_GlobalParams.Credit * swp_FixedParams.fixMoneyDenom, ss);
	addstr((char*)SetupForm.tRaw[12], ss, 55, LEFT);
	formatCredit(swp_GlobalParams.Credit, ss);
	addstr((char*)SetupForm.tRaw[12], ss, 75, LEFT);

	strcat((char*)SetupForm.tRaw[15],tHandPay5);
	formatMoney(0, ss);
	addstr((char*)SetupForm.tRaw[15], ss, 55, LEFT);
	formatCredit(0, ss);
	addstr((char*)SetupForm.tRaw[15], ss, 75, LEFT);

	strcat((char*)SetupForm.tRaw[17],tHandPay6);
	formatMoney(0, ss);
	addstr((char*)SetupForm.tRaw[17], ss, 55, LEFT);
	formatCredit(0, ss);
	addstr((char*)SetupForm.tRaw[17], ss, 75, LEFT);
}


