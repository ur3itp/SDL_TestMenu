/**
  ******************************************************************************
  * File Name          : swap.cpp
  * Description        : non volatile data
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//#include "setup.h"
#include "utility.h"
#include "swap.h"

static FILE *fpNvRam;
static byte *pBaseAdrNvram;

static uint CurrentNvramPageAdr;

static uint baseAdrShiftSwap = 0;
static uint adrShiftEventMachine;
static uint adrShiftEventBill;
static uint adrShiftEventCoin;
static uint adrShiftEventRemotein;
static uint adrShiftEventHandpay;
static uint adrShiftEventJackpot;

static uint adrShiftFixedParams;
static uint adrShiftGameParams;
static uint adrShiftSetupGames;

static uint adrShiftHistory;
static uint adrShiftStatistic;
static uint adrShiftPosition;

static uint adrShiftBillParams;
static uint adrShiftCoinParams;

static uint adrShiftRootParams;
static uint adrShiftOwnerParams;

static uint adrShiftMechCounters;

static uint adrShiftSystemParams;
static uint adrShiftGlobalParams;

etagEvent enumEvent;

//###############return value#########
// 0 - file reload to ram buffer
// 1 - error create ram buffer
// 2 - error create file nvram
// 3 - new create file nvram
int NvRamFileLoad(void){

	pBaseAdrNvram = new byte[NVRAM_SIZE];
	int size;

	if(NULL == pBaseAdrNvram){
		return 1;
	}
	fpNvRam = fopen("nvram.bin", "rb+");
	if(NULL == fpNvRam){
		fpNvRam = fopen("nvram.bin", "wb+");
	}
	if(NULL == fpNvRam){
		return 2;
	}
	fseek(fpNvRam, 0 , SEEK_END);
	size = ftello(fpNvRam);

	if(size != NVRAM_SIZE){
		fpNvRam = fopen("nvram.bin", "wb+");
		if(NULL == fpNvRam){
			return 2;
		}
		else{
			return 3;
		}
	}

	fseek(fpNvRam, 0, SEEK_SET);
	fread(pBaseAdrNvram, 1, NVRAM_SIZE, fpNvRam);
	return 0;
}

int NvRamFileSave(void){
	fseek(fpNvRam, 0, SEEK_SET);
	return fwrite(pBaseAdrNvram, 1, NVRAM_SIZE, fpNvRam);
}

void NvRamFileClose(void){
	fclose(fpNvRam);
}

static void initAdrShiftSwap(void){
	adrShiftHistory = baseAdrShiftSwap;
	adrShiftEventMachine = adrShiftHistory + sizeof(tagHistory) * MAX_RECORD_HISTORY;
	adrShiftEventBill = adrShiftEventMachine + sizeof(tagEvent) * MAX_RECORD_EVENT;
	adrShiftEventCoin = adrShiftEventBill + sizeof(tagEvent) * MAX_RECORD_EVENT;	
	adrShiftEventRemotein = adrShiftEventCoin + sizeof(tagEvent) * MAX_RECORD_EVENT;
	adrShiftEventHandpay = adrShiftEventRemotein + sizeof(tagEvent) * MAX_RECORD_EVENT;
	adrShiftEventJackpot = adrShiftEventHandpay + sizeof(tagEvent) * MAX_RECORD_EVENT;
	
	adrShiftFixedParams = adrShiftEventJackpot + sizeof(tagEvent) * MAX_RECORD_EVENT;
	adrShiftGameParams = adrShiftFixedParams + sizeof(tagFixedParams);
	adrShiftSetupGames = adrShiftGameParams + sizeof(tagGameParams) * MAX_AMOUNT_GAMES; 
	
	adrShiftStatistic = adrShiftSetupGames + sizeof(tagSetupGames) * MAX_AMOUNT_GAMES;
	adrShiftPosition = adrShiftStatistic + sizeof(tagStisticGame) * MAX_AMOUNT_GAMES; //20 games
	
	adrShiftBillParams = adrShiftPosition + sizeof(tagPosition);
	adrShiftCoinParams = adrShiftBillParams + sizeof(tagBillParams);
	
	adrShiftRootParams = adrShiftCoinParams + sizeof(tagCoinParams);
	adrShiftOwnerParams = adrShiftRootParams + sizeof(tagTotalParams);

	adrShiftMechCounters = adrShiftOwnerParams + sizeof(tagTotalParams);	
	
	adrShiftSystemParams = adrShiftMechCounters + sizeof(tagMechCounters);
	adrShiftGlobalParams = adrShiftSystemParams + sizeof(tagSystemParams);
	
}
//********param************
// shift - point begin region
// data - pointer write array
// size - size in byte array
// pos - number write structure
static void save_data(uint shift, byte *data, uint size, uint pos){
	uint address;
	byte *padr;

//	HAL_GPIO_WritePin(ENAWR_Port, ENAWR_Pin, GPIO_PIN_SET);
	
	address = BASE_ADR_NVRAM_PAGE1 + shift + size * pos ;
	padr = pBaseAdrNvram + address;
	for(uint i=0; i < size; i++){
		padr[i] = data[i];
	}
	address = BASE_ADR_NVRAM_PAGE2 + shift + size * pos;
	padr = pBaseAdrNvram + address;
	for(uint i=0; i < size; i++){
		padr[i] = data[i];
	}
//	HAL_GPIO_WritePin(ENAWR_Port, ENAWR_Pin, GPIO_PIN_RESET);
}

static uint read_data(uint adr, byte *data, uint size, uint pos){
	uint result = 0;
	uint address;
	byte *padr;
	
	address = adr + size * pos ;

	padr = pBaseAdrNvram + address;
	for(uint i=0; i < size; i++){
		data[i] = padr[i];
		result += data[i];
	}
	return result;
}

//************************************************************************************//
void savePosition(){
	uint checksum = 0;
	swp_Position.checksum =0;
	byte *pdata = (byte*) &swp_Position;
	
	for(uint i=0; i<sizeof(tagFixedParams); i++){
		checksum += pdata[i];
	}
	swp_Position.checksum = checksum;
	save_data(adrShiftPosition, pdata, sizeof(tagPosition), 0);
}

