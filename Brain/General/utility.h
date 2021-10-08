/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UTILITY_H
#define __UTILITY_H

  /* Includes ------------------------------------------------------------------*/

#include "../sys_global.h"
#include "swap.h"
#include "swap_vars.h"

typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

#define LEFT	1
#define RAIGHT	0
#define CENTERE	2


void updateCurrentDTime(DateTime *CruurentDTime);
void setCurrentDTime(DateTime *var);
void getStrDtime(char *Dtime, uint size, const DateTime *swp_FromInitBoard);
void getStrDate(char *Dtime, uint size, const DateTime *swp_FromInitBoard);
void getStrTime(char *Dtime, uint size, const DateTime *swp_FromInitBoard);
void addstr(char *str1, const char *str2, int shift, int pos);
void closeRaw(char *raw);
void formatMoney(int value, char* pTxt);
void formatCredit(int credit, char *pTxt);
void bytecpy(byte *pdest, byte *psend, uint size);
unsigned int sumarr(unsigned char *pbuf, int Length);

void UpdatePowerEvent(void);

#endif /* __UTILITY_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

