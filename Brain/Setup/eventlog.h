/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENTLOG_H
#define __EVENTLOG_H

  /* Includes ------------------------------------------------------------------*/

typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

void eventButton(uint code);
void updateEventMachine(void);
void updateEventBill(void);
void updateEventRemotein(void);
void updateEventHandpay(void);	 
void updateEventJackpot(void);	 
void EventLogInit(void);

#endif /* __EVENTLOG_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
