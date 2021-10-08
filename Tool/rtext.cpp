/*
 * rtext.cpp
 *
 *  Created on: Apr 3, 2020
 *      Author: lot
 */

#include "rtext.h"

const char *modOpenColor[MAX_COLOR] = { "<color=aqua>", "<color==black>", "<color=blue>", "<color=brown>", "<color=cyan>",
		"<color=darkblue>", "<color=fuchsia>", "<color=green>", "<color=grey>", "<color=lightblue>", "<color=lime>",
		"<color=magenta>", "<color=maroon>", "<color=navy>", "<color=olive>", "<color=orange>" ,"<color=purple>",
		"<color=red>", "<color=silver>", "<color=teal>", "<color=white>", "<color=yellow>"};
const char modCloseColor[] = "</color>";

bool cRText::chend_raw(char *str, Uint8 Length){
	int i = 0;
	while(i < Length){
		if(str[i++] == 0){
			return true;
		}
	}
	return false;
}