void saveHistory(){
	uint checksum = 0;
	swp_History.checksum =0;
	byte *phistory = (byte*) &swp_History;
	
	for(uint i=0; i<sizeof(tagHistory); i++){
		checksum += phistory[i];
	}
	swp_History.checksum = checksum;
	save_data(adrShiftHistory, phistory, sizeof(tagHistory), swp_Position.historyPage);
	
	swp_Position.historyPage++;
	if(swp_Position.historyPage == MAX_RECORD_HISTORY)
		swp_Position.historyPage = 0;
	savePosition();
}

void saveEvent(etagEvent nameEvent){
	uint checksum = 0;
	uint shiftAdr;
	uint pos;
	byte *pevent;
	tagEvent *p;
	
	switch(nameEvent){
		case _eventMachine:
			shiftAdr = adrShiftEventMachine;
			pevent = (byte*) &swp_EventMachine;
			p = &swp_EventRemotein;
			pos = swp_Position.eventMachine;
			break;
		case _eventBill:
			shiftAdr = adrShiftEventBill;
			pevent = (byte*) &swp_EventBill;
			p = &swp_EventBill;
			pos = swp_Position.eventBill;
			break;
		case _eventCoin:
			shiftAdr = adrShiftEventCoin;
			pevent = (byte*) &swp_EventCoin;
			p = &swp_EventCoin;
			pos = swp_Position.eventCoin;
			break;
		case _eventHandpay:
			shiftAdr = adrShiftEventHandpay;
			pevent = (byte*) &swp_EventHandpay;
			p = &swp_EventHandpay;
			pos = swp_Position.eventHandpay;
			break;
		case _eventRemotein:
			shiftAdr = adrShiftEventRemotein;
			pevent = (byte*) &swp_EventRemotein;
			p = &swp_EventRemotein;
			pos = swp_Position.eventRemotein;
			break;
		case _eventJackpot:
			shiftAdr = adrShiftEventJackpot;
			pevent = (byte*) &swp_EventJackpot;
			p = &swp_EventJackpot;
			pos = swp_Position.eventJackpot;
			break;
	}		

	for(uint i=0; i < sizeof(tagEvent); i++){
		checksum += pevent[i];
	}
	p->checksum = checksum;

	save_data(shiftAdr, pevent, sizeof(tagEvent), pos);
	
	switch(nameEvent){
		case _eventMachine:	
			swp_Position.eventMachine++;
			if(swp_Position.eventMachine == MAX_RECORD_EVENT)
				swp_Position.eventMachine =0;
			break;
		case _eventBill:
			swp_Position.eventBill++;
			if(swp_Position.eventBill == MAX_RECORD_EVENT)
				swp_Position.eventBill =0;
			break;
		case _eventCoin:
			swp_Position.eventCoin++;
			if(swp_Position.eventCoin == MAX_RECORD_EVENT)
				swp_Position.eventCoin =0;
			break;
		case _eventHandpay:
			swp_Position.eventHandpay++;
			if(swp_Position.eventHandpay == MAX_RECORD_EVENT)
				swp_Position.eventHandpay =0;
			break;
		case _eventRemotein:
			swp_Position.eventRemotein++;
			if(swp_Position.eventRemotein == MAX_RECORD_EVENT)
				swp_Position.eventRemotein =0;
			break;
		case _eventJackpot:
			swp_Position.eventJackpot++;
			if(swp_Position.eventJackpot == MAX_RECORD_EVENT)
				swp_Position.eventJackpot =0;
			break;
	}
	savePosition();
}

void saveFixedParams(){
	uint checksum = 0;
	swp_FixedParams.checksum =0;
	byte *pfix = (byte*) &swp_FixedParams;
	
	for(uint i=0; i<sizeof(tagFixedParams); i++){
		checksum += pfix[i];
	}
	swp_FixedParams.checksum = checksum;
	save_data(adrShiftFixedParams, pfix, sizeof(tagFixedParams), 0);
}

