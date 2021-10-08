/**
  ******************************************************************************
  * File Name          : account.cpp
  * Description        : Parcel accounting Setup
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../HARDWARE/pservice.h"
#include "account.h"
#include "setup.h"
#include "../General/utility.h"
#include "../General/swap_vars.h"

const char tBarAccount1[] = "ACCOUNTING > MASTER ACCOUNTING";
const char tBarAccount2[] = "ACCOUNTING > PERIODIC ACCOUNTING";
const char tBarAccount3[] =	"ACCOUNTING > HARD METER COPY";
const char tBarAccount4[] =	"ACCOUNTING > SECURITY ACCOUNTING";
const char tBarAccount5[] =	"ACCOUNTING > PERIODIC METER CLEAR";

bool clearAccount = false;
byte accountPage=1;																	

void accountInit(void){
	accountPage = 1;
}

static void accountBar(){
//	memset(tBar, 0, sizeof(tBar));
	switch(eAccount){
		case _account_master:	
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarAccount1);
			sprintf((char*)SetupForm.tBar[1][2], "Page %d/%d",accountPage, NUMPAGEMASTER);
			break;
		case _account_period:		
			sprintf((char*)SetupForm.tBar[1][0], "%s",tBarAccount2);
			sprintf((char*)SetupForm.tBar[1][2], "Page %d/%d",accountPage, NUMPAGEPERIOD);
			break;
		case _account_meter:	
			sprintf((char*)SetupForm.tBar[1][0], "%s",tBarAccount3);
			sprintf((char*)SetupForm.tBar[1][2], "Page 1/1");
			break;
		case _account_security:
			sprintf((char*)SetupForm.tBar[1][0], "%s",tBarAccount4);
			sprintf((char*)SetupForm.tBar[1][2], "Page %d/%d",accountPage, NUMPAGESECURE);
			break;
		case _account_clear:
			sprintf((char*)SetupForm.tBar[1][0], "%s",tBarAccount5);
			sprintf((char*)SetupForm.tBar[1][2], "Page 1/1");
			break;
		default: break;
	}
	
}	

static void accountKey(){
	sprintf((char*)SetupForm.tKey[1][0],"Back");
//	sprintf((char*)SetupForm.tKey[1][1],"");
//	sprintf((char*)SetupForm.tKey[1][2],"");
	if(eAccount == _account_meter || clearAccount){
//		sprintf((char*)SetupForm.tKey[1][3],"");
//		sprintf((char*)SetupForm.tKey[1][4],"");
		return;
	}		
	if(eAccount == _account_clear){
//		sprintf((char*)SetupForm.tKey[1][3],"");
		sprintf((char*)SetupForm.tKey[1][4],"Clear");
		return;
	}
	sprintf((char*)SetupForm.tKey[1][3],"Prev Page");
	sprintf((char*)SetupForm.tKey[1][4],"Next Page");
}

void updatePage(uint code, uint max){
	if(code == 4){
			accountPage --;
			if(accountPage == 0){
				accountPage = max;		
			}
		}
		if(code == 5){
			accountPage++;
			if(accountPage > max){
				accountPage = 1;
			}
		}
}

void accountButton(uint code){
	if(code == 1){
		eAudit = _accounting;		
		clearAccount = false;
		accountPage = 1;		
	}
	switch(eAccount){
		case _account_master:
			updatePage(code, NUMPAGEMASTER);
			break;
		case _account_period:	
			updatePage(code, NUMPAGEPERIOD);
			break;
		case _account_meter:	
			break;
		case _account_security:
			updatePage(code, NUMPAGESECURE);			
			break;
		case _account_clear:
			if(code == 5){
				clearAccount = true;
				owner_clear();
			}
			break;
		default: break;
	}
}

void updateAccountMaster(){
	char ss[50];
	char sb[50];
	DateTime CurrentDTime;
	float yield;
		
	accountBar();
	accountKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	updateCurrentDTime(&CurrentDTime);	
	getStrDtime(ss, sizeof(ss), &swp_SystemParams.RootInitBoard);
	sprintf((char*)SetupForm.tRaw[1],"FROM: %s", ss);
	getStrDtime(ss, sizeof(ss), &CurrentDTime);
	sprintf(sb,"TO: %s", ss); 
	addstr((char*)SetupForm.tRaw[1],sb,45,RAIGHT);

	switch(accountPage){
		case 1:
			sprintf(ss,"VALUE(%s)", ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
			addstr((char*)SetupForm.tRaw[3],ss,55,LEFT);
			sprintf(ss,"CREDITS");
			addstr((char*)SetupForm.tRaw[3],ss,75,LEFT);

			strcat((char*)SetupForm.tRaw[5],"TOTAL IN");
			formatMoney(swp_RootParams.TotalIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalIn, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[8],"   COIN IN");
			formatMoney(swp_RootParams.TotalIn_coinIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalIn_coinIn, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 75, LEFT);
	
			strcat((char*)SetupForm.tRaw[10],"   TOKEN IN");
			formatMoney(swp_RootParams.TotalIn_tokenIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalIn_tokenIn, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 75, LEFT);
	
			strcat((char*)SetupForm.tRaw[12],"   BILL IN");
			formatMoney(swp_RootParams.TotalIn_billIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalIn_billIn, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[14],"   REMOTE IN");
			formatMoney(swp_RootParams.TotalIn_RemoteIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalIn_RemoteIn, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[17],"TOTAL OUT");
			formatMoney(swp_RootParams.TotalOut * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[17], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalOut, ss);
			addstr((char*)SetupForm.tRaw[17], ss, 75, LEFT);
		
			strcat((char*)SetupForm.tRaw[19],"   COIN OUT");
			formatMoney(swp_RootParams.CoinOut * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[19], ss, 55, LEFT);
			formatCredit(swp_RootParams.CoinOut, ss);
			addstr((char*)SetupForm.tRaw[19], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[21],"   HANDPAY");
			formatMoney(swp_RootParams.Handpay * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[21], ss, 55, LEFT);
			formatCredit(swp_RootParams.Handpay, ss);
			addstr((char*)SetupForm.tRaw[21], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[28],"TOTAL IN-OUT");
			formatMoney(swp_RootParams.TotalIn * swp_FixedParams.fixMoneyDenom - swp_RootParams.TotalOut * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[28], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalIn - swp_RootParams.TotalOut, ss);
			addstr((char*)SetupForm.tRaw[28], ss, 75, LEFT);
			
			closeRaw((char*)SetupForm.tRaw[10]);
			break;
		case 2:
			sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
			addstr((char*)SetupForm.tRaw[3],ss,55,LEFT);
			sprintf(ss,"CREDITS");
			addstr((char*)SetupForm.tRaw[3],ss,75,LEFT);

			strcat((char*)SetupForm.tRaw[5],"TOTAL BET");
			formatMoney(swp_RootParams.TotalBet * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalBet, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[8],"TOTAL WON");
			formatMoney(swp_RootParams.TotalWon * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 55, LEFT);
			formatCredit(swp_RootParams.TotalWon, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 75, LEFT);
	
			strcat((char*)SetupForm.tRaw[10],"   GAME WIN TO CREDIT");
			formatMoney(swp_RootParams.WinToCredit * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 55, LEFT);
			formatCredit(swp_RootParams.WinToCredit, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 75, LEFT);
			
			strcat((char*)SetupForm.tRaw[12],"   JP WIN TO CREDIT");
			formatMoney(swp_RootParams.JPtoCredit * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 55, LEFT);
			formatCredit(swp_RootParams.JPtoCredit, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[14],"   BONUS WIN TO CREDIT");
			formatMoney(swp_RootParams.BonusToCredit * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 55, LEFT);
			formatCredit(swp_RootParams.BonusToCredit, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[18],"MACHINE YIELD");
			yield = ((((double)swp_RootParams.TotalWon / (double)swp_RootParams.TotalBet) * 100.00 ));
			if(0 != swp_RootParams.TotalBet){
				sprintf(ss,"%.2f%%",yield);
			}else{
				sprintf(ss,"--,--%%");
			}
			addstr((char*)SetupForm.tRaw[18], ss, 55, LEFT);

			strcat((char*)SetupForm.tRaw[20],"TOTAL GAMES");
			formatCredit(swp_RootParams.TotalGames, ss);
			addstr((char*)SetupForm.tRaw[20], ss, 55, LEFT);
			break;
		case 3:
			sprintf(ss, "BILL ACCEPTOR :    %s", strBillAcceptor[swp_BillParams.TypeBillAcceptor]);
			addstr((char*)SetupForm.tRaw[3], ss, 20, RAIGHT);
			if(0 == swp_BillParams.TypeBillAcceptor){
				break;
			}
			sprintf(ss, "CHANNEL");		
			addstr((char*)SetupForm.tRaw[5], ss, 5, RAIGHT);
			sprintf(ss, "VALUE");		
			addstr((char*)SetupForm.tRaw[5], ss, 20, RAIGHT);
			sprintf(ss, "COUNT");		
			addstr((char*)SetupForm.tRaw[5], ss, 35, RAIGHT);
			sprintf(ss, "CREDIT");		
			addstr((char*)SetupForm.tRaw[5], ss, 50, RAIGHT);
			sprintf(ss, "TOTAL");		
			addstr((char*)SetupForm.tRaw[5], ss, 65, RAIGHT);
			for(int i=0; i<8; i++){
				sprintf(ss, "%d", i+1);		
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 9, LEFT);
				
				formatMoney(swp_BillParams.BillValueCh[i], ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 25, LEFT);
				
				sprintf(ss, "%d", swp_BillParams.RootBillCountCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 40, LEFT);
				
				sprintf(ss, "%d", swp_BillParams.RootBillCreditCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 57, LEFT);

				formatMoney(swp_BillParams.RootBillCreditCh[i] * swp_FixedParams.fixMoneyDenom, ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 75, LEFT);
				
				if(0 == swp_BillParams.BillValueCh[i]){
					closeRaw((char*)SetupForm.tRaw[7 + i*2]);
				}
			}
			sprintf(ss, "--------------------------------------------------------------------------------");
			addstr((char*)SetupForm.tRaw[23], ss, 3, RAIGHT);
			break;
		case 4:
			sprintf(ss, "COIN ACCEPTOR :    %s", strCoinAcceptor[swp_CoinParams.TypeCoinAcceptor]);
			addstr((char*)SetupForm.tRaw[3], ss, 20, RAIGHT);
			if(0 == swp_CoinParams.TypeCoinAcceptor){
				break;
			}
			sprintf(ss, "CHANNEL");		
			addstr((char*)SetupForm.tRaw[5], ss, 5, RAIGHT);
			sprintf(ss, "VALUE");		
			addstr((char*)SetupForm.tRaw[5], ss, 20, RAIGHT);
			sprintf(ss, "COUNT");		
			addstr((char*)SetupForm.tRaw[5], ss, 35, RAIGHT);
			sprintf(ss, "CREDIT");		
			addstr((char*)SetupForm.tRaw[5], ss, 50, RAIGHT);
			sprintf(ss, "TOTAL");		
			addstr((char*)SetupForm.tRaw[5], ss, 65, RAIGHT);
			for(int i=0; i<4; i++){
				sprintf(ss, "%d", i+1);		
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 9, RAIGHT);
				
				formatMoney(swp_CoinParams.CoinValueCh[i], ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 25, LEFT);
				
				sprintf(ss, "%d", swp_CoinParams.RootCoinCountCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 40, LEFT);
				
				sprintf(ss, "%d", swp_CoinParams.RootCoinCreditCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 57, LEFT);

				formatMoney(swp_CoinParams.RootCoinCreditCh[i] * swp_FixedParams.fixMoneyDenom, ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 75, LEFT);
				
				if(0 == swp_CoinParams.CoinValueCh[i]){
					closeRaw((char*)SetupForm.tRaw[7 + i*2]);
				}
			}
			sprintf(ss, "--------------------------------------------------------------------------------");
			addstr((char*)SetupForm.tRaw[18], ss, 3, RAIGHT);
			break;	
		default: break;
	}
}
	
void updateAccountPeriodic(){
	char ss[50];
	char sb[50];
	DateTime CurrentDTime;
	float yield;
	
	accountBar();
	accountKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	updateCurrentDTime(&CurrentDTime);	
	getStrDtime(ss, sizeof(ss), &swp_SystemParams.OwnerInitBoard);
	sprintf((char*)SetupForm.tRaw[1],"FROM: %s", ss);
	getStrDtime(ss, sizeof(ss), &CurrentDTime);
	sprintf(sb,"TO: %s", ss); 
	addstr((char*)SetupForm.tRaw[1],sb,45,RAIGHT);

	switch(accountPage){
		case 1:
			sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
			addstr((char*)SetupForm.tRaw[3],ss,55,LEFT);
			sprintf(ss,"CREDITS");
			addstr((char*)SetupForm.tRaw[3],ss,75,LEFT);

			strcat((char*)SetupForm.tRaw[5],"TOTAL IN");
			formatMoney(swp_OwnerParams.TotalIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalIn, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[8],"   COIN IN");
			formatMoney(swp_OwnerParams.TotalIn_coinIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalIn_coinIn, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 75, LEFT);
	
			strcat((char*)SetupForm.tRaw[10],"   TOKEN IN");
			formatMoney(swp_OwnerParams.TotalIn_tokenIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalIn_tokenIn, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 75, LEFT);
	
			strcat((char*)SetupForm.tRaw[12],"   BILL IN");
			formatMoney(swp_OwnerParams.TotalIn_billIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalIn_billIn, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[14],"   REMOTE IN");
			formatMoney(swp_OwnerParams.TotalIn_RemoteIn * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalIn_RemoteIn, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[17],"TOTAL OUT");
			formatMoney(swp_OwnerParams.TotalOut * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[17], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalOut, ss);
			addstr((char*)SetupForm.tRaw[17], ss, 75, LEFT);
		
			strcat((char*)SetupForm.tRaw[19],"   COIN OUT");
			formatMoney(swp_OwnerParams.CoinOut * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[19], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.CoinOut, ss);
			addstr((char*)SetupForm.tRaw[19], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[21],"   HANDPAY");
			formatMoney(swp_OwnerParams.Handpay * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[21], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.Handpay, ss);
			addstr((char*)SetupForm.tRaw[21], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[28],"TOTAL IN-OUT");
			formatMoney(swp_OwnerParams.TotalIn * swp_FixedParams.fixMoneyDenom - swp_OwnerParams.TotalOut * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[28], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalIn - swp_OwnerParams.TotalOut, ss);
			addstr((char*)SetupForm.tRaw[28], ss, 75, LEFT);
			
			closeRaw((char*)SetupForm.tRaw[10]);
			break;
		case 2:
			sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
			addstr((char*)SetupForm.tRaw[3],ss,55,LEFT);
			sprintf(ss,"CREDITS");
			addstr((char*)SetupForm.tRaw[3],ss,75,LEFT);

			strcat((char*)SetupForm.tRaw[5],"TOTAL BET");
			formatMoney(swp_OwnerParams.TotalBet * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalBet, ss);
			addstr((char*)SetupForm.tRaw[5], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[8],"TOTAL WON");
			formatMoney(swp_OwnerParams.TotalWon * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.TotalWon, ss);
			addstr((char*)SetupForm.tRaw[8], ss, 75, LEFT);
	
			strcat((char*)SetupForm.tRaw[10],"   GAME WIN TO CREDIT");
			formatMoney(swp_OwnerParams.WinToCredit * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.WinToCredit, ss);
			addstr((char*)SetupForm.tRaw[10], ss, 75, LEFT);
			
			strcat((char*)SetupForm.tRaw[12],"   JP WIN TO CREDIT");
			formatMoney(swp_OwnerParams.JPtoCredit * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.JPtoCredit, ss);
			addstr((char*)SetupForm.tRaw[12], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[14],"   BONUS WIN TO CREDIT");
			formatMoney(swp_OwnerParams.BonusToCredit * swp_FixedParams.fixMoneyDenom, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 55, LEFT);
			formatCredit(swp_OwnerParams.BonusToCredit, ss);
			addstr((char*)SetupForm.tRaw[14], ss, 75, LEFT);

			strcat((char*)SetupForm.tRaw[18],"MACHINE YIELD");
			yield = ((((double)swp_OwnerParams.TotalWon / (double)swp_OwnerParams.TotalBet) * 100.00 ));
			if(0 != swp_OwnerParams.TotalBet){
				sprintf(ss,"%.2f%%",yield);
			}else{
				sprintf(ss,"--,--%%");
			}
			addstr((char*)SetupForm.tRaw[18], ss, 55, LEFT);

			strcat((char*)SetupForm.tRaw[20],"TOTAL GAMES");
			formatCredit(swp_OwnerParams.TotalGames, ss);
			addstr((char*)SetupForm.tRaw[20], ss, 55, LEFT);
			break;
		case 3:
			sprintf(ss, "BILL ACCEPTOR :    %s", strBillAcceptor[swp_BillParams.TypeBillAcceptor]);
			addstr((char*)SetupForm.tRaw[3], ss, 20, RAIGHT);
			if(0 == swp_BillParams.TypeBillAcceptor){
				break;
			}
			sprintf(ss, "CHANNEL");		
			addstr((char*)SetupForm.tRaw[5], ss, 5, RAIGHT);
			sprintf(ss, "VALUE");		
			addstr((char*)SetupForm.tRaw[5], ss, 20, RAIGHT);
			sprintf(ss, "COUNT");		
			addstr((char*)SetupForm.tRaw[5], ss, 35, RAIGHT);
			sprintf(ss, "CREDIT");		
			addstr((char*)SetupForm.tRaw[5], ss, 50, RAIGHT);
			sprintf(ss, "TOTAL");		
			addstr((char*)SetupForm.tRaw[5], ss, 65, RAIGHT);
			for(int i=0; i<8; i++){
				sprintf(ss, "%d", i+1);		
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 9, RAIGHT);
				
				formatMoney(swp_BillParams.BillValueCh[i], ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 25, LEFT);
				
				sprintf(ss, "%d", swp_BillParams.OwnerBillCountCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 40, LEFT);
				
				sprintf(ss, "%d", swp_BillParams.OwnerBillCreditCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 57, LEFT);

				formatMoney(swp_BillParams.OwnerBillCreditCh[i] * swp_FixedParams.fixMoneyDenom, ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 75, LEFT);
				
				if(0 == swp_BillParams.BillValueCh[i]){
					closeRaw((char*)SetupForm.tRaw[7 + i*2]);
				}
			}
			sprintf(ss, "--------------------------------------------------------------------------------");
			addstr((char*)SetupForm.tRaw[23], ss, 3, RAIGHT);
			break;
		case 4:
			sprintf(ss, "COIN ACCEPTOR :    %s", strCoinAcceptor[swp_CoinParams.TypeCoinAcceptor]);
			addstr((char*)SetupForm.tRaw[3], ss, 20, RAIGHT);
			if(0 == swp_CoinParams.TypeCoinAcceptor){
				break;
			}
			sprintf(ss, "CHANNEL");		
			addstr((char*)SetupForm.tRaw[5], ss, 5, RAIGHT);
			sprintf(ss, "VALUE");		
			addstr((char*)SetupForm.tRaw[5], ss, 20, RAIGHT);
			sprintf(ss, "COUNT");		
			addstr((char*)SetupForm.tRaw[5], ss, 35, RAIGHT);
			sprintf(ss, "CREDIT");		
			addstr((char*)SetupForm.tRaw[5], ss, 50, RAIGHT);
			sprintf(ss, "TOTAL");		
			addstr((char*)SetupForm.tRaw[5], ss, 65, RAIGHT);
			for(int i=0; i<4; i++){
				sprintf(ss, "%d", i+1);		
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 9, RAIGHT);
				
				formatMoney(swp_CoinParams.CoinValueCh[i], ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 25, LEFT);
				
				sprintf(ss, "%d", swp_CoinParams.OwnerCoinCountCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 40, LEFT);
				
				sprintf(ss, "%d", swp_CoinParams.OwnerCoinCreditCh[i]);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 57, LEFT);

				formatMoney(swp_CoinParams.OwnerCoinCreditCh[i] * swp_FixedParams.fixMoneyDenom, ss);
				addstr((char*)SetupForm.tRaw[7 + i*2], ss, 75, LEFT);
				
				if(0 == swp_CoinParams.CoinValueCh[i]){
					closeRaw((char*)SetupForm.tRaw[7 + i*2]);
				}
			}
			sprintf(ss, "--------------------------------------------------------------------------------");
			addstr((char*)SetupForm.tRaw[18], ss, 3, RAIGHT);
			break;	
		default: break;
	}
}

void updateAccountMeter(){
	char ss[50];

	accountBar();
	accountKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	sprintf(ss, "HARD METER TYPE:");
	addstr((char*)SetupForm.tRaw[1], ss, 15, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[4], "   BET");
	sprintf(ss, "%d", swp_MechCounters.MeterBet);
	addstr((char*)SetupForm.tRaw[4], ss, 65, LEFT);
	
	sprintf((char*)SetupForm.tRaw[6], "   WIN");
	sprintf(ss, "%d", swp_MechCounters.MeterWin);
	addstr((char*)SetupForm.tRaw[6], ss, 65, LEFT);

	sprintf((char*)SetupForm.tRaw[8], "   REMOTE");
	sprintf(ss, "%d", swp_MechCounters.MeterRemote);
	addstr((char*)SetupForm.tRaw[8], ss, 65, LEFT);
	
	sprintf((char*)SetupForm.tRaw[10], "   HANDPAY");
	sprintf(ss, "%d", swp_MechCounters.MeterHandpay);
	addstr((char*)SetupForm.tRaw[10], ss, 65, LEFT);

	sprintf((char*)SetupForm.tRaw[12], "   BILLS");
	sprintf(ss, "%d", swp_MechCounters.MeterBills);
	addstr((char*)SetupForm.tRaw[12], ss, 65, LEFT);

	sprintf((char*)SetupForm.tRaw[14], "   DROP");
	sprintf(ss, "%d", swp_MechCounters.MeterDrop);
	addstr((char*)SetupForm.tRaw[14], ss, 65, LEFT);
	closeRaw((char*)SetupForm.tRaw[14]);
	
	sprintf((char*)SetupForm.tRaw[16], "   GAMES");
	sprintf(ss, "%d", swp_MechCounters.MeterGames);
	addstr((char*)SetupForm.tRaw[16], ss, 65, LEFT);

	sprintf((char*)SetupForm.tRaw[18], "   TOKEN");
	sprintf(ss, "%d", swp_MechCounters.MeterToken);
	addstr((char*)SetupForm.tRaw[18], ss, 65, LEFT);
	closeRaw((char*)SetupForm.tRaw[18]);
}

void updateAccountSecure(){
	char ss[50];

	accountBar();
	accountKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));

	switch(accountPage){
		case 1:
			sprintf((char*)SetupForm.tRaw[1], "MAIN DOOR");

			sprintf((char*)SetupForm.tRaw[3], "   LAST OPEN");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.MainDoorOpen);
			addstr((char*)SetupForm.tRaw[3], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[4], "   LAST CLOSE");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.MainDoorClose);
			addstr((char*)SetupForm.tRaw[4], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[5], "   OPEN COUNT");
			sprintf(ss, "%d", swp_SystemParams.MainDoorCount);
			addstr((char*)SetupForm.tRaw[5], ss, 70, LEFT);

			sprintf((char*)SetupForm.tRaw[6], "   GAMES SINCE LAST CLOSE");
			sprintf(ss, "%d", swp_SystemParams.MainDoorEvent);
			addstr((char*)SetupForm.tRaw[6], ss, 70, LEFT);
			//-------------------------------------
			sprintf((char*)SetupForm.tRaw[10], "DOOR IN DOOR");

			sprintf((char*)SetupForm.tRaw[12], "   LAST OPEN");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.DoorDoorOpen);
			addstr((char*)SetupForm.tRaw[12], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[13], "   LAST CLOSE");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.DoorDoorClose);
			addstr((char*)SetupForm.tRaw[13], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[14], "   OPEN COUNT");
			sprintf(ss, "%d", swp_SystemParams.DoorDoorCount);
			addstr((char*)SetupForm.tRaw[14], ss, 70, LEFT);

			sprintf((char*)SetupForm.tRaw[15], "   GAMES SINCE LAST CLOSE");
			sprintf(ss, "%d", swp_SystemParams.DoorDoorEvent);
			addstr((char*)SetupForm.tRaw[15], ss, 70, LEFT);
			//-------------------------------------
			sprintf((char*)SetupForm.tRaw[19], "POWER FAIL");

			sprintf((char*)SetupForm.tRaw[21], "   LAST POWER FAIL");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.PowerDateFail);
			addstr((char*)SetupForm.tRaw[21], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[22], "   LAST POWER ON");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.PowerDateOn);
			addstr((char*)SetupForm.tRaw[22], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[23], "   POWER FAIL COUNT");
			sprintf(ss, "%d", swp_SystemParams.PowerFailCount);
			addstr((char*)SetupForm.tRaw[23], ss, 70, LEFT);

			sprintf((char*)SetupForm.tRaw[24], "   GAMES SINCE LAST PAWER FAIL");
			sprintf(ss, "%d", swp_SystemParams.PowerEvent);
			addstr((char*)SetupForm.tRaw[24], ss, 70, LEFT);
			break;
		case 2:
			sprintf((char*)SetupForm.tRaw[1], "PERIODIC METER CLEAR");

			sprintf((char*)SetupForm.tRaw[3], "   LAST CLEAR");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.OwnerDateClear);
			addstr((char*)SetupForm.tRaw[3], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[4], "   CLEAR COUNT");
			sprintf(ss, "%d", swp_SystemParams.OwnerClearCount);
			addstr((char*)SetupForm.tRaw[4], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[5], "   GAMES SINCE LAST CLEAR");
			sprintf(ss, "%d", swp_SystemParams.OwnerClearEvent);
			addstr((char*)SetupForm.tRaw[5], ss, 70, LEFT);
			//---------------------------------------------
			sprintf((char*)SetupForm.tRaw[9], "INIT MACHINE");

			sprintf((char*)SetupForm.tRaw[11], "   LAST INIT MACHINE");
			getStrDtime(ss, sizeof(ss), &swp_SystemParams.RootDateInit);
			addstr((char*)SetupForm.tRaw[11], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[12], "   GAMES SINCE LAST INIT");
			sprintf(ss, "%d", swp_SystemParams.RootInitEvent);
			addstr((char*)SetupForm.tRaw[12], ss, 70, LEFT);
	
			sprintf((char*)SetupForm.tRaw[13], "   TOTAL INIT MACHINE COUNT");
			sprintf(ss, "%d", swp_SystemParams.RootInitCount);
			addstr((char*)SetupForm.tRaw[13], ss, 70, LEFT);

			sprintf((char*)SetupForm.tRaw[14], "   TOTAL INIT MACHINE ERROR");
			sprintf(ss, "%d", swp_SystemParams.RootInitError);
			addstr((char*)SetupForm.tRaw[14], ss, 70, LEFT);
			
			sprintf((char*)SetupForm.tRaw[18], "OPERATION TIME SINCE LAST INIT");
			break;
		default:	break;
	}		
}

void updateAccountClear(){
	char ss[50];

	accountBar();
	accountKey();
//	memset((char*)SetupForm.tRaw, 0, sizeof((char*)SetupForm.tRaw));
	
	if(clearAccount){
			sprintf(ss, "<color=red>RAM CLEAR OK</color>");
			addstr((char*)SetupForm.tRaw[14], ss, 35, RAIGHT);
	}else{
			sprintf(ss, "PRESS CLEAR BUTTON TO CLEAR PERIODIC RAM");
			addstr((char*)SetupForm.tRaw[14], ss, 20, RAIGHT);
	}
	
}
