/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ACCOUNT_H
#define __ACCOUNT_H

  /* Includes ------------------------------------------------------------------*/

typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

#define NUMPAGEMASTER		4
#define NUMPAGEPERIOD		4
#define NUMPAGESECURE	 	2

void accountInit(void);
void accountButton(uint code);
void updateAccountMaster(void);
void updateAccountPeriodic(void);
void updateAccountMeter(void);
void updateAccountSecure(void);
void updateAccountClear(void);

#endif /* __ACCOUNT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
