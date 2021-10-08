/**
  ******************************************************************************
  * File Name          : pservice.cpp
  * Description        : external service 
  ******************************************************************************
*/	
/* Includes ------------------------------------------------------------------*/
#include<stdio.h>
#include<string.h>
#include <stdbool.h>

#include "pservice.h"
#include "../General/swap_vars.h"

void TogglePService(void){
	byte temp = swp_service & 0x01;
	if(temp == 1)	
		swp_service &= 0xFE;
	else
		swp_service |= 0x01;
}

bool getPService(void){
	if(swp_service & 0x01)
		return true;
	else
		return false;
}

void owner_clear(){
	
}

