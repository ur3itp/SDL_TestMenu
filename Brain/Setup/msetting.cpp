/**
  ******************************************************************************
  * File Name          : msetting.c
  * Description        : machine setup 
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "msetting.h"
#include "../General/utility.h"
#include "setup.h"
#include "../General/swap.h"

const char tBarSMachine1[] = "MACHINE SETUP > ";
const char tBarSMachine2[] = "LIMIT SETUP";
const char tBarSMachine3[] = "PARAMETER SETUP"; 
const char tBarSMachine4[] = "BILL ACCEPTOR SETUP";
const char tBarSMachine5[] = "COIN ACCEPTOR SETUP";
const char tBarSMachine6[] = "INITIAL SETUP";
const char tBarSMachine7[] = "GAMES ENABLE / DISABLE";

static byte cursorX =0, cursorY =0;

static void msetBar(){
//	memset(tBar, 0, sizeof(tBar));
	sprintf((char*)SetupForm.tBar[1][2], "Page 1/1");
	switch(eMsetting){
		case _mset_limit:	
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarSMachine1, tBarSMachine2);
			break;
		case _mset_params:
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarSMachine1, tBarSMachine3);
			break;
		case _mset_bill:
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarSMachine1, tBarSMachine4);
			break;
		case _mset_coin:
			sprintf((char*)SetupForm.tBar[1][0], "%s%s", tBarSMachine1, tBarSMachine5);
			break;
		default:	break;
	}
}

static void msetKey(uint param){
	sprintf((char*)SetupForm.tKey[1][0],"Back");
	if(param == 0){
		sprintf((char*)SetupForm.tKey[1][1],"More");
		sprintf((char*)SetupForm.tKey[1][2],"Less");
		sprintf((char*)SetupForm.tKey[1][3],"Prev Iteam");
		sprintf((char*)SetupForm.tKey[1][4],"Next Iteam");
		return;
	}
	if(param == 1){
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
//		sprintf((char*)SetupForm.tKey[1][3],"");
//		sprintf((char*)SetupForm.tKey[1][4],"");
		return;
	}
	if(param == 2){
		sprintf((char*)SetupForm.tKey[1][1],"On / Off");
		sprintf((char*)SetupForm.tKey[1][2],"Prev Iteam");
		sprintf((char*)SetupForm.tKey[1][3],"Next Iteam");
//		sprintf((char*)SetupForm.tKey[1][4],"");
		return;
	}
}		

static void dec_value(uint min, uint *value){
	uint temp = *value;
	switch(cursorX){
		case 0:	if(temp > 0) temp -= 1;			 break;	
		case 1: if(temp > 9) temp -= 10; 		 break;
		case 2: if(temp > 99) temp -= 100; 		 break;
		case 4: if(temp > 999) temp -= 1000; 		 break;
		case 5: if(temp > 9999) temp -= 10000; 		 break;
		case 6: if(temp > 99999) temp -= 100000; 		 break;
		case 8: if(temp > 999999) temp -= 1000000; 		 break;
	}
	if(temp >= min)
			*value = temp;
}

static void inc_value(uint *value, uint max){
		uint temp = *value;
	switch(cursorX){
		case 0:	temp += 1;			 break;	
		case 1: temp += 10; 		 break;
		case 2: temp += 100; 		 break;
		case 4: temp += 1000; 		 break;
		case 5: temp += 10000; 		 break;
		case 6: temp += 100000; 		 break;
		case 8: temp += 1000000; 		 break;
	}
	if(temp <= max)
			*value = temp;
}


void MachineSetupButton(uint code){
	
	if(code == 1){
		eAudit = _machine;
		cursorX = 0;
		cursorY = 0;	
	}
	switch(eMsetting){
		case _mset_init:
			if(code == 2){
					switch(cursorY){
						case 0:	inc_value( &swp_FixedParams.CreditInLimit, 1000000); 		break;
						case 1: inc_value( &swp_FixedParams.CreditLimit, 1000000); 	break;
						case 2: inc_value( &swp_FixedParams.JackpotLimit, 1000000); 			break;
						case 3: inc_value( &swp_FixedParams.DoubleUpLimit, 1000000); 		break;
						case 4: inc_value( &swp_FixedParams.HoperPayoutLimit, 100000); 	break;
						case 5: inc_value( &swp_FixedParams.MinimumHandpay, 100000); 		break;
						case 6: inc_value( &swp_FixedParams.EvenHandpay, 100000); 				break;
						default:	break;
					}
				saveFixedParams();
			}
	
			if(code == 3){
					switch(cursorY){
						case 0:	dec_value( 0, &swp_FixedParams.CreditInLimit); 		break;
						case 1: dec_value( 200000, &swp_FixedParams.CreditLimit); 	break;
						case 2: dec_value( 0, &swp_FixedParams.JackpotLimit); 			break;
						case 3: dec_value( 0, &swp_FixedParams.DoubleUpLimit); 		break;
						case 4: dec_value( 0, &swp_FixedParams.HoperPayoutLimit); 	break;
						case 5: dec_value( 0, &swp_FixedParams.MinimumHandpay); 		break;
						case 6: dec_value( 0, &swp_FixedParams.EvenHandpay); 				break;
						default:	break;
					}
				saveFixedParams();
			}
	
			if(code == 4){
					if(cursorY != 6 || cursorX != 8){
						if(cursorX == 8){
							cursorY ++;
							cursorX = 0;
						} else {
								if(cursorX == 2 || cursorX == 6 ){	
									cursorX += 2;
								} else {
								cursorX ++;
								}						
						}
					}
			}
	
			if(code == 5){
					if(cursorX != 0 || cursorY != 0){
						if(cursorX == 0){
							cursorY--;
							cursorX = 8;
						} else {
							if(cursorX == 8 || cursorX == 4 ){	
									cursorX -= 2;
							} else {
									cursorX --;
							}						
						}
					}
			}
			break;
		case _mset_params:		
			if(code == 2 || code == 3){
				switch(cursorY){
					case 0:	swp_FixedParams.edRemoteInput = swp_FixedParams.edRemoteInput ? 0 : 1; 
						break;
					case 1: swp_FixedParams.edHandpayCredit = swp_FixedParams.edHandpayCredit ? 0 : 1;
						break;
					case 2: swp_FixedParams.edBillInput = swp_FixedParams.edBillInput ? 0 : 1;
						break;
					case 3: swp_FixedParams.edCoinInput = swp_FixedParams.edCoinInput ? 0 : 1;
						break;
					case 4: swp_FixedParams.edHopper = swp_FixedParams.edHopper ? 0 : 1;
						break;
					case 5: swp_FixedParams.edHopperDump = swp_FixedParams.edHopperDump ? 0 : 1;
						break;
					case 6: swp_FixedParams.selKeybordMode = swp_FixedParams.selKeybordMode ? 0 : 1;
						break;
					case 7: swp_FixedParams.selSoundMode = swp_FixedParams.selSoundMode ? 0 : 1;
						break;
					case 8: swp_FixedParams.edSecondScreen = swp_FixedParams.edSecondScreen ? 0 : 1;
						break;
					case 9: 
						if(code == 2){
							if(swp_FixedParams.IdxRemoteinMode != 0)	swp_FixedParams.IdxRemoteinMode--;
						}
						if(code == 3){
							if(swp_FixedParams.IdxRemoteinMode != 4) swp_FixedParams.IdxRemoteinMode++;
						}
						break;
					case 10: swp_FixedParams.selTouchscrMode = swp_FixedParams.selTouchscrMode ? 0 : 1;
						break;
					case 11: 	swp_FixedParams.edKeyGameSel = swp_FixedParams.edKeyGameSel ? 0 : 1;
						break;
				}
				saveFixedParams();
			}
			if(code == 4){
				if(cursorY == 0)
					cursorY = 12;
				cursorY--;
			}
			if(code == 5){
				cursorY++;
				if(cursorY == 12)
					cursorY = 0;
			}
			break;
		case _mset_bill:	
			if(swp_BillParams.TypeBillAcceptor == 2 || swp_BillParams.TypeBillAcceptor == 3){
				if(code == 3){
					if(cursorY == 0)
						cursorY = 8;
					cursorY--;
				}
				if(code == 4){
					cursorY++;
					if(cursorY == 8)
						cursorY = 0;
				}
					

			}
			break;
		default:	break; 
		}
}



void updateMachineSetupLimit(){
	const char modL[] = "<color=grey>" ;
	const char modR[] = "</color>";
//	char bufA[] = {'<','c','o','l','o','r','=','g','r','e','y','>'};	
	
	char ss[50];
	
	msetBar();
	msetKey(0);
//	memset(tRaw, 0, sizeof(tRaw));
	
	addstr((char*)SetupForm.tRaw[2], "MIN", 35, LEFT);
	addstr((char*)SetupForm.tRaw[2], "CURRENT", 50, LEFT);
	addstr((char*)SetupForm.tRaw[2], "MAX", 65, LEFT);
	
	sprintf((char*)SetupForm.tRaw[4], "CREDIT IN LIMIT");
	sprintf(ss, "%s%d%s", modL, 0, modR);
	addstr((char*)SetupForm.tRaw[4], ss, 34, RAIGHT);
	formatCredit(swp_FixedParams.CreditInLimit, ss);	
	addstr((char*)SetupForm.tRaw[4], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "1.000.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[4], ss, 56, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[6], "CREDIT LIMIT");
	sprintf(ss, "%s%s%s", modL, "200.000", modR);
	addstr((char*)SetupForm.tRaw[6], ss, 28, RAIGHT);
	formatCredit(swp_FixedParams.CreditLimit, ss);	
	addstr((char*)SetupForm.tRaw[6], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "1.000.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[6], ss, 56, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[8], "JACKPOT LIMIT");
	sprintf(ss, "%s%d%s", modL, 0, modR);
	addstr((char*)SetupForm.tRaw[8], ss, 34, RAIGHT);
	formatCredit(swp_FixedParams.JackpotLimit, ss);	
	addstr((char*)SetupForm.tRaw[8], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "1.000.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[8], ss, 56, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[10], "DOUBLE UP LIMIT");
	sprintf(ss, "%s%d%s", modL, 0, modR);
	addstr((char*)SetupForm.tRaw[10], ss, 34, RAIGHT);
	formatCredit(swp_FixedParams.DoubleUpLimit, ss);	
	addstr((char*)SetupForm.tRaw[10], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "1.000.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[10], ss, 56, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[12], "HOPPER PAYOUT LIMIT");
	sprintf(ss, "%s%d%s", modL, 0, modR);
	addstr((char*)SetupForm.tRaw[12], ss, 34, RAIGHT);
	formatCredit(swp_FixedParams.HoperPayoutLimit, ss);	
	addstr((char*)SetupForm.tRaw[12], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "100.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[12], ss, 58, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[14], "MINIMUM HANDPAY");
	sprintf(ss, "%s%d%s", modL, 0, modR);
	addstr((char*)SetupForm.tRaw[14], ss, 34, RAIGHT);
	formatCredit(swp_FixedParams.MinimumHandpay, ss);	
	addstr((char*)SetupForm.tRaw[14], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "100.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[14], ss, 58, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[16], "EVEN HANDPAY");
	sprintf(ss, "%s%d%s", modL, 0, modR);
	addstr((char*)SetupForm.tRaw[16], ss, 34, RAIGHT);
	formatCredit(swp_FixedParams.EvenHandpay, ss);	
	addstr((char*)SetupForm.tRaw[16], ss, 50, LEFT);
	sprintf(ss, "%s%s%s %s", modL, "100.000", modR, "Credits");
	addstr((char*)SetupForm.tRaw[16], ss, 58, RAIGHT);

	addstr((char*)SetupForm.tRaw[5 + cursorY *2], "<color=yellow>^</color>", 49 - cursorX, RAIGHT);
}

void updateMachineSetupParams(){
	const char modL[] = "<color=yellow>" ;
	const char modR[] = "</color>";
	
	char ss[50];
	char sb[50];
	
	msetBar();
	msetKey(0);
//	memset(tRaw, 0, sizeof(tRaw));

	sprintf((char*)SetupForm.tRaw[2], "REMOTE INPUT");
	sprintf(sb, "%d: %s", swp_FixedParams.edRemoteInput,(swp_FixedParams.edRemoteInput ? "ENABLE" : "DISABLE"));
	if(cursorY == 0)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[2], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[4], "HANDPAY CREDIT");
	sprintf(sb, "%d: %s", swp_FixedParams.edHandpayCredit,(swp_FixedParams.edHandpayCredit ? "ENABLE" : "DISABLE"));
	if(cursorY == 1)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[4], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[6], "BILL INPUT");
	sprintf(sb, "%d: %s", swp_FixedParams.edBillInput,(swp_FixedParams.edBillInput ? "ENABLE" : "DISABLE"));
	if(cursorY == 2)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[6], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[8], "COIN INPUT");
	sprintf(sb, "%d: %s", swp_FixedParams.edCoinInput,(swp_FixedParams.edCoinInput ? "ENABLE" : "DISABLE"));
	if(cursorY == 3)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[8], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[10], "HOPPER");
	sprintf(sb, "%d: %s", swp_FixedParams.edHopper,(swp_FixedParams.edHopper ? "ENABLE" : "DISABLE"));
	if(cursorY == 4)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[10], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[12], "HOPPER DUMP");
	sprintf(sb, "%d: %s", swp_FixedParams.edHopperDump,(swp_FixedParams.edHopperDump ? "ENABLE" : "DISABLE"));
	if(cursorY == 5)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[12], ss, 40, RAIGHT);

	sprintf((char*)SetupForm.tRaw[14], "KEYBOARD MODE");
	sprintf(sb, "%d: %s", swp_FixedParams.selKeybordMode,(swp_FixedParams.selKeybordMode ? "12 BUTTONS" : "8 BBUTTONS"));
	if(cursorY == 6)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[14], ss, 40, RAIGHT);

	sprintf((char*)SetupForm.tRaw[16], "SOUND MODE");
	sprintf(sb, "%d: %s", swp_FixedParams.selSoundMode,(swp_FixedParams.selSoundMode ? "STEREO" : "MONO"));
	if(cursorY == 7)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[16], ss, 40, RAIGHT);

	sprintf((char*)SetupForm.tRaw[18], "SECOND SCREEN");
	sprintf(sb, "%d: %s", swp_FixedParams.edSecondScreen,(swp_FixedParams.edSecondScreen ? "ENABLE" : "DISABLE"));
	if(cursorY == 8)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[18], ss, 40, RAIGHT);

	sprintf((char*)SetupForm.tRaw[20], "REMOTE IN MODE");
	sprintf(sb, "%d: hold3 - %d, hold4 - %d, hold5 - %d", swp_FixedParams.IdxRemoteinMode, ConstGameParams.tableRemoteInCredit[swp_FixedParams.IdxRemoteinMode][0],
		ConstGameParams.tableRemoteInCredit[swp_FixedParams.IdxRemoteinMode][1], ConstGameParams.tableRemoteInCredit[swp_FixedParams.IdxRemoteinMode][2]);
	if(cursorY == 9)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[20], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[22], "TOUCHSCREEN MODE");
	sprintf(sb, "%d: %s", swp_FixedParams.selTouchscrMode, (swp_FixedParams.selTouchscrMode ? "ENABLE" : "DISABLE"));
	if(cursorY == 10)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[22], ss, 40, RAIGHT);
	
	sprintf((char*)SetupForm.tRaw[24], "BUTTONS FOR GAMES SELECT");
	sprintf(sb, "%d: %s", swp_FixedParams.edKeyGameSel, (swp_FixedParams.edKeyGameSel ? "ENABLE" : "DISABLE"));
	if(cursorY == 11)
		sprintf(ss, "%s%s%s", modL, sb, modR);
	else
		sprintf(ss, "%s", sb);
	addstr((char*)SetupForm.tRaw[24], ss, 40, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[3 + cursorY *2], "<color=yellow>^</color>", 40, RAIGHT);
}

void updateMachineSetupBill(){
	const char modL[] = "<color=yellow>" ;
	const char modR[] = "</color>";
	
	char ss[50];
	char sb[50];
	
	msetBar();
//	memset(tRaw, 0, sizeof(tRaw));
	
	sprintf(ss, "BILL ACCEPTOR : %s", strBillAcceptor[swp_BillParams.TypeBillAcceptor]);
	addstr((char*)SetupForm.tRaw[3], ss, 40, CENTERE);
	addstr((char*)SetupForm.tRaw[5], "CHANNEL", 22, LEFT);
	addstr((char*)SetupForm.tRaw[5], "VALUE", 35, RAIGHT);
	addstr((char*)SetupForm.tRaw[5], "ENABLE", 60, LEFT);

	msetKey(1);			
	
	if(swp_BillParams.TypeBillAcceptor == 0){
		return;	
	}
	
	msetKey(1);		
	
	if(swp_BillParams.TypeBillAcceptor == 1){
		formatMoney(swp_BillParams.BillValueCh[0], sb);
		sprintf(ss, "%s %s", sb, ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
		addstr((char*)SetupForm.tRaw[7], "1", 22, LEFT);
		addstr((char*)SetupForm.tRaw[7], ss, 35, RAIGHT);
		addstr((char*)SetupForm.tRaw[7], (swp_FixedParams.edBillInput ? "ON" : "OFF"), 60, LEFT);
		return;
	}

	msetKey(2);		
	
	for(int i =0; i < 8; i++){
		sprintf(ss, "%d", i+1);	
		addstr((char*)SetupForm.tRaw[7 + i*2], ss, 22, LEFT);
		sprintf(ss, "%s %s", sb, ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
		addstr((char*)SetupForm.tRaw[7 + i*2], ss, 35, RAIGHT);
		addstr((char*)SetupForm.tRaw[7 + i*2], ((swp_BillParams.edChanal >> i) & 0x01  ? "ON" : "OFF"), 60, LEFT);
	}
	
	addstr((char*)SetupForm.tRaw[28], "DIRECTION                 A B C D", 20, RAIGHT);
	
	addstr((char*)SetupForm.tRaw[7 + cursorY *2], "<color=yellow><</color>", 61, RAIGHT);
}

void updateMachineSetupCoin(){
	const char modL[] = "<color=yellow>" ;
	const char modR[] = "</color>";
	
	char ss[50];
	char sb[50];
	
	msetBar();
	msetKey(1);
//	memset(tRaw, 0, sizeof(tRaw));

	if(swp_CoinParams.TypeCoinAcceptor == 0){
		addstr((char*)SetupForm.tRaw[3], strCoinAcceptor[0], 40, CENTERE);
		return;	
	}
	
}