void saveGameParams(uint ngame){
	uint checksum = 0;
	swp_GameParams.checksum =0;
	byte *pgame = (byte*) &swp_GameParams;
	
	for(uint i=0; i<sizeof(tagGameParams); i++){
		checksum += pgame[i];
	}
	swp_GameParams.checksum = checksum;
	save_data(adrShiftGameParams, pgame, sizeof(tagGameParams), ngame);
}

void saveSetupGames(tagSetupGames *setupGames, uint ngame){
	uint checksum = 0;
	setupGames->checksum =0;
	byte *pgame = (byte*) setupGames;
	
	for(uint i=0; i<sizeof(tagSetupGames); i++){
		checksum += pgame[i];
	}
	setupGames->checksum = checksum;
	save_data(adrShiftSetupGames, pgame, sizeof(tagSetupGames), ngame);
}

void readSetupGames(tagSetupGames *setupGames, uint ngame){
	read_data( CurrentNvramPageAdr + adrShiftSetupGames, (byte*) setupGames, sizeof(tagSetupGames), ngame);	
}

void saveStaticGame(uint ngame){
	uint checksum = 0;
	swp_StaticGame.checksum =0;
	byte *pgame = (byte*) &swp_StaticGame;
	
	for(uint i=0; i<sizeof(tagStisticGame); i++){
		checksum += pgame[i];
	}
	swp_StaticGame.checksum = checksum;
	save_data(adrShiftStatistic, pgame, sizeof(tagStisticGame), ngame);
}

void saveBillParams(){
	uint checksum = 0;
	swp_BillParams.checksum =0;
	byte *pdata = (byte*) &swp_BillParams;
	
	for(uint i=0; i<sizeof(tagBillParams); i++){
		checksum += pdata[i];
	}
	swp_BillParams.checksum = checksum;
	save_data(adrShiftBillParams, pdata, sizeof(tagBillParams), 0);
}

void saveCoinParams(){
	uint checksum = 0;
	swp_CoinParams.checksum =0;
	byte *pdata = (byte*) &swp_CoinParams;
	
	for(uint i=0; i<sizeof(tagCoinParams); i++){
		checksum += pdata[i];
	}
	swp_CoinParams.checksum = checksum;
	save_data(adrShiftCoinParams, pdata, sizeof(tagCoinParams), 0);
}

void saveRootParams(){
	uint checksum = 0;
	swp_RootParams.checksum =0;
	byte *pdata = (byte*) &swp_RootParams;
	
	for(uint i=0; i<sizeof(tagTotalParams); i++){
		checksum += pdata[i];
	}
	swp_RootParams.checksum = checksum;
	save_data(adrShiftRootParams, pdata, sizeof(tagTotalParams), 0);
}

void saveOwnerParams(){
	uint checksum = 0;
	swp_OwnerParams.checksum =0;
	byte *pdata = (byte*) &swp_OwnerParams;
	
	for(uint i=0; i<sizeof(tagTotalParams); i++){
		checksum += pdata[i];
	}
	swp_OwnerParams.checksum = checksum;
	save_data(adrShiftOwnerParams, pdata, sizeof(tagTotalParams), 0);
}

void saveMechConters(){
	uint checksum = 0;
	swp_MechCounters.checksum =0;
	byte *pdata = (byte*) &swp_MechCounters;
	
	for(uint i=0; i<sizeof(tagMechCounters); i++){
		checksum += pdata[i];
	}
	swp_MechCounters.checksum = checksum;
	save_data(adrShiftMechCounters, pdata, sizeof(tagMechCounters), 0);	
}

void saveSystemParams(){
	uint checksum = 0;
	swp_SystemParams.checksum =0;
	byte *pdata = (byte*) &swp_SystemParams;
	
	for(uint i=0; i<sizeof(tagSystemParams); i++){
		checksum += pdata[i];
	}
	swp_SystemParams.checksum = checksum;
	save_data(adrShiftSystemParams, pdata, sizeof(tagSystemParams), 0);	
}

void saveGlobalParams(){
	uint checksum = 0;
	swp_GlobalParams.checksum =0;
	byte *pdata = (byte*) &swp_GlobalParams;
	
	for(uint i=0; i<sizeof(tagGlobalParams); i++){
		checksum += pdata[i];
	}
	swp_GlobalParams.checksum = checksum;
	save_data(adrShiftGlobalParams, pdata, sizeof(tagGlobalParams), 0);	
}

//-----------------------------------------------------------------------------//
static void	low_get_event(uint adr_ram, tagEvent *event, uint position){

	uint address = CurrentNvramPageAdr + adr_ram;
	read_data(address, (byte*) event, sizeof(tagEvent), position);
}

void getHistory(tagHistory *history, uint position){
	uint address = CurrentNvramPageAdr + adrShiftHistory;
	read_data(address, (byte*) history, sizeof(tagHistory), position);

}

void getStatistic(tagStisticGame *statistic, uint position){

	uint address = CurrentNvramPageAdr + adrShiftStatistic;
	read_data(address, (byte*) statistic, sizeof(tagStisticGame), position);

}

