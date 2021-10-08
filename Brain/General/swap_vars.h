/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SWAPVARS_H
#define __SWAPVARS_H

  /* Includes ------------------------------------------------------------------*/

typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

typedef struct{
	const char *pstrMachineNumber;
	const char *pstrMachine;
	const char *pstrMachineVersion;
	const char *pstrEepromConf;
	const char *pstrMachineSha1;
	const char *pstrMachineSha2;
	const char *pstrKernelVer;
	const char *pstrBoardVer;
	const char *pstrBoardNumber;
	const char *pstrBootId;
	const char *pstrBackPlainVer;
	const char *pstrRomCrc;
	const char *pstrGameSelector;	 

	const char *pstrGameLadyCharm;
}tagConstInfo;	
extern tagConstInfo ConstSystemInfo;

typedef struct{
	const char strMonth[13][4];							
	const char strDay[8][4];
	const char tableCurrency[5][4];
	const ushort tableDenom[6];
	const uint tableRemoteInCredit[6][3];	
	const byte tableReelTime[5];
	const byte tableGambleMult[10];	
}tagConstGamesParams;
extern tagConstGamesParams ConstGameParams;

typedef struct{
	ushort 	Year;
	byte  	Month;
	byte		Day;
	byte		Hour;
	byte		Minute;
	byte		Second;
//	byte		nu;
}DateTime;

typedef struct{
	byte 				name;
	byte				status;
	byte				reel[24];
	ushort 				maxPhase;
	ushort				curPhase;
	DateTime			datetime;
	uint				credit;
	uint	 			bet;
	uint 				win;
	uint				twin;
	byte 				gambles;
	uint				gamblIn;
	uint 				gamblOut;
	uint				coinIn;
	uint				billIn;
	uint 				remoteIn;
	uint				collect;
	uint				checksum;
}tagHistory;
extern tagHistory swp_History;

typedef struct{
	byte		TypeMaths;								// type mathimatic
	ushort 		TableDenom[8];							// modify donom table
	ushort 		fixMoneyDenom;
	ushort  	MainCoin;								// denomiation main coin
	ushort 		Tokenisation;							// number of credits per coin
	byte 		IdxCurrency;							// language index  { "USD", "EUR", "ISL", "RUR", "UAH"};
	ushort		MaximumBet;					 			// set maximum bet in credits 20000
	ushort 		MaxBetPerRow;							// set maximum bet per row in credits 1000
	byte 		AutoPlayInFeature;						// enable/disable bonus games run automatic or button start
	byte 		ReelTime;								// time reel
	byte 		GambleMult;								// amount step gamble
	uint 		CreditInLimit;							// maximum value of set credit
	uint 		CreditLimit;							// maximum value of credit which can be reached in game						
	uint		JackpotLimit;							// maximum value of win added to credit
	uint 		DoubleUpLimit;							// maximum value of win which can be reached in double game
	uint 		HoperPayoutLimit;						// maximum coin amount paid out by hopper
	uint		MinimumHandpay;							// minimum credit avaliable for handpay
	uint		EvenHandpay;							// size of credit rounding at handpay
	byte		GameList[60];							// list index uses games
	byte		GamePage;								// number page in game
	uint 		edRemoteInput			: 1;			// enable / disable remote input
	uint 		edHandpayCredit			: 1;			// enable / disable handpay credit
	uint	 	edBillInput				: 1;			// enable / disable bill acceptor
	uint 		edCoinInput				: 1;			// enable / disable coin acceptor
	uint 		edHopper				: 1;			// enable / disable hopper
	uint 		edHopperDump			: 1;			// enable / disable hopper dump by operator
	uint 		selKeybordMode			: 1;			// 12 or 8 keybord
	uint 		selSoundMode			: 1; 			// sound stereo or mono
	uint 		edSecondScreen			: 1;			// enable / disable top screen
	uint 		IdxRemoteinMode			: 4;			// multiplication factor of set credit by buttons HOLD3-5 on manual credit input
	uint 		selTouchscrMode			: 1;			// DEFAULT � basic mode EXPANDED � allows player to choose bet and line with the help of touch scree
	uint 		edKeyGameSel			: 1;			// enable/disable possibility of game choice by buttons HOLD1-5	
	uint 		edBellWinHigh			: 1;			// enable/disable ring bell to high win	
	uint 		selLineMode				: 1;			// choose lines mode choice
																			// options:
																			// DEFAULT � player can set desired amount of game lines if it is allowed by the game.
																			// FIXED � gaming machine will always set maximum amount of game lines
	uint 		selSetupProtect			: 2;			// choise type protect setup 	door, password, door + password, none
	uint 		selAlarmSound			: 2;			// shoise type alarm sound door, error, door + error, quiet
	uint 		checksum;
}tagFixedParams;
extern tagFixedParams swp_FixedParams; // params for all games

typedef struct{
	uint 	Credit;								// used credit
	ushort 	CurrentDenom;						// base denom
	byte	Language;							// base language
	uint 	checksum;
}tagGlobalParams;
extern tagGlobalParams swp_GlobalParams; 

