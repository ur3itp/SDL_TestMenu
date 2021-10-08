/*
 * tool.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: serg
 */

#include "setup.h"
#include "audit.h"
#include "diagnos.h"
#include "attendant.h"
#include "account.h"
#include "eventlog.h"
#include "statistic.h"
#include "initial.h"
#include "msetting.h"
#include "history.h"
#include "gparam.h"

#include "../sys_main.h"
#include "../General/queue.h"
#include "../HARDWARE/inout.h"

//void SndSysBuf(Uint32 Length);
extern ts_TxPipeBuf T_TxPipeBuf;

Uint8 NumberGame;

Uint8 SetupLayer = 0; // Setup Layer 0 - base; 1 - video test 2 - sound test;
Uint8 SubSetupLayer = 0;

Uint8 TypeSetup=0; // 0 - short audit menu 1 - long audit menu

tSetupForma SetupForm;

tAudit eAudit;
tAttendant eAttendant;
tAccount eAccount;
tDiagnos eDiagnos;
tEvent eEvent;
tStatistic eStatistic;
tGparam	eGparam;
tMsetting eMsetting;

Uint32 var = 0;

void clickSetup(uint code);
void setup(void);

void WaitToSetup(Uint8 irq){
	Sys_Queue_Clear(irq);
	if(getKeyCode() == 'S'){
		Sys_Queue_AddFunc(Setup, 20);
	}
	else{
		Sys_Queue_AddFunc(WaitToSetup, 20);
	}
}

void RunSetup(Uint8 irq){
	Sys_Queue_Clear(irq);
	auditInit();
	accountInit();
	EventLogInit();
	HistoryInit();
	eAudit = _audit;
	Sys_Queue_AddFunc(Setup, 20);
}

void Setup(Uint8 irq){
	int shift;
	uint code = getKeyCode();

	Sys_Queue_Clear(irq);

	if(code == 'S'){
		Loading(xxxSETUP, xxxNONE);
		return;
	}

	ClearSetupForm();

//	auditUpdate();
	clickSetup(code);
	setup();
	shift = SetByteBuf(CMD_SETUP, 0);
	shift = SetFormaBuf(shift);
	SndSysBuf(shift);
	Sys_Queue_AddFunc(Setup, 20);
}


int SetupConstructor(void){
	int res = 0;
	int i, j;
//	auditinit();
	eAudit = _audit;
	SetupForm.Layer = 0;
	for( i =0; i < 2; i++){
		for( j = 0; j < 3; j++){
			SetupForm.tBar[i][j] = new unsigned char[50];
			if(NULL == SetupForm.tBar[i][j]){
				res++;
			}
		}
	}
	for( i =0; i < 3; i++){
		for( j = 0; j < 5; j++){
			SetupForm.tKey[i][j] = new unsigned char[20];
			if(NULL == SetupForm.tKey[i][j]){
				res++;
			}
		}
	}
	for( i = 0; i < RAW_MAX; i++){
		SetupForm.tRaw[i] = new unsigned char[RAW_COLUMN];
		if( NULL == SetupForm.tRaw[i] ){
			res++;
		}
	}
	printf("setup %d\n", res);
	fflush(stdout);
	return res;
}

void ClearSetupForm(void){
	int i, j;
	for( i=0; i < 2; i++){
		for( j=0; j < 3; j ++){
			memset(SetupForm.tBar[i][j], 0, 50);
		}
	}
	for( i=0; i < 3; i++){
		for( j=0; j < 5; j ++){
			memset(SetupForm.tKey[i][j], 0, 20);
		}
	}
	for( i=0; i < RAW_MAX; i++){
		memset(SetupForm.tRaw[i], 0, RAW_COLUMN);
	}
}

int SetFormaBuf(int shift){
	int i, j, x;
	int _shift;

	T_TxPipeBuf.pBuf[shift++] = SetupForm.Layer;

	// reserve counter raw
	_shift = shift + RAW_MAX;

	for(i = 0; i < RAW_MAX; i++){
		j = 0;
		while(SetupForm.tRaw[i][j] != 0){
			T_TxPipeBuf.pBuf[_shift++] = SetupForm.tRaw[i][j++];
		}
		// j counter char in raw
		T_TxPipeBuf.pBuf[shift++] = j;
	}

	// 6 [2][3] - bar counter raw
	shift = _shift;
	_shift += 6;

	for(i = 0; i < 2; i++){
		for(j= 0; j < 3; j++){
			x = 0;
			while(SetupForm.tBar[i][j][x] != 0){
				T_TxPipeBuf.pBuf[_shift++] = SetupForm.tBar[i][j][x++];
			}
			T_TxPipeBuf.pBuf[shift++] = x;
		}
	}

	// 10 [2][5] - bar counter raw
	shift = _shift;
	_shift += 15;

	for(i = 0; i < 3; i++){
		for(j= 0; j < 5; j++){
			x = 0;
			while(SetupForm.tKey[i][j][x] != 0){
				T_TxPipeBuf.pBuf[_shift++] = SetupForm.tKey[i][j][x++];
			}
			T_TxPipeBuf.pBuf[shift++] = x;
		}
	}

	return _shift;
}
/////////////////////////////////////////////////////////////////////////

