/*
 * button.c
 * by xythobuz
 */
#include "fxlib.h"
#include "button.h"
#include "keybios.h"

char getButtons() {
	// Casio has broken shit... We do something about it...
	unsigned int c;
	GetKeyWait(KEYWAIT_HALTOFF_TIMEROFF, 0, 1, &c); 
	if (IsKeyDown(KEY_CTRL_UP)) {
		return 1; 
	}
	if (IsKeyDown(KEY_CTRL_RIGHT)) {
		return 2;
	}
	if (IsKeyDown(KEY_CTRL_LEFT)) {
		return 3;
	}
	if (IsKeyDown(KEY_CTRL_DOWN)) {
		return 4;
	}
	if (IsKeyDown(KEY_CTRL_EXIT)) {
		return -1;
	}
	return 0;
}
