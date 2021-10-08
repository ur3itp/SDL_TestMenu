/*
 * tool.h
 *
 *  Created on: Mar 24, 2020
 *      Author: serg
 */

#ifndef BRAIN_SETUP_SETUP_H_
#define BRAIN_SETUP_SETUP_H_

#include "../sys_global.h"


typedef struct{
	unsigned char Layer;
	unsigned char *tBar[2][3];
	unsigned char *tRaw[RAW_MAX];
	unsigned char *tKey[3][5];
}tSetupForma;


typedef enum {_audit, _attendant, _accounting, _diagnostic, _eventlog, _history, _statistic1, _statistic2,
							_setup, _machine, _calibrate, _password,
							_audit_sub, _attendant_sub, _accounting_sub, _diagnostic_sub, _eventlog_sub,
							_statistic_sub, _setup_sub, _machine_sub, _calibrate_sub} tAudit;
typedef enum {_remote_in, _handpay} tAttendant;
typedef enum {_account_master, _account_period, _account_meter, _account_security, _account_clear} tAccount;
typedef enum {_diagnos_prgver, _diagnos_keytest, _diagnos_video, _diagnos_audio, _diagnos_self, _diagnos_touch} tDiagnos;
typedef enum {_event_machine, _event_bill, _event_remotein, _event_handpay,	_event_jackpot} tEvent;
typedef enum {_stat_total, _stat_game} tStatistic;
typedef enum {_gparam_total, _gparam_game} tGparam;
typedef enum {_mset_limit, _mset_params, _mset_bill, _mset_coin, _mset_init, _mset_game_onoff} tMsetting;

extern Uint8 TypeSetup;
extern tSetupForma SetupForm;
extern tAudit eAudit;
extern tAttendant eAttendant;
extern tAccount eAccount;
extern tDiagnos eDiagnos;
extern tEvent eEvent;
extern tStatistic eStatistic;
extern tGparam eGparam;
extern tMsetting eMsetting;

extern Uint8 NumberGame;
extern Uint8 SetupLayer;
extern Uint8 SubSetupLayer;

void WaitToSetup(Uint8 irq);
void Setup(Uint8 irq);
int SetupConstructor(void);
void ClearSetupForm(void);
int SetFormaBuf(int shift);
int SetCmdBuf(Uint8 cmd, int shift);
void RunSetup(Uint8 irq);

#endif /* BRAIN_SETUP_SETUP_H_ */
