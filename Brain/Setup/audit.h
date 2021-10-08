/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIT_H
#define __AUDIT_H

  /* Includes ------------------------------------------------------------------*/

#include "setup.h"

typedef unsigned 					short 	ushort;
typedef unsigned					int		uint;
typedef unsigned					char	uchar;	
typedef unsigned					char	byte;	

#define AUDITSHORT				6
#define AUDITLONG				9
#define ATTENDADMIN				3
#define ACCONTADMIN				5
#define DIAGNSADMIN				6
#define EVENADMIN				5
#define STATADMIN1				12
#define STATADMIN2				11	 
#define SETUPADMIN				2	 
#define MACHINEADMIN			6
#define CALIBRADMIN				3
	 
void auditInit(void);
void auditButton(uint code);
void auditUpdate(void);


#endif /* __AUDIT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