void getEvent(etagEvent eventName, tagEvent *event, uint position){

	if(position > 99)	position = 0;
	
	switch(eventName){
		case _eventMachine:	
				low_get_event(adrShiftEventMachine, event, position); 
				break;	
		case _eventBill: 
				low_get_event(adrShiftEventBill, event, position); 
				break;	
		case _eventCoin:
				low_get_event(adrShiftEventCoin, event, position); 
				break;	
		case _eventHandpay:
				low_get_event(adrShiftEventHandpay, event, position); 
				break;	
		case _eventRemotein:
				low_get_event(adrShiftEventRemotein, event, position); 
				break;	
		case _eventJackpot:
				low_get_event(adrShiftEventJackpot, event, position);
				break;	
		default:		break;
	}
}

void getArrBets(ushort *pbet, uint game){
	ushort bets[15];
	tagSetupGames  SetupGames;
	ushort minbet, maxbet;
	uint j;
	
	for(int i= 0; i < DescriptGame[game].pBetSeries[0]; i++){
			bets[i] =  DescriptGame[game].pBetSeries[i];
	}

	uint address = CurrentNvramPageAdr + adrShiftSetupGames;
	read_data(address, (byte*) &SetupGames, sizeof(tagSetupGames), game);
	
	minbet = SetupGames.minBet;
	maxbet = SetupGames.maxBet;
	
	j=1;
	for(int i=1; i < bets[0]; i++){
		if(bets[i] >= minbet && bets[i] <= maxbet){ 		
			pbet[j++] = bets[i];
		}
	}
	pbet[0] = j;
}

static void reset_dtime(DateTime *dt){
	dt->Year = 2018;
	dt->Day = 1;
	dt->Month = 1;
	dt->Hour = 0;
	dt->Minute = 0;
	dt->Second =0;
}

static void init_event(tagEvent *p){
	reset_dtime(&p->datetime);
	p->value = 0;
	p->type = 0;
}

