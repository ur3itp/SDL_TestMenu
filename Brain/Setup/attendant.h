/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ATTENDANT_H
#define __ATTENDANT_H

  /* Includes ------------------------------------------------------------------*/

#include "setup.h"

typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

void initHandpay(void);
void attendantButton(uint code);
void updateRemoteIn(void);
void updateHandpay(void);

#endif /* __ATTENDANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


