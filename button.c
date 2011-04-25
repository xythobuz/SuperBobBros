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
