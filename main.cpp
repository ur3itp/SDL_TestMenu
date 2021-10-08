/*
 * main.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: serg
 */

#include "Brain/sys_main.h"
#include "control.h"
#include "Tool/media.h"
#include "Setup/dosmode.h"
#include "Menu/menu.h"
#include "global.h"


cMedia oMedia;

int main(int argc, char* args[])
{
	Uint32 res;
	if(RET_OK != oMedia.InitMedia(800 , 600)){
		printf("error initialize  media system");
		return 0;
	}
	if(RET_OK != InitNet()){
		printf("error media Init");
		oMedia.CloseMedia();
		return 0;
	}
	if(RET_OK != InitSetup()){
		printf("error initialize setup part");
		oMedia.CloseMedia();
		return 0;
	}
	if(RET_OK != InitMenu()){
		printf("error initialize menu");
		oMedia.CloseMedia();
		return 0;
	}

	if(0 != BrainInit()){
		printf("error brain Init");
		oMedia.CloseMedia();
		return 0;
	}

	do{
		mSetTick();

		MediaUpdate();

		res = BrainUpdate();
	}while(res != 'Q');
//	printf("update %d", CurrentTime);
//	fflush(stdout);
	oMedia.CloseMedia();
	return 0;
}