void clickSetup(uint code){

	switch(code){
		case '1': 	code = 1;			break;
		case '2':	code = 2;			break;
		case '3':	code = 3;			break;
		case '4':	code = 4;			break;
		case '5':	code = 5;			break;
		case 'C':	TypeSetup = 1;		return;
		case 'N':	TypeSetup = 0;		return;
		default:	return;
	}

	switch(eAudit){
		case _audit:			auditButton(code); 			break;
		case _attendant:		auditButton(code); 			break;
		case _accounting:		auditButton(code); 			break;
		case _diagnostic:		auditButton(code); 			break;
		case _eventlog:			auditButton(code); 			break;
		case _history:			histotyButton(code);		break;
		case _statistic1:		auditButton(code); 			break;
		case _statistic2:		auditButton(code); 			break;
		case _setup:			auditButton(code); 			break;
		case _machine:			auditButton(code); 			break;
		case _calibrate:		auditButton(code); 			break;
		case _attendant_sub:	attendantButton(code);		break;
		case _accounting_sub:	accountButton(code);		break;
		case _diagnostic_sub:	diagnosButton(code);		break;
		case _eventlog_sub:		eventButton(code);			break;
		case _statistic_sub:	statisticButton(code);		break;
		case _setup_sub:		gparamButton(code);			break;
		case _machine_sub:		MachineSetupButton(code);	break;
		case _calibrate_sub:								break;
		default:	break;
	}
}

void setup(void)
{
	SetupLayer = 0;
	switch(eAudit){
		case _audit:			auditUpdate(); 					break;
		case _attendant:		auditUpdate();					break;
		case _accounting:		auditUpdate(); 					break;
		case _diagnostic:		auditUpdate();					break;
		case _eventlog:			auditUpdate(); 					break;
		case _history:			historyUpdate();				break;
		case _statistic1:		auditUpdate();					break;
		case _statistic2:		auditUpdate(); 					break;
		case _setup:			auditUpdate(); 					break;
		case _machine:			auditUpdate(); 					break;
		case _calibrate:		auditUpdate(); 					break;
		case _attendant_sub:
			switch(eAttendant){
				case _remote_in:		updateRemoteIn();		break;
				case _handpay:			updateHandpay();		break;
			}
			break;
		case _accounting_sub:
			switch(eAccount){
				case _account_master:		updateAccountMaster();								break;
				case _account_period:		updateAccountPeriodic(); 							break;
				case _account_meter: 		updateAccountMeter();								break;
				case _account_security: 	updateAccountSecure();								break;
				case _account_clear:		updateAccountClear();								break;
			}
			break;
		case _diagnostic_sub:
			switch(eDiagnos){
				case _diagnos_prgver:		updateDiagnosVer();									break;
				case _diagnos_keytest:		updateDiagnosTest();								break;
				case _diagnos_video:		SetupLayer = updateDiagnosVideo();					break;
				case _diagnos_audio:		SetupLayer = updateDiagnosSound(&SubSetupLayer);	break;
				case _diagnos_self:			updateDiagnosSelf(); 								break;
				case _diagnos_touch:		updateDiagnosTouch();								break;
			}
			break;
		case _eventlog_sub:
			switch(eEvent){
				case _event_machine:		updateEventMachine(); 								break;
				case _event_bill:			updateEventBill();	 								break;
				case _event_remotein:		updateEventRemotein();								break;
				case _event_handpay:		updateEventHandpay();								break;
				case _event_jackpot:		updateEventJackpot();								break;
			}
			break;
		case _statistic_sub:
			switch(eStatistic){
				case _stat_total:				updateStatTotal();								 break;
				case _stat_game:				updateStatGame();								 break;
				default: 	break;
			}
			break;
		case _setup_sub:
			switch(eGparam){
				case _gparam_total:			updateGparamTotal();								break;
				case _gparam_game:			updateGparamGame();									break;
			}
			break;
		case _machine_sub:
			switch(eMsetting){
				case _mset_limit:				updateMachineSetupLimit();						break;
				case _mset_params: 				updateMachineSetupParams();						break;
				case _mset_bill:				updateMachineSetupBill();						break;
				case _mset_coin:				updateMachineSetupCoin();						break;
				case _mset_init:				SetupLayer = updateMachineSetupInitial();		break;
				default:	break;
			}
			break;
		default:																break;
	}
/*
	if(*_SetupFormaUsb.pKey[0]) setLamp(LAMP_HOLD1_ON);
		else	setLamp(LAMP_HOLD1_OFF);
	if(*_SetupFormaUsb.pKey[1]) setLamp(LAMP_HOLD2_ON);
		else	setLamp(LAMP_HOLD2_OFF);
	if(*_SetupFormaUsb.pKey[2]) setLamp(LAMP_HOLD3_ON);
		else	setLamp(LAMP_HOLD3_OFF);
	if(*_SetupFormaUsb.pKey[3]) setLamp(LAMP_HOLD4_ON);
		else	setLamp(LAMP_HOLD4_OFF);
	if(*_SetupFormaUsb.pKey[4]) setLamp(LAMP_HOLD5_ON);
		else	setLamp(LAMP_HOLD5_OFF);
*/
	return ;
}



