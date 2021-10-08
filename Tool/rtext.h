/*
 * rtext.h
 *
 *  Created on: Apr 3, 2020
 *      Author: lot
 */

#ifndef TOOL_RTEXT_H_
#define TOOL_RTEXT_H_

#include "../global.h"

extern const char *modOpenColor[MAX_COLOR];
extern const char modCloseColor[];

typedef struct{
	Uint8 is;
	Uint8 ie;
	Uint8 ixcolor;
	Uint8 flag;
}tRich;

class cRText{
	private:

	public:
		bool chend_raw(char *str, Uint8 Length);
};


#endif /* TOOL_RTEXT_H_ */