void initRoot(){
	
	swp_History.name = 0;
	swp_History.status = 0;
	for(int i=0; i<24; i++){
		swp_History.reel[i] = 0;
	}
	swp_History.maxPhase = 0;
	swp_History.curPhase = 0;
	reset_dtime(&swp_History.datetime);

	swp_History.credit = 0;
	swp_History.bet = 0;	
	swp_History.win = 0;
	swp_History.twin = 0;
	
	swp_History.gambles = 0;
	swp_History.gamblIn = 0;
	swp_History.gamblOut = 0;
	
	swp_History.coinIn = 0;
	swp_History.billIn = 0;
	swp_History.remoteIn = 0;
	swp_History.collect = 0;
	
	for(int i=0; i < 200; i++){
		saveHistory();
	}	
	
	init_event(&swp_EventMachine);
	init_event(&swp_EventBill);
	init_event(&swp_EventCoin);
	init_event(&swp_EventRemotein);
	init_event(&swp_EventHandpay);
	init_event(&swp_EventJackpot);
	
	for(int i=0; i < 100; i++){
		saveEvent(_eventMachine);
		saveEvent(_eventBill);
		saveEvent(_eventCoin);
		saveEvent(_eventRemotein);
		saveEvent(_eventHandpay);
		saveEvent(_eventJackpot);
	}
	swp_FixedParams.TypeMaths = 2;								// 2 - 92% - 94%
	swp_FixedParams.AutoPlayInFeature = 1;
	swp_FixedParams.edBellWinHigh = 1;
	swp_FixedParams.fixMoneyDenom = 1;
	swp_FixedParams.MainCoin = 100;
	swp_FixedParams.Tokenisation = 1;
	swp_FixedParams.MaximumBet = 5000;
	swp_FixedParams.MaxBetPerRow = 100;
	swp_FixedParams.IdxCurrency = 0;
	swp_FixedParams.GambleMult = 5;
	swp_FixedParams.ReelTime = 2;
	swp_FixedParams.TableDenom[0] = 4;
	swp_FixedParams.TableDenom[1] = 1;
	swp_FixedParams.TableDenom[2] = 10;
	swp_FixedParams.TableDenom[3] = 100;
	swp_FixedParams.CreditInLimit = 200000;
	swp_FixedParams.CreditLimit = 1000000;
	swp_FixedParams.JackpotLimit = 450000;
	swp_FixedParams.DoubleUpLimit = 250000;
	swp_FixedParams.HoperPayoutLimit = 400;
	swp_FixedParams.MinimumHandpay = 0;
	swp_FixedParams.EvenHandpay = 0;
	swp_FixedParams.edRemoteInput = 1;
	swp_FixedParams.edHandpayCredit = 1;
	swp_FixedParams.edBillInput = 1;
	swp_FixedParams.edCoinInput = 1;
	swp_FixedParams.edHopper = 1;
	swp_FixedParams.edHopperDump = 1;
	swp_FixedParams.selKeybordMode = 1;
	swp_FixedParams.selSoundMode = 1;
	swp_FixedParams.selLineMode = 0;
	swp_FixedParams.edSecondScreen = 1;
	swp_FixedParams.IdxRemoteinMode = 0;
	swp_FixedParams.selTouchscrMode =0;
	swp_FixedParams.edKeyGameSel = 1;
	swp_FixedParams.selSetupProtect = 0; 		// door
	swp_FixedParams.selAlarmSound = 2;			// door + error			
	swp_FixedParams.GamePage = 1;
	for(int i = 0; i < swp_FixedParams.GamePage * 10; i++){
		swp_FixedParams.GameList[i] = i + 1;
	}
	
	saveFixedParams();
	
	for(int i=0; i<20; i++){
		swp_GameParams.currentBet = DescriptGame[i].pBetSeries[1];
		swp_GameParams.currentLine = DescriptGame[i].pLineSeries[1];

		swp_SetupGames.minBet = DescriptGame[i].pBetSeries[1];
		swp_SetupGames.maxBet = DescriptGame[i].pBetSeries[DescriptGame[i].pBetSeries[0] - 1];
		swp_SetupGames.defBet = DescriptGame[i].pBetSeries[1];
		swp_SetupGames.defLine = DescriptGame[i].pLineSeries[1];	
		swp_SetupGames.minLine = DescriptGame[i].pLineSeries[1];	
		swp_SetupGames.maxLine = DescriptGame[i].pLineSeries[DescriptGame[i].pLineSeries[0] - 1];
		
		memset(&swp_StaticGame, 0, sizeof(tagStisticGame));	
		saveGameParams(i);
		saveStaticGame(i);
		saveSetupGames(&swp_SetupGames, i);
	}
	
	memset(&swp_Position, 0, sizeof(tagPosition));
	savePosition();
	
	swp_BillParams.TypeBillAcceptor = 1;
	for(int i=0; i<8; i++){
		swp_BillParams.BillValueCh[i] = 0;
		swp_BillParams.RootBillCountCh[i] = 0;
		swp_BillParams.RootBillCreditCh[i] =0;
		swp_BillParams.OwnerBillCountCh[i] = 0;
		swp_BillParams.OwnerBillCreditCh[i] = 0;
	}		
	saveBillParams();

	swp_CoinParams.TypeCoinAcceptor = 0;
	for(int i=0; i<4; i++){
		swp_CoinParams.CoinValueCh[i] = 0;
		swp_CoinParams.RootCoinCountCh[i] = 0;
		swp_CoinParams.RootCoinCreditCh[i] =0;
		swp_CoinParams.OwnerCoinCountCh[i] = 0;
		swp_CoinParams.OwnerCoinCreditCh[i] = 0;
	}		
	saveCoinParams();
	
	memset(&swp_RootParams, 0, sizeof(tagTotalParams));
	saveRootParams();
	
	memset(&swp_OwnerParams, 0, sizeof(tagTotalParams));
	saveOwnerParams();

	memset(&swp_MechCounters, 0 , sizeof(tagMechCounters));
	saveMechConters();	
	
	reset_dtime(&swp_SystemParams.RootInitBoard);
	reset_dtime(&swp_SystemParams.OwnerInitBoard);
	reset_dtime(&swp_SystemParams.MainDoorOpen);
	reset_dtime(&swp_SystemParams.MainDoorClose);	
	swp_SystemParams.MainDoorCount = 0;
	swp_SystemParams.MainDoorEvent = 0;
	reset_dtime(&swp_SystemParams.DoorDoorOpen);
	reset_dtime(&swp_SystemParams.DoorDoorClose);	
	swp_SystemParams.DoorDoorCount = 0;
	swp_SystemParams.DoorDoorEvent = 0;
	reset_dtime(&swp_SystemParams.PowerDateFail);	
	reset_dtime(&swp_SystemParams.PowerDateOn);
	swp_SystemParams.PowerFailCount = 0;
	swp_SystemParams.PowerEvent = 0;
	reset_dtime(&swp_SystemParams.OwnerDateClear);
	swp_SystemParams.OwnerClearCount = 0;
	swp_SystemParams.OwnerClearEvent = 0;
	reset_dtime(&swp_SystemParams.RootDateInit);
	swp_SystemParams.RootInitCount = 0;
	swp_SystemParams.RootInitEvent = 0;
	swp_SystemParams.RootInitError = 0;
	
	saveSystemParams();
	
	swp_GlobalParams.Credit =0;
	swp_GlobalParams.CurrentDenom = ConstGameParams.tableDenom[1];
	saveGlobalParams();
}

void initOwner(){
	
	
}