typedef struct{
	uint TBetGame;
	uint TWinGame;
	uint TCntGame;

	uint ArrCntGame[15];
	uint ArrBetGame[15];
	uint ArrWinGame[15];
	
	uint ArrAnyWin[15];
	uint ArrNoWin[15];
	uint ArrScaterWin[15];
	uint ArrLinesPlay[5][15];
	uint ArrGamblPlay[15];
	uint ArrGamblIn[15];
	uint ArrGamblOut[15];
	uint checksum;
}tagStisticGame;
extern tagStisticGame swp_StaticGame;

typedef struct{
	const char *pNameGame;
	const ushort *pBetSeries;
	const byte *pLineSeries;	
}tagNoteGame;
extern const tagNoteGame DescriptGame[20];

typedef struct{
	byte eventMachine;
	byte eventBill;
	byte eventCoin;	
	byte eventRemotein;
	byte eventHandpay;
	byte eventJackpot;
	byte historyPage;
	byte currentGame;
	uint checksum;	
}tagPosition;
extern tagPosition swp_Position;

typedef struct{
	DateTime	datetime;
	uint 			value;
	byte 			type;
	uint 			checksum;	
}tagEvent;
extern tagEvent swp_EventMachine;
extern tagEvent swp_EventJackpot;
extern tagEvent swp_EventBill;
extern tagEvent swp_EventCoin;
extern tagEvent swp_EventRemotein;
extern tagEvent swp_EventHandpay;

typedef struct{
	ushort currentBet;
	byte currentLine;
	uint checksum;	
}tagGameParams;
extern tagGameParams swp_GameParams;

typedef struct{
	ushort 		minBet;
	ushort		maxBet;
	byte		minLine;
	byte		maxLine;
	ushort 		defBet;
	byte 		defLine;	
	uint 		checksum;		
}tagSetupGames;
extern tagSetupGames swp_SetupGames;

typedef struct{
	byte 	TypeBillAcceptor;					// number type bill , change from table
	uint 	BillValueCh[8];						// value one money
	byte 	edChanal;							// each bit enable / disable chanal
	byte 	DirInput;							// direction A B C D
	uint 	RootBillCountCh[8];					// count money throw chanel
	uint 	RootBillCreditCh[8];				// summa money trow chanel
	uint 	OwnerBillCountCh[8];
	uint 	OwnerBillCreditCh[8];
	uint 	checksum;
}tagBillParams;
extern tagBillParams swp_BillParams;

typedef struct{
	byte 	TypeCoinAcceptor;
	uint 	CoinValueCh[4];
	uint 	RootCoinCountCh[4];
	uint 	RootCoinCreditCh[4];

	uint 	OwnerCoinCountCh[4];
	uint 	OwnerCoinCreditCh[4];
	uint 	checksum;
}tagCoinParams;
extern tagCoinParams swp_CoinParams;

typedef struct{
	uint TotalIn;
	uint TotalIn_RemoteIn;
	uint TotalIn_coinIn;
	uint TotalIn_billIn;
	uint TotalIn_tokenIn;
	uint TotalOut;
	uint CoinOut;
	uint Handpay;
	
	uint TotalBet;
	uint TotalWon;
	uint WinToCredit;
	uint JPtoCredit;
	uint BonusToCredit;
	uint TotalGames;

	uint BillCountCh[8];
	uint BillCreditCh[8];
	
	uint CoinCountCh[4];
	uint CoinCreditCh[4];
	uint checksum;
}tagTotalParams;
extern tagTotalParams swp_RootParams;
extern tagTotalParams swp_OwnerParams;
	
typedef struct{
	uint MeterBet;
	uint MeterWin;
	uint MeterRemote;
	uint MeterHandpay;
	uint MeterBills;
	uint MeterDrop;
	uint MeterGames;
	uint MeterToken;
	uint MeterJP;
	uint checksum;
}tagMechCounters;
extern tagMechCounters swp_MechCounters;

typedef struct{
	DateTime 	RootInitBoard;
	DateTime 	OwnerInitBoard;

	DateTime 	MainDoorOpen;
	DateTime 	MainDoorClose;
	uint 		MainDoorCount;
	uint 		MainDoorEvent;

	DateTime 	DoorDoorOpen;
	DateTime 	DoorDoorClose;
	uint 		DoorDoorCount;
	uint 		DoorDoorEvent;

	DateTime 	PowerDateFail;
	DateTime 	PowerDateOn;
	uint 		PowerFailCount;
	uint 		PowerEvent;

	DateTime 	OwnerDateClear;
	uint 		OwnerClearCount;
	uint 		OwnerClearEvent;

	DateTime 	RootDateInit;
	uint 		RootInitEvent;
	uint 		RootInitCount;
	uint 		RootInitError;
	uint 		checksum;
}tagSystemParams;
extern tagSystemParams swp_SystemParams;


extern uint var_SetupRemoteIn;							// hand set credit from setup

extern uint var_SetupHandpay;

extern byte swp_service;


extern const char *strBillAcceptor[4];
extern const char *strCoinAcceptor[4];

extern unsigned char StateNvRam;

#endif /* __SWAPVARS_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
