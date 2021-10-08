/**
  ******************************************************************************
  * File Name          : eventlog.c
  * Description        : setup event log
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../General/swap_vars.h"
#include "../General/utility.h"
#include "setup.h"
#include "../General/swap.h"
#include "../General/swap_vars.h"
#include "eventlog.h"


const char tBarEventlog1[] = 	"EVENT LOG > MACHINE EVENTS";
const char tBarEventlog2[] = 	"EVENT LOG > BILL ACCEPTOR EVENTS";
const char tBarEventlog3[] = 	"EVENT LOG > REMOTE IN EVENTS";
const char tBarEventlog4[] = 	"EVENT LOG > HANDPAY EVENTS";
const char tBarEventlog5[] =	"EVENT LOG > JACKPOT EVENTS";

const char tEventMachine1[] = "E EE06: Service mode entered";
const char tEventMachine2[] = "E EE07: Service mode left";
const char tEventMachine3[] = "E 63 3: Main door open";
const char tEventMachine4[] = "E 50 5: System power up";
const char tEventMachine5[] = "E 50 4: System shutdown";

const char *pTevent[5] = {tEventMachine1, tEventMachine2, tEventMachine3, tEventMachine4, tEventMachine5};

static byte eventPage=1;																	
static byte maxPage;

void EventLogInit(void){
	eventPage=1;
}

static void eventlogBar(){
//	memset(tBar, 0, sizeof(tBar));
	switch(eEvent){
		case _event_machine:	
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarEventlog1);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",eventPage, maxPage);
			break;
		case _event_bill:	
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarEventlog2);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",eventPage, maxPage);
			break;
		case _event_remotein:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarEventlog3);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",eventPage, maxPage);
			break;
		case _event_handpay:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarEventlog4);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",eventPage, maxPage);
			break;
		case _event_jackpot:
			sprintf((char*)SetupForm.tBar[1][0], "%s", tBarEventlog5);
			sprintf((char*)SetupForm.tBar[1][2],"Page %d/%d",eventPage, maxPage);
			break;
		default:	break;	
		}
}

static void eventlogKey(){
		sprintf((char*)SetupForm.tKey[1][0],"Back");
//		sprintf((char*)SetupForm.tKey[1][1],"");
//		sprintf((char*)SetupForm.tKey[1][2],"");
		if(maxPage > 1){
			sprintf((char*)SetupForm.tKey[1][3],"Prev Page");
			sprintf((char*)SetupForm.tKey[1][4],"Next Page");
		} else {
//			sprintf((char*)SetupForm.tKey[1][3],"");
//			sprintf((char*)SetupForm.tKey[1][4],"");
		}
}

void eventButton(uint code){

	if(code == 1){
		eAudit = _eventlog;		
		eventPage = 1;		
	}
	if(code == 4){
			eventPage --;
			if(eventPage == 0){
				eventPage = maxPage;		
			}
	}
	if(code == 5){
			eventPage++;
			if(eventPage > maxPage){
				eventPage = 1;
			}
	}
}

void updateEventMachine(){
	char ss[100];
	tagEvent event;
	byte count;
	
	getEvent(_eventMachine, &event, swp_Position.eventMachine);
	count = (event.value == 0) ? swp_Position.eventMachine : 100;

	maxPage = count / 25 + ((count % 25) ? 1 : 0);
	
	byte pos = swp_Position.eventMachine;
	
	eventlogBar();
	eventlogKey();
//	memset(tRaw, 0, sizeof(tRaw));

	if((pos == 0 && count == 0)){	
			addstr((char*)SetupForm.tRaw[3], "Event has no records", 40, CENTERE);
			return;
	}
	
	uint temp = (eventPage - 1) * 25;	
	while(temp){
		if(pos == 0){
			pos = 100;
		}
		pos --;
		temp --;
	}
// 25 amount raw in page	
	for(int i=0; i < 25; i++){

		if(pos == 0)
				pos = 100;
		pos--;
		
		getEvent(_eventMachine, &event, pos);
		if(event.value == 0)
			break;

		getStrDtime(ss, sizeof(ss), &event.datetime);
		sprintf((char*)SetupForm.tRaw[3+i], "%s %s", ss, pTevent[event.value - 1]);
	}	
}

void updateEventBill(){
	char ss[100];
	tagEvent event;	
	byte count;
	
	getEvent(_eventBill, &event, swp_Position.eventBill);
	count = (event.value == 0) ? swp_Position.eventBill : 100;

	maxPage = count / 25 + ((count % 25) ? 1 : 0);
	
	byte pos = swp_Position.eventBill;
	
	eventlogBar();
	eventlogKey();
//	memset(tRaw, 0, sizeof(tRaw));

	if((pos == 0 && count == 0)){	
			addstr((char*)SetupForm.tRaw[3], "Event has no records", 40, CENTERE);
			return;
	}
	
	uint temp = (eventPage - 1) * 25;
	while(temp){
		if(pos == 0){
			pos = 100;
		}
		pos --;
		temp --;
	}
	
	sprintf((char*)SetupForm.tRaw[2], "EVENT");
	addstr((char*)SetupForm.tRaw[2], "TIME", 35, LEFT);
	sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[2], ss, 50, LEFT);
	addstr((char*)SetupForm.tRaw[2], "CREDITS", 65, LEFT);
	
	for(int i=0; i < 25; i++){

		if(pos == 0)
			pos = 100;
		
		pos --;			
		getEvent(_eventBill, &event, pos);		
		if(event.value == 0)
			break;

		sprintf((char*)SetupForm.tRaw[4+i], "%d", (eventPage-1)*25 + i);
		getStrDtime(ss, sizeof(ss), &event.datetime);
		addstr((char*)SetupForm.tRaw[4+i], ss, 35, LEFT);
		formatMoney(swp_BillParams.BillValueCh[event.value] * swp_FixedParams.fixMoneyDenom, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 50, LEFT);
		formatCredit(swp_BillParams.BillValueCh[event.value], ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 65, LEFT);
	}	
}

void updateEventRemotein(){
	char ss[100];
	tagEvent event;	
	byte count;
	
	getEvent(_eventRemotein, &event, swp_Position.eventRemotein);
	count = (event.value == 0) ? swp_Position.eventRemotein : 100;

	maxPage = count / 25 + ((count % 25) ? 1 : 0);
	
	byte pos = swp_Position.eventRemotein;
	
	eventlogBar();
	eventlogKey();
//	memset(tRaw, 0, sizeof(tRaw));

	if((pos == 0 && count == 0)){	
			addstr((char*)SetupForm.tRaw[3], "Event has no records", 40, CENTERE);
			return;
	}
	
	uint temp = (eventPage - 1) * 25;
	while(temp){
		if(pos == 0){
			pos = 100;
		}
		pos --;
		temp --;
	}
	
	sprintf((char*)SetupForm.tRaw[2], "EVENT");
	addstr((char*)SetupForm.tRaw[2], "TIME", 35, LEFT);
	sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[2], ss, 50, LEFT);
	addstr((char*)SetupForm.tRaw[2], "CREDITS", 65, LEFT);
	
	for(int i=0; i < 25; i++){

		if(pos == 0)
			pos = 100;
		
		pos --;			
		getEvent(_eventRemotein, &event, pos);				
		if(event.value == 0)
			break;

		sprintf((char*)SetupForm.tRaw[4+i], "%d", (eventPage-1)*25 + i);
		getStrDtime(ss, sizeof(ss), &event.datetime);
		addstr((char*)SetupForm.tRaw[4+i], ss, 35, LEFT);
		formatMoney(event.value * swp_FixedParams.fixMoneyDenom, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 50, LEFT);
		formatCredit(event.value, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 65, LEFT);
	}	
}

void updateEventHandpay(){
	char ss[100];
	tagEvent event;
	byte count;
	
	getEvent(_eventHandpay, &event, swp_Position.eventHandpay);
	count = (event.value == 0) ? swp_Position.eventHandpay : 100;

	maxPage = count / 25 + ((count % 25) ? 1 : 0);
	
	byte pos = swp_Position.eventHandpay;
	
	eventlogBar();
	eventlogKey();
//	memset(tRaw, 0, sizeof(tRaw));

	if((pos == 0 && count == 0)){	
			addstr((char*)SetupForm.tRaw[3], "Event has no records", 40, CENTERE);
			return;
	}
	
	uint temp = (eventPage - 1) * 25;
	while(temp){
		if(pos == 0){
			pos = 100;
		}
		pos --;
		temp --;
	}
	
	sprintf((char*)SetupForm.tRaw[2], "EVENT");
	addstr((char*)SetupForm.tRaw[2], "TIME", 35, LEFT);
	sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[2], ss, 50, LEFT);
	addstr((char*)SetupForm.tRaw[2], "CREDITS", 65, LEFT);
	
	for(int i=0; i < 25; i++){

		if(pos == 0)
			pos = 100;
		
		pos --;		
		getEvent(_eventHandpay, &event, pos);						
		if(event.value == 0)
			break;

		sprintf((char*)SetupForm.tRaw[4+i], "%d", (eventPage-1)*25 + i);
		getStrDtime(ss, sizeof(ss), &event.datetime);
		addstr((char*)SetupForm.tRaw[4+i], ss, 35, LEFT);
		formatMoney(event.value * swp_FixedParams.fixMoneyDenom, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 50, LEFT);
		formatCredit(event.value, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 65, LEFT);
	}	
}

void updateEventJackpot(){
	char ss[100];
	tagEvent event;
	byte count;

	getEvent(_eventJackpot, &event, swp_Position.eventJackpot);
	count = (event.value == 0) ? swp_Position.eventJackpot : 100;
	
	byte pos = swp_Position.eventJackpot;

	eventlogBar();
	eventlogKey();
//	memset(tRaw, 0, sizeof(tRaw));

	if((pos == 0 && count == 0)){	
			addstr((char*)SetupForm.tRaw[3], "Event has no records", 40, CENTERE);
			return;
	}
	
	uint temp = (eventPage - 1) * 25;
	while(temp){
		if(pos == 0){
			pos = 100;
		}
		pos --;
		temp --;
	}
	
	sprintf((char*)SetupForm.tRaw[2], "EVENT");
	addstr((char*)SetupForm.tRaw[2], "TIME", 30, LEFT);
	addstr((char*)SetupForm.tRaw[2], "TYPE", 40, LEFT);
	sprintf(ss,"VALUE(%s)",ConstGameParams.tableCurrency[swp_FixedParams.IdxCurrency]);
	addstr((char*)SetupForm.tRaw[2], ss, 60, LEFT);
	addstr((char*)SetupForm.tRaw[2], "CREDITS", 75, LEFT);
	
	for(int i=0; i < 25; i++){

		if(pos == 0)
			pos = 100;
		
		pos --;			
		getEvent(_eventJackpot, &event, pos);								
		if(event.value == 0)
			break;

		sprintf((char*)SetupForm.tRaw[4+i], "%d", (eventPage-1)*25 + i);
		getStrDtime(ss, sizeof(ss), &event.datetime);
		addstr((char*)SetupForm.tRaw[4+i], ss, 30, LEFT);
		sprintf(ss, "%d", event.type);
		addstr((char*)SetupForm.tRaw[4+i], ss, 40, LEFT);
		formatMoney(event.value * swp_FixedParams.fixMoneyDenom, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 60, LEFT);
		formatCredit(event.value, ss);
		addstr((char*)SetupForm.tRaw[4+i], ss, 75, LEFT);
	}	
}
