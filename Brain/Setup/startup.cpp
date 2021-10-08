/*
 * startup.cpp
 *
 *  Created on: Mar 24, 2020
 *      Author: serg
 */
#include "../sys_main.h"
#include "../General/utility.h"
#include "../General/swap_vars.h"
#include "../General/queue.h"
#include "startup.h"
#include "setup.h"


//extern int get_sysbuf_status(void);
void SndSysBuf(Uint32 Length);

const char asf1[] = "Processor initialisation";
const char asf2[] = "Initial video modes: P1:2-1 P2:2-1 P3:nc P4:nc";
const char asf3[] = "494MB dynamic memory test";
const char asf4[] = "Program ROM test";
const char asf5[] = "ISE test";
const char asf6[] = "Running nucleus configuration";
const char asf7[] = "Configuration EEPROM (INT 82.0) test";
const char asf8[] = "Switching to runlevel";
const char asf9[] = "Mounting static ram - 4MB found";
const char asf10[] = "System driver startup";
const char asf11[] = "Network initialisation";
const char asf12[] = "Nucleus startup";
const char asf13[] = "Loading machine constructor";
const char asf14[] = "Enumerating device F035/3503/0 (AGI GAME SELECTOR)";
const char asf15[] = "Enumerating device F032/3205/9 (STANDART TICKET)";
const char asf16[] = "Enumerating device F005/0500/2 (NOVOMATIC P380)";
const char asf17[] = "Enumerating device F00B/0B00/0 (MICROTOUCH SMT2/3)";
const char asf18[] = "Starting PremiumV+Gaminator5 V8.20-3";
const char ase1[]  = "<color=red>Non volatile memory physical bad</color>";
const char ase4[]  = "<color=red>Non volatile memory data destroy</color>";
const char ase2[]  = "<color=red>Non volatile memory checksum bad</color>";
const char ase3[]  = "<color=red>escape memory error</color>";
const char ass1[] = "[ <color=green>OK</color> ]";
const char ass2[] = "[ <color=aqua>GAME</color> ]";
const char ass3[] = "[ <color=green>COMPLETE</color> ]";
const char ass4[] = " ";

const char *pTxtStartUp[][2] = {	{asf1, ass1}, {asf2, ass1}, {asf3, ass1}, {asf4, ass1}, {asf5, ass1}, {asf6, ass1},
										{asf7, ass1}, {asf8, ass2}, {asf9, ass1}, {asf10, ass1}, {asf11, ass1}, {asf12, ass3},
										{asf13, ass1}, {asf14, ass1}, {asf15, ass1}, {asf16, ass1}, {asf17, ass1}, {asf18, ass4} 	};

static Uint8 cnt =0;

void startup(Uint8 irq){
	int Length, shift;
	//char str[120];
	int i =0 ;

	Sys_Queue_Clear(irq);
	ClearSetupForm();

    addstr((char*)SetupForm.tRaw[0], "Welcome to Coolfire kernel V8.20-3", 40, CENTERE);

    while(i < cnt && i < 17){
    	addstr((char*)SetupForm.tRaw[i+3], pTxtStartUp[i][0], 0, RAIGHT);
    	addstr((char*)SetupForm.tRaw[i+3], pTxtStartUp[i][1], 80, LEFT);
    	i++;
    }

    if(cnt == 17){
    	switch(StateNvRam){
    		case 1: //ram bad
    			addstr((char*)SetupForm.tRaw[cnt + 3], ase3, 0, RAIGHT);
    			break;
    		case 2: // nvram file bad
    			addstr((char*)SetupForm.tRaw[cnt + 3], ase1, 0, RAIGHT);
    			break;
    		case 3: //memory data destroy
    			addstr((char*)SetupForm.tRaw[cnt + 3], ase4, 0, RAIGHT);
    			break;
    		case 4: //checksum bad
    			addstr((char*)SetupForm.tRaw[cnt + 3], ase2, 0, RAIGHT);
    			break;
    		case 0: // nvram checksum ok
    			addstr((char*)SetupForm.tRaw[cnt + 3], pTxtStartUp[17][0], 0, RAIGHT);
    			break;
    	}
    }

	shift = SetByteBuf(CMD_BOOT, 0);
	SetupForm.Layer = 0;
	Length = SetFormaBuf(shift);
	SndSysBuf(Length);
	if(cnt == 17){
		UpdatePowerEvent();
		Loading(xxxSTARTUP, xxxNONE);
	}
	else{
		Sys_Queue_AddFunc(startup, 100);
		cnt++;
	}
//	printf("startup");
//	fflush(stdout);
}

