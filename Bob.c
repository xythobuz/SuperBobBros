/*
 * Bob.c
 * by xythobuz
 * visit: www.xythobuz.org
 */
#include "fxlib.h"
#include "timer.h"
#include "keybios.h"
#include "mechanics.h"

/*
 * AddIn_main()
 * Parameters are ignored!
 * Returns 1 if no error, 0 if error.
 */
int AddIn_main(int isAppli, unsigned short OptionNum) {
	
	unsigned int key;
	
	while(1) {
		Bdisp_AllClr_DDVRAM();
		locate(6, 3);
		Print((unsigned char*)"Super-Mario");
		locate(9, 4);
		Print((unsigned char*)"Clone");
		locate(6, 6);
		Print((unsigned char*)"by xythobuz");
		locate(1, 8);
		Print((unsigned char*)"F1:New Game");
		Bdisp_PutDisp_DD();
		GetKey(&key);
		if (key == KEY_CTRL_F1) {
			playLevel(1, 0);
		}
	}
	return 1;
}

// Casio's initialization code:
#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum) {
	return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section
