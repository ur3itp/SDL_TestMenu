/**
  ******************************************************************************
  * File Name          : swap.cpp
  * Description        : non volatile data
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/

#include <time.h>
#include "utility.h"

static const char *modOpenColor[MAX_COLOR] = { "<color=aqua>", "<color==black>", "<color=blue>", "<color=brown>", "<color=cyan>",
		"<color=darkblue>", "<color=fuchsia>", "<color=green>", "<color=grey>", "<color=lightblue>", "<color=lime>",
		"<color=magenta>", "<color=maroon>", "<color=navy>", "<color=olive>", "<color=orange>" ,"<color=purple>",
		"<color=red>", "<color=silver>", "<color=teal>", "<color=white>", "<color=yellow>"};
static const char modCloseColor[] = "</color>";

void getStrDtime(char *astr, uint size, const DateTime *DTime){
	uint year = DTime->Year;
	uint month = DTime->Month;
	uint day = DTime->Day;
	uint hour = DTime->Hour;
	uint minute = DTime->Minute;
	uint second = DTime->Second;
	memset(astr, 0, size);
	if(DTime->Year < 2000 || DTime->Year > 2100)
		year = 2000;
	if(DTime->Month < 1 || DTime->Month > 12)
		month = 0;
	if(DTime->Day < 1 || DTime->Day > 31)
		day = 0;
	if(DTime->Hour > 24)
		hour = 0;
	if(DTime->Minute > 60)
		minute = 0;
	if(DTime->Second > 60)
		second = 0;
//	sprintf(astr,"%d-%s-%02d %02d-%02d-%02d", year, ConstGameParams.strMonth[month], day, hour, minute, second);
}
void getStrDate(char *astr, uint size, const DateTime *DTime){
	uint year = DTime->Year;
	uint month = DTime->Month;
	uint day = DTime->Day;
	memset(astr, 0, size);
	if(DTime->Year < 2000 || DTime->Year > 2100)
		year = 2000;
	if(DTime->Month < 1 || DTime->Month > 12)
		month = 0;
	if(DTime->Day < 1 || DTime->Day > 31)
		day = 0;
//	sprintf(astr,"%d-%s-%02d", year, ConstGameParams.strMonth[month], day);
}
void getStrTime(char *astr, uint size, const DateTime *DTime){
	uint hour = DTime->Hour;
	uint minute = DTime->Minute;
	uint second = DTime->Second;
	memset(astr, 0, size);
	if(DTime->Hour > 24)
		hour = 0;
	if(DTime->Minute > 60)
		minute = 0;
	if(DTime->Second > 60)
		second = 0;
	sprintf(astr,"%02d-%02d-%02d", hour, minute, second);		
}

void updateCurrentDTime(DateTime *CurrentDTime){
	time_t t;
	struct tm *dev_timer;
//	char ss[200];
	
	t = time(NULL);
	dev_timer = localtime(&t);
//	memset(ss, 0 , sizeof(ss));
//	sprintf(ss, "date %d %d %d time %d %d %d", dev_timer.year, dev_timer.month, dev_timer.day, dev_timer.hour, dev_timer.minutes, dev_timer.seconds);
//	HAL_UART_Transmit(&huart1,(uint8_t*)ss,sizeof(ss),500);
	
	CurrentDTime->Year = 	(ushort)dev_timer->tm_year;
	CurrentDTime->Month = 	(byte)dev_timer->tm_mon;
	CurrentDTime->Day =  	(byte)dev_timer->tm_mday;
	CurrentDTime->Hour = 	(byte)dev_timer->tm_hour;
	CurrentDTime->Minute = (byte)dev_timer->tm_min;
	CurrentDTime->Second = (byte)dev_timer->tm_sec;
}

void setCurrentDTime(DateTime *var){
	time_t t;
	struct tm *dev_timer;
//	char ss[200];
	t = time(NULL);
	dev_timer = localtime(&t);
	
	var->Year = (ushort)dev_timer->tm_year;
	var->Month = (byte)dev_timer->tm_mon;
	var->Day = (byte)dev_timer->tm_mday;
	var->Hour = (byte)dev_timer->tm_hour;
	var->Minute = (byte)dev_timer->tm_min;
	var->Second = (byte)dev_timer->tm_sec;
}

void UpdatePowerEvent(void){
	DateTime dt;
	updateCurrentDTime(&dt);
	swp_SystemParams.PowerEvent++;
	swp_SystemParams.PowerDateOn = dt;
	saveSystemParams();
}

static int _calc_color(char *str, int mod ){
	char *stra;
	char *strb;
	int i, icnt, ocnt;

	i = 0;
	icnt = ocnt = 0;
	strb = str;
	while(i < MAX_COLOR){
		stra = strstr(strb, modOpenColor[i]);
		if(stra == NULL){
			i++;
			continue;
		}
		strb = strstr(stra, modCloseColor);
		if(strb == NULL){
			icnt = ocnt = 0;
			break;
		}
		icnt += strlen(modOpenColor[i]);
		ocnt += strlen(modCloseColor);
		i++;
	};
	switch(mod){
		case 0 :	return icnt + ocnt;
					break;
		case 1 :	return icnt;
					break;
		case 2:		return ocnt;
					break;
		default:	return 0;
	}
}

void addstr(char *str1, const char *str2, int shift , int pos)
{
	int count1, count2, count3;
	int i, y;
//-------------------------------
	i = strlen(str1);
	y = strlen(str2);

	count1 = i - _calc_color(str1, 0);

	if(pos == 2){
		count2 = y - _calc_color((char*)str2, 0);
	} else {
		count2 = _calc_color((char*)str2, 0);;
	}

	count3 = shift - (Uint32) (count2 / 2);

	switch(pos){
		case 0: // equal raight
			do{
				str1[i++] = ' ';
			}while(count1++ < shift);
			for(int j=0; str2[j] !=0; j++){
				str1[i++] = str2[j];
			}	
			break;
		case 1: // equal left
			for( ; count1 < shift + count2 ; count1++){
				str1[i++] = ' ';
			}

			while(y > 0){
				str1[--i] = str2[--y]	;
			}
			break;
		case 2: //equal center	
			for( ; count1 < count3; count1++){
				str1[i++] = ' ';
			}
			for(int j=0; str2[j] !=0; j++){
				str1[i++] = str2[j];
			}	
			break;
		default: 
			break;	
	}		
}


void closeRaw(char *raw){
//	const char modL[] = "<color=silver>" ;
		const char modR[] = "</color>";
//	char buf[20];
//	int size = sizeof(modL);
	int i, j;
	int ix =0, iy =0;
//	char bufA[] = {'<','c','o','l','o','r','=','s','i','l','v','e','r','>'};
	char bufA[] = {'<','c','o','l','o','r','=','g','r','e','y','>'};	
	char bufB[sizeof(bufA)];
	char *writeBuf = bufB;
	char *readBuf = bufA;
	char *swap;
	bool endRaw = false;
	
	do{
		memset(writeBuf, 0,  sizeof(bufA));	
		i=0;
		do{
			if(0 == raw[ix]){
				endRaw = true;
			}
			writeBuf[i++] = raw[ix++];
		}while(!endRaw && i != sizeof(bufA));

		j=0;
		do{
				raw[iy++] = readBuf[j++];
		}while(j != sizeof(bufA));
		
		swap = writeBuf;
		writeBuf = readBuf; 
		readBuf = swap;
	}while(!endRaw);
	
	j=0;
	while(0 != readBuf[j]){
		raw[iy++] = readBuf[j++];
	};
	
	i=0;
	do{
		raw[iy++] = modR[i++];
	}while(i != sizeof(modR));

	raw[iy] = 0;
}
	
void formatMoney(int value, char* pTxt){
	char temp[20];
	uint sign;
	uint i = 0, y = 0, j = 0;
	bool m = false;
	
	if(value < 0){
		pTxt[j++] = '-';
		value = abs(value);	
	}
	
	do{
		m = false;
		i++;
		sign = value % 10;
		value /=  10;
		temp[y++] = (char)(sign + 0x30);
		if(i==2) 
			temp[y++] = ',';
		if(i < 3) 
			m  = true;
	}while((value > 0)||(m == true));
	
	while(y-- >0){
		pTxt[j++] = temp[y];
	}
	pTxt[j] = 0;
}

void formatCredit(int credit, char *pTxt){
	char temp[20];
	uint sign;
	uint i = 0, y = 0, j = 0;

	if(credit < 0){
		pTxt[j++] = '-';
		credit = abs(credit);	
	}

	do{
		i++;
		sign = credit % 10;
		credit /=  10;
		temp[y++] = (char)(sign + 0x30);		if((credit > 0) && (i % 3 == 0))
			temp[y++] = '.';
	}while(credit > 0);
	
	while(y-- >0){
		pTxt[j++] = temp[y];
	}
	pTxt[j] = 0;
}

void bytecpy(byte *pdest, byte *psend, uint size){
	for(uint i =0; i < size; i++){
		pdest[i] = psend[i];
	}
}

unsigned int sumarr(unsigned char *pbuf, int Length){
	unsigned int sum = 0;
	int i = 0;

	while(i < Length){
		sum += pbuf[i++];
	}
	return sum;
}