static bool equal_checksum(uint retsum, uint checksum){
	uint temp;
	
	temp = checksum & 0xFF;
	temp += checksum >> 8 & 0xFF; 
	temp += checksum >> 16 & 0xFF;
	temp += checksum >> 24 & 0xFF; 	
	
	retsum -= temp;
	if(checksum == retsum)	
		return true;
	else
		return false;		
}
//#######return value###########
// 0 - checksum complete
// 1 - have bad data one bank
// 2 - corrupt data
uint startUpNvramPage(){
		
	char ss[100];
	
	uint retsum1, retsum2;
	uint errbank1 = 0, errbank2 = 0;
	uint errchecksum =0;
	{
		tagGlobalParams bank1, bank2;
		retsum1 = read_data(adrShiftGlobalParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagGlobalParams), 0);
		retsum2 = read_data(adrShiftGlobalParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagGlobalParams), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagSystemParams bank1, bank2;
		retsum1 = read_data(adrShiftSystemParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagSystemParams), 0);
		retsum2 = read_data(adrShiftSystemParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagSystemParams), 0);

		memset(ss, 0, sizeof(ss));		
		sprintf(ss, "retsum1 = %d, retsum2 = %d \n", retsum1, retsum2);
		printf("%s", ss);
		fflush(stdout);
		
		memset(ss, 0, sizeof(ss));		
		sprintf(ss, "checksum1 = %d, checksum2 = %d \n", bank1.checksum, bank2.checksum);
		printf("%s", ss);
		fflush(stdout);
		
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagMechCounters bank1, bank2;
		retsum1 = read_data(adrShiftMechCounters + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagMechCounters), 0);
		retsum2 = read_data(adrShiftMechCounters + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagMechCounters), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}		
	{
		tagTotalParams bank1, bank2;
		retsum1 = read_data(adrShiftRootParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagTotalParams), 0);
		retsum2 = read_data(adrShiftRootParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagTotalParams), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagTotalParams bank1, bank2;
		retsum1 = read_data(adrShiftOwnerParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagTotalParams), 0);
		retsum2 = read_data(adrShiftOwnerParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagTotalParams), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagBillParams bank1, bank2;
		retsum1 = read_data(adrShiftBillParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagBillParams), 0);
		retsum2 = read_data(adrShiftBillParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagBillParams), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{	
		tagCoinParams bank1, bank2;
		retsum1 = read_data(adrShiftCoinParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagCoinParams), 0);
		retsum2 = read_data(adrShiftCoinParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagCoinParams), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagPosition bank1, bank2;
		retsum1 = read_data(adrShiftPosition + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagPosition), 0);
		retsum2 = read_data(adrShiftPosition + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagPosition), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagFixedParams bank1, bank2;
		retsum1 = read_data(adrShiftFixedParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagFixedParams), 0);
		retsum2 = read_data(adrShiftFixedParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagFixedParams), 0);
		if(bank1.checksum != bank2.checksum){
			errchecksum++;
			if(!equal_checksum(retsum1,bank1.checksum))
				errbank1++;
			if(!equal_checksum(retsum2,bank2.checksum))
				errbank2++;
		}
	}
	{
		tagStisticGame bank1, bank2;
		for(int i=0; i < 20; i++){
			retsum1 = read_data(adrShiftStatistic + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagStisticGame), i);
			retsum2 = read_data(adrShiftStatistic + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagStisticGame), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
	}
	{
		tagGameParams bank1, bank2;
		for(int i=0; i < 20; i++){
			retsum1 = read_data(adrShiftGameParams + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagGameParams), i);
			retsum2 = read_data(adrShiftGameParams + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagGameParams), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
	}
	{
		tagSetupGames bank1, bank2;
		for(int i=0; i < 20; i++){
			retsum1 = read_data(adrShiftSetupGames + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagSetupGames), i);
			retsum2 = read_data(adrShiftSetupGames + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagSetupGames), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
	}
	{
		tagEvent bank1, bank2;
		for(int i=0; i < 100; i++){
			retsum1 = read_data(adrShiftEventMachine + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagEvent), i);
			retsum2 = read_data(adrShiftEventMachine + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagEvent), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
		for(int i=0; i < 100; i++){
			retsum1 = read_data(adrShiftEventRemotein + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagEvent), i);
			retsum2 = read_data(adrShiftEventRemotein + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagEvent), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
		for(int i=0; i < 100; i++){
			retsum1 = read_data(adrShiftEventHandpay + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagEvent), i);
			retsum2 = read_data(adrShiftEventHandpay + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagEvent), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
		for(int i=0; i < 100; i++){
			retsum1 = read_data(adrShiftEventJackpot + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagEvent), i);
			retsum2 = read_data(adrShiftEventJackpot + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagEvent), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
		for(int i=0; i < 100; i++){
			retsum1 = read_data(adrShiftEventCoin + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagEvent), i);
			retsum2 = read_data(adrShiftEventCoin + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagEvent), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
		for(int i=0; i < 100; i++){
			retsum1 = read_data(adrShiftEventBill + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagEvent), i);
			retsum2 = read_data(adrShiftEventBill + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagEvent), i);
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
	}
	{
		tagHistory bank1, bank2;
		for(int i=0; i < 200; i++){
			retsum1 = read_data(adrShiftHistory + BASE_ADR_NVRAM_PAGE1, (byte*) &bank1, sizeof(tagHistory), i);
			retsum2 = read_data(adrShiftHistory + BASE_ADR_NVRAM_PAGE2, (byte*) &bank2, sizeof(tagHistory), i);
			
			if(bank1.checksum != bank2.checksum){
				errchecksum++;
				if(!equal_checksum(retsum1,bank1.checksum))
					errbank1++;
				if(!equal_checksum(retsum2,bank2.checksum))
					errbank2++;
			}
		}
	}

	printf("adrShiftHistory = %X \n", adrShiftHistory);
	fflush(stdout);
	printf("adrShiftEventMachine = %X \n", adrShiftEventMachine);
	fflush(stdout);
	printf("error1 = %d, error2 = %d \n", errbank1, errbank2);
	fflush(stdout);

	if(errchecksum == 0){
		CurrentNvramPageAdr = BASE_ADR_NVRAM_PAGE1;
		return 0;
	} else {
		if(errbank2 == 0) {
			CurrentNvramPageAdr = BASE_ADR_NVRAM_PAGE2;
			return 1;
		}
		if(errbank1 == 0) {
			CurrentNvramPageAdr = BASE_ADR_NVRAM_PAGE1;
			return 1;
		}
	}
	return 2;
}

