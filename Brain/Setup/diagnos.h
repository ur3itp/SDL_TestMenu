/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DIAGNOS_H
#define __DIAGNOS_H

  /* Includes ------------------------------------------------------------------*/
#include "setup.h"

typedef unsigned 					short ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

#define NUMPAGEPRGVER		2	 

void diagnosButton(uint code);	 
void updateDiagnosVer(void);	 
void updateDiagnosTest(void);
uint updateDiagnosVideo(void);	 
uint updateDiagnosSound(byte *melody);	 
void updateDiagnosSelf(void);	 
void updateDiagnosTouch(void);	 

#endif /* __DIAGNOS_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
