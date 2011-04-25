/*
 * Draw.c
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
#include "Draw.h"
#include "models.h"

#define WalkingA 1
#define WalkingB 2
#define COIN 3
#define BLOCK 4

int lastWalkingState = WalkingA;

void set(char x, char y) {
	if (x >= 0) {
		if (x <= 127) {
			if (y >= 0) {
				if (y <= 63) {
					Bdisp_SetPoint_VRAM(x, y, 1);
				}
			}
		}
	}
}

void unset(char x, char y) {
	if (x >= 0) {
		if (x <= 127) {
			if (y >= 0) {
				if (y <= 63) {
					Bdisp_SetPoint_VRAM(x, y, 0);
				}
			}
		}
	}
}

void clear() {
	Bdisp_AllClr_VRAM();
}

void draw() {
	Bdisp_PutDisp_DD();
}

int getPlayerPixel(char player, char anim, char mirror, char x, char y) {
	// 0 <= x <= 6
	// 0 <= y <= 7
	char value = 0;
	if ((y < 8) && (y >= 0) && (x >= 0) && (x < 7)) {
		value = playerData[player][anim][y];
		if (mirror != 0) {
			x = 6 - x;
		}
		value <<= x;
		if ((value & 128) != 0) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

int getBCPixel(char x, char y, char what) {
	char value = 0;
	if ((y < 8) && (y >= 0) && (x >= 0) && (x < 8)) {
		switch (what) {
			case BLOCK:
				value = block[y];
				break;
			case COIN:
				value = coin[y];
				break;
		}
		value <<= x;
		if ((value & 128) != 0) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

int getBoxPixel(char x, char y) {
	char value = 0;
	if ((y < 7) && (y >= 0) && (x < 7) && (x >= 0)) {
		value = box[y];
		value <<= x;
		if ((value & 128) != 0) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

int getEnemyPixel(char x, char y, char enemy) {
	char value = 0;
	if ((y < 8) && (y >= 0) && (x < 8) && (x >= 0)) {
		value = enemys[enemy][y];
		value <<= x;
		if ((value & 128) != 0) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return -1;
	}
}

int drawPlayer(char player, char direction, char x, char y) {
	// 0 <= x <= 127
	// 0 <= y <= 63
	int i;
	int j;
	char anim = 0;
	char mirror = 0;
	if ((x < 0) || (y < 0) || (x > 127) || (y > 63)) {
		return -1;
	}
	switch (direction) {
		case 0:
			anim = 0;
			mirror = 0;
			break;
		case 1:
			if (lastWalkingState == WalkingA) {
				lastWalkingState = WalkingB;
				anim = 2;
			} else {
				lastWalkingState = WalkingA;
				anim = 1;
			}
			mirror = 0;
			break;
		case 2:
			if (lastWalkingState == WalkingA) {
				lastWalkingState = WalkingB;
				anim = 2;
			} else {
				lastWalkingState = WalkingA;
				anim = 1;
			}
			mirror = 1;
			break;
		case 3:
			anim = 4;
			mirror = 0;
			break;
		case 4:
			anim = 4;
			mirror = 1;
			break;
		case 5:
			anim = 3;
			mirror = 0;
			break;
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 8; j++) {
			if (getPlayerPixel(player, anim, mirror, i, j) == 1) {
				set((x + i), (y + j));
			}
		}
	}
	return 0;
}

int drawBlock(char x, char y) {
	int i;
	int j;
	if ((x < -7) || (y < 0) || (x > 127) || (y > 63)) {
		return -1;
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (getBCPixel(i, j, BLOCK) == 1) {
				set((x + i), (y + j));
			}
		}
	}
	return 0;
}

int drawCoin(char x, char y) {
	int i;
	int j;
	if ((x < -7) || (y < 0) || (x > 127) || (y > 63)) {
		return -1;
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (getBCPixel(i, j, COIN) == 1) {
				set((x + i), (y + j));
			}
		}
	}
	return 0;
}

int drawBox(char x, char y) {
	int i;
	int j;
	if ((x < -7) || (y < 0) || (x > 127) || (y > 63)) {
		return -1;
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			if (getBoxPixel(i, j) == 1) {
				set((x + i), (y + j));
			}
		}
	}
	return 0;
}

int drawEnemy(char x, char y, char enemy) {
	int i;
	int j;
	if ((x < -7) || (y < 0) || (x > 127) || (y > 63)) {
		return -1;
	}
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (getEnemyPixel(i, j, enemy) == 1) {
				set((x + i), (y + j));
			}
		}
	}
}
