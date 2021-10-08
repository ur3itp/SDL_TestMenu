/**
  ******************************************************************************
  * File Name          : core.cpp
  * Description        : general credit fuction 
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include <stdbool.h>

#include "../General/swap_vars.h"

void RemoteInCredit(uint code){
	var_SetupRemoteIn += ConstGameParams.tableRemoteInCredit[swp_FixedParams.IdxRemoteinMode][code];	
}


void HandPayCredit(void){
	var_SetupHandpay = swp_GlobalParams.Credit + var_SetupRemoteIn;	
	swp_GlobalParams.Credit = 0;
	var_SetupRemoteIn =0;
}
