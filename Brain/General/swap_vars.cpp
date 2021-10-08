/**
  ******************************************************************************
  * File Name          : swap_vars.cpp
  * Description        : non volatile game variable
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/

#include "swap_vars.h"

//---------------CONST GAME PARAMETERS CONSIST ROM-------------------------//

const char tNameGame1[] = 	"GAME1";
const char tNameGame2[] = 	"GAME2";
const char tNameGame3[] = 	"GAME3";
const char tNameGame4[] = 	"GAME4";
const char tNameGame5[] = 	"GAME5";
const char tNameGame6[] = 	"GAME6";
const char tNameGame7[] = 	"GAME7";
const char tNameGame8[] = 	"GAME8";
const char tNameGame9[] = 	"GAME9";
const char tNameGame10[] = 	"GAME10";
const char tNameGame11[] = 	"GAME11";
const char tNameGame12[] = 	"GAME12";
const char tNameGame13[] = 	"GAME13";
const char tNameGame14[] = 	"GAME14";
const char tNameGame15[] = 	"GAME15";
const char tNameGame16[] = 	"GAME16";
const char tNameGame17[] = 	"GAME17";
const char tNameGame18[] = 	"GAME18";
const char tNameGame19[] = 	"GAME19";
const char tNameGame20[] = 	"GAME20";

const ushort tableBetGrp1[] = {13, 1, 2, 3, 4, 5, 10, 20, 50, 70, 100, 200, 500};
const ushort tableBetGrp2[] = {10, 1, 2, 4, 8, 10, 20, 40, 100, 200};

const byte tableLineGrp1[] = {6, 1, 3, 5, 8, 10}; 
const byte tableLineGrp2[] = {6, 1, 5, 7, 10, 15};
const byte tableLineGrp3[] = {6, 1, 10, 20, 30, 40};
const byte tableLineGrp4[] = {2, 3};
const byte tableLineGrp5[] = {2, 5};
const byte tableLineGrp6[] = {2, 10};
const byte tableLineGrp7[] = {2, 20};
const byte tableLineGrp8[] = {2, 40};

const tagNoteGame DescriptGame[20] = {	
																{tNameGame1, tableBetGrp1, tableLineGrp1 },
																{tNameGame2, tableBetGrp1, tableLineGrp1 },
																{tNameGame3, tableBetGrp2, tableLineGrp5 },
																{tNameGame4, tableBetGrp2, tableLineGrp2 },																
																{tNameGame5, tableBetGrp2, tableLineGrp3 },																
																{tNameGame6, tableBetGrp1, tableLineGrp1 },
																{tNameGame7, tableBetGrp1, tableLineGrp1 },
																{tNameGame8, tableBetGrp1, tableLineGrp1 },
																{tNameGame9, tableBetGrp1, tableLineGrp1 },
																{tNameGame10, tableBetGrp1, tableLineGrp1 },
																{tNameGame11, tableBetGrp1, tableLineGrp1 },
																{tNameGame12, tableBetGrp1, tableLineGrp1 },
																{tNameGame13, tableBetGrp1, tableLineGrp1 },
																{tNameGame14, tableBetGrp1, tableLineGrp1 },
																{tNameGame15, tableBetGrp1, tableLineGrp1 },
																{tNameGame16, tableBetGrp1, tableLineGrp1 },
																{tNameGame17, tableBetGrp1, tableLineGrp1 },
																{tNameGame18, tableBetGrp1, tableLineGrp1 },
																{tNameGame19, tableBetGrp1, tableLineGrp1 },
																{tNameGame20, tableBetGrp1, tableLineGrp1 }	
														};

const char strMachineNumber[] ="000.000.001";
const char strMachine[] = "NovaMedia V+ (1/1258-D)";
const char strMachineVersion[] = "V8.20-3 / 1081 / 24 - MAR - 2019";
const char strEepromConf[] = "INT 82.0 / 779CDD64 / 1.024";
const char strMachineSha1[] = "SHA-1: D5455A76FC2C390BB79D";
const char strMachineSha2[] = "C6A12E9484F30BDFC67F";
const char strKernelVer[] = "V8.20-3 / 207 / 23-FEB-1976";
const char strBoardVer[] = "V3";
const char strBoardNumber[] = "000015DF6265";
const char strBootId[] = "2A36";
const char strBackPlainVer[] = "V1";
const char strRomCrc[] = "15BE5AAF";
const char strGameSelector[] = "V5.4.1 C1258.2 P32780 BV5.4.4";
		
const char strGameLadyCharm[]  = "92.19% LLady's Charm dlx v8.8-13 / 24-JUL-2013";
		
tagConstInfo ConstSystemInfo = 	{
														strMachineNumber,
														strMachine,
														strMachineVersion,
														strEepromConf,
														strMachineSha1,
														strMachineSha2,
														strKernelVer,
														strBoardVer,
														strBoardNumber,
														strBootId,
														strBackPlainVer,
														strRomCrc,
														strGameSelector,

														strGameLadyCharm
													};		

const char *strBillAcceptor[4] = {"BILL ACCEPTOR DISABLE", "IMPULSE", "ICT / SSP", "JCM WBA 21"}; 
const char *strCoinAcceptor[4]=  {"COIN ACCEPTOR DISABLE", "IMPULSE", "COIN COMPARATOR", ""};

//----------------------------------------------------------------------------------------------//
tagConstGamesParams ConstGameParams = {
																				{"NUN", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
																				"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"},
																				{"NUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"},
																				{ "USD", "EUR", "ISL", "RUR", "UAH"},
																				{1, 5, 10, 50, 100, 1000},	
																				{
																					{1, 10, 100 },
																					{10, 100, 1000},
																					{100, 1000, 10000},
																					{1000, 10000, 100000},
																					{10000, 100000, 1000000},
																					{100000, 1000000, 10000000}
																				},
																				{1,2,3,4,5},
																				{1,2,3,4,5,6,7,8,9,10}
																			};

//-------------------------------GLOBAL GAME NVRAM PARAMETERS-----------------------------------// 

tagGlobalParams swp_GlobalParams;
																			
uint var_SetupRemoteIn;									// hand set credit from setup
uint var_SetupHandpay;

ushort array_Bet[15];							// game array Bets

byte swp_service;

tagFixedParams swp_FixedParams;							// structure params for all games

tagBillParams swp_BillParams;
tagCoinParams swp_CoinParams;

tagTotalParams swp_RootParams;
tagTotalParams swp_OwnerParams;

tagMechCounters swp_MechCounters;

tagSystemParams swp_SystemParams;

tagPosition swp_Position;

tagEvent swp_EventMachine;
tagEvent swp_EventJackpot;
tagEvent swp_EventBill;
tagEvent swp_EventCoin;
tagEvent swp_EventRemotein;
tagEvent swp_EventHandpay;

tagGameParams swp_GameParams;

tagSetupGames swp_SetupGames;

tagStisticGame swp_StaticGame;

tagHistory swp_History;

unsigned char StateNvRam;
//--------------------------------------------------------------------------------------------------------//



