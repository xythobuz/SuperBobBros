/*
 * button.c
 *
 * Copyright 2011 Thomas Buck, Max Nuding
 *
 * This file is part of SuperBobBros.
 * SuperBobBros is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SuperBobBros is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SuperBobBros. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "fxlib.h"
#include "button.h"
#include "keybios.h"
#include "fxlib.h"

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

int getNumber() {
	int nums[2] = { 0, 0 };
	int i = 0;
	unsigned char buf[2];
	buf[1] = '\0';

	Print((unsigned char*)"Ent. Num (2 DIG.):");
	Bdisp_PutDisp_DD();
	
	for (i = 0; i <= 1; i++) {
		while(1) {
			if (IsKeyDown(KEY_CHAR_0)) {
				nums[i] = 0;
				break;
			}
			if (IsKeyDown(KEY_CHAR_1)) {
				nums[i] = 1;
				break;
			}
			if (IsKeyDown(KEY_CHAR_2)) {
				nums[i] = 2;
				break;
			}
			if (IsKeyDown(KEY_CHAR_3)) {
				nums[i] = 3;
				break;
			}
			if (IsKeyDown(KEY_CHAR_4)) {
				nums[i] = 4;
				break;
			}
			if (IsKeyDown(KEY_CHAR_5)) {
				nums[i] = 5;
				break;
			}
			if (IsKeyDown(KEY_CHAR_6)) {
				nums[i] = 6;
				break;
			}
			if (IsKeyDown(KEY_CHAR_7)) {
				nums[i] = 7;
				break;
			}
			if (IsKeyDown(KEY_CHAR_8)) {
				nums[i] = 8;
				break;
			}
			if (IsKeyDown(KEY_CHAR_9)) {
				nums[i] = 9;
				break;
			}
		}
		buf[0] = nums[i] + '0';
		PrintC(buf);
		Bdisp_PutDisp_DD();
		Sleep(500);
	}
	return (nums[0] * 10) + nums[1];
}
