
#include"inout.h"

Uint32 KeyCode;

Uint8 PIN_HOLD1;
Uint8 PIN_HOLD2;
Uint8 PIN_HOLD3;
Uint8 PIN_HOLD4;
Uint8 PIN_HOLD5;
Uint8 SIG_QUIT;


Uint32 getKeyCode(void){
	Uint32 temp = KeyCode;
	KeyCode = 0;
	return temp;
}

void ProgramIsRunning()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type){
			case SDL_QUIT:
				SIG_QUIT = 'Q';
				printf("quit");
				fflush(stdout);
				break;
			case SDL_KEYDOWN:
				switch((uint)event.key.keysym.sym){
					case SDLK_e:	KeyCode = 'E';	break;
					case SDLK_s:	KeyCode = 'S';	break;
					case SDLK_c:	KeyCode = 'C';	break;
					case SDLK_n:	KeyCode = 'N';	break;
					case SDLK_d: 	KeyCode = 'D';	break;
					case SDLK_1:	KeyCode = '1';  PIN_HOLD1 = 1;	break;
					case SDLK_2:	KeyCode = '2';  PIN_HOLD2 = 1;	break;
					case SDLK_3:	KeyCode = '3';  PIN_HOLD3 = 1;	break;
					case SDLK_4:	KeyCode = '4';  PIN_HOLD4 = 1;	break;
					case SDLK_5:	KeyCode = '5';  PIN_HOLD5 = 1;	break;
				}
				break;
			case SDL_KEYUP:
				KeyCode = 0;
				switch((uint)event.key.keysym.sym){
					case SDLK_1:	 PIN_HOLD1 = 0;	break;
					case SDLK_2:	 PIN_HOLD2 = 0;	break;
					case SDLK_3:	 PIN_HOLD3 = 0;	break;
					case SDLK_4:	 PIN_HOLD4 = 0;	break;
					case SDLK_5:	 PIN_HOLD5 = 0;	break;
				}
				break;
		}
	}
}