void restoreGameParams(){
	read_data( CurrentNvramPageAdr + adrShiftFixedParams, (byte*) &swp_FixedParams, sizeof(tagFixedParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftPosition, (byte*) &swp_Position, sizeof(tagPosition), 0);
	read_data( CurrentNvramPageAdr + adrShiftSystemParams, (byte*) &swp_SystemParams, sizeof(tagSystemParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftMechCounters, (byte*) &swp_MechCounters, sizeof(tagMechCounters), 0);
	read_data( CurrentNvramPageAdr + adrShiftGlobalParams, (byte*) &swp_GlobalParams, sizeof(tagGlobalParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftRootParams, (byte*) &swp_RootParams, sizeof(tagTotalParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftOwnerParams, (byte*) &swp_OwnerParams, sizeof(tagTotalParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftCoinParams, (byte*) &swp_CoinParams, sizeof(tagCoinParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftBillParams, (byte*) &swp_BillParams, sizeof(tagBillParams), 0);
	read_data( CurrentNvramPageAdr + adrShiftGameParams, (byte*) &swp_GameParams, sizeof(tagGameParams), swp_Position.currentGame);
	read_data( CurrentNvramPageAdr + adrShiftSetupGames, (byte*) &swp_SetupGames, sizeof(tagSetupGames), swp_Position.currentGame);
}

int TestBoardInit(){
	int tst;
	
	initAdrShiftSwap();

	tst = NvRamFileLoad();

	// bad nvram
	if(1 == tst){
		printf("RAM ERROR \n");
		fflush(stdout);
		return 1;
	}

	// create file error
	if(2 == tst){
		printf("FILE ERROR \n");
		fflush(stdout);
		return 2;
	}

	// bad data
	if(3 == tst){
		initRoot();
		NvRamFileSave();
		NvRamFileClose();
		printf("Create ini \n" );
		fflush(stdout);
		return 3;
	}
	//load done
	if(0 == tst){
		printf("nvram load \n" );
		fflush(stdout);
	}
	
	if(0 != startUpNvramPage()){
		printf("CHECKSUM ERROR \n");
		fflush(stdout);
		return 4;
	}

	restoreGameParams();
//	swp_TableDenom = 1;							// base denom
//	swp_IdxLangCurrency = 2;					// language index  { "USD", "EUR", "ISL", "RUR", "UAH"};
//	swp_IdxSetCredit = 2;			 	// group hand buttom set credit from setup
//	swp_Current_RemoteIn = 0;							// hand set credit from setup
//	swp_Current_Handpay = 0;
//	swp_service =0;

//	swp_RootTotalIn =0;
//	swp_RootTotalIn_RemoteIn =0;
//	swp_RootTotalIn_coinIn =0;
//	swp_RootTotalIn_billIn =0;
//	swp_RootTotalIn_tokenIn =0;
//	swp_RootTotalOut =0;
//	swp_RootCoinOut =0;
//	swp_RootHandpay =0;

//	swp_RootTotalBet = 800;
//	swp_RootTotalWon = 602;
//	swp_RootWinToCredit = 100;
//	swp_RootJPtoCredit = 502;
//	swp_RootBonusToCredit = 0;
//	swp_RootTotalGames = 100;	

//	swp_OwnerTotalIn =0;
//	swp_OwnerTotalIn_RemoteIn =0;
//	swp_OwnerTotalIn_coinIn =0;
//	swp_OwnerTotalIn_billIn =0;
//	swp_OwnerTotalIn_tokenIn =0;
//	swp_OwnerTotalOut =0;
//	swp_OwnerCoinOut =0;
//	swp_OwnerHandpay =0;

//	swp_OwnerTotalBet = 800;
//	swp_OwnerTotalWon = 602;
//	swp_OwnerWinToCredit = 100;
//	swp_OwnerJPtoCredit = 502;
//	swp_OwnerBonusToCredit = 0;
//	swp_OwnerTotalGames = 100;	

//	swp_RootInitBoard.Year = 2019;
//	swp_RootInitBoard.Month = 2;
//	swp_RootInitBoard.Day = 23;
//	swp_RootInitBoard.Hour = 14;
//	swp_RootInitBoard.Minute = 54;
//	swp_RootInitBoard.Second = 32;
//	
//	swp_OwnerInitBoard.Year = 2019;
//	swp_OwnerInitBoard.Month = 6;
//	swp_OwnerInitBoard.Day = 3;
//	swp_OwnerInitBoard.Hour = 4;
//	swp_OwnerInitBoard.Minute = 4;
//	swp_OwnerInitBoard.Second = 2;
//	
//	swp_TypeBillAcceptor = 2;
//	swp_BillValueCh[0] = 0;
//	swp_BillValueCh[1] = 2000;	
//	swp_BillValueCh[2] = 5000;		
//	swp_BillValueCh[3] = 10000;	
//	swp_BillValueCh[4] = 50000;		
//	swp_BillValueCh[5] = 100000;	
//	swp_BillValueCh[6] = 0;
//	swp_BillValueCh[7] = 0;	
//	
//	swp_RootBillCountCh[0] = 0;
//	swp_RootBillCountCh[1] = 10;
//	swp_RootBillCountCh[2] = 20;
//	swp_RootBillCountCh[3] = 30;
//	swp_RootBillCountCh[4] = 40;
//	swp_RootBillCountCh[5] = 50;	
//	swp_RootBillCountCh[6] = 60;
//	swp_RootBillCountCh[7] = 0;	
//	
//	swp_TypeCoinAcceptor = 1;	
//	
//	for(int i=0; i<8; i++){
//		swp_RootBillCreditCh[i] =0;
//		swp_RootBillTotal[i] =0;	
//		swp_OwnerBillCreditCh[i] =0;
//		swp_OwnerBillTotal[i] =0;	
//	}
//	swp_MeterBet = 10000;
//	swp_MeterWin = 3875;
//	swp_MeterRemote = 363784;
//	swp_MeterHandpay = 2637463;
//	swp_MeterBills = 324;
//	swp_MeterDrop = 0;
//	swp_MeterGames = 88934;
//	swp_MeterToken =0;	
//	

//	for(int i=0; i < 110; i++){
//		swp_EventMachine.value = i+1;
//		setCurrentDTime(&swp_EventMachine.datetime);
//		saveEvent(_eventMachine);
//	}

//	swp_eventBill.position = 10;
//	for(int i=0; i < 100; i++){
//		swp_eventBill.event[i].value = (byte) ((rand()% 5)+1);
//	}

//	swp_eventRemotein.position = 15;
//	for(int i=0; i < 100; i++){
//		swp_eventRemotein.event[i].value = ((rand()% 10000)+1);
//	}

//	swp_eventHandpay.position = 15;
//	for(int i=0; i < 100; i++){
//		swp_eventHandpay.event[i].value = ((rand()% 10000)+1);
//	}

//	swp_eventJackpot.position = 20;
//	for(int i=0; i < 100; i++){
//		swp_eventJackpot.event[i].value = ((rand()% 10000)+1);
//		swp_eventJackpot.event[i].type = ((rand()% 3)+1);
//	}

	for(int i=0; i < 210; i++){
		memset(&swp_History, 0, sizeof(tagHistory));
		swp_History.status = 3;
		swp_History.name = ((rand()% 3)+1);
		swp_History.maxPhase = 1;
		swp_History.curPhase = 1;
		swp_History.credit = (rand()% 10000);
		swp_History.bet = i;
		swp_History.win = i;
		setCurrentDTime(&swp_History.datetime);
		saveHistory();
	}
//	
//	swp_grp1_bet_min = 1;
//	swp_grp1_bet_max = 200;
//	
//	for(int i=0; i<20; i++){
//		swp_stisticGame[i].TBetGame = (rand()% 10000);
//		swp_stisticGame[i].TWinGame = (rand()% 10000);
//		swp_stisticGame[i].TCntGame = (rand()% 10000);
//		swp_stisticGame[i].get_bet_game = &get_bet_grp1;
//		swp_stisticGame[i].get_line_game = &get_line_grp1;
//		for(int j=0; j < get_bet_grp1(0xff); j++){
//			swp_stisticGame[i].ArrBetGame[j] = (rand()% 100);
//			swp_stisticGame[i].ArrWinGame[j] = (rand()% 100);
//			swp_stisticGame[i].ArrCntGame[j] = (rand()% 100);
//			swp_stisticGame[i].ArrAnyWin[j] = (rand()% 100);
//			swp_stisticGame[i].ArrNoWin[j] = (rand()% 100);
//			swp_stisticGame[i].ArrGamblIn[j] = (rand()% 100);
//			swp_stisticGame[i].ArrGamblOut[j] = (rand()% 100);
//			swp_stisticGame[i].ArrGamblPlay[j] = (rand()% 1000);
//			for(int x=0; x < 5; x++){
//				swp_stisticGame[i].ArrLinesPlay[x][j] = (rand()% 100);
//			}
//			swp_stisticGame[i].ArrScaterWin[j] = (rand() % 100);
//		}
//	}
	return 0;
}



