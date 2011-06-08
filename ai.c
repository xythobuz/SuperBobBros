/*
 * ai.c
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
#include "ai.h"
#include "Draw.h"
#include "levels.h"
#include "mechanics.h"


// Rewrite: MAXSLOTS, dynamic memory allocation for slots, current slot amount
// in a var...


#define NUMOFSLOTS 1

// Four 'slots' for enemys, SlotX[5] = { type, x, y, toDelete, lastDir };
// Meaning of type:
// -1 = inactive
// 0 -> (HOWMANYENEMYS - 1) = Slot in use, thats the enemy type.

char Slot1[5] = { -1, 0, 0, 0, 0 };
char Slot2[5] = { -1, 0, 0, 0, 0 };
char Slot3[5] = { -1, 0, 0, 0, 0 };
char Slot4[5] = { -1, 0, 0, 0, 0 };
char *Slots[NUMOFSLOTS] = { Slot1 };
int lastlevel = 0;

char getPixel1(int x, int y) {
	return (char)Bdisp_GetPoint_VRAM(x, y);
}

int getFreeSlot() {
	int i;
	for (i = 0; i < NUMOFSLOTS; i++) {
		if (Slots[i][0] == -1) {
			return i;
		}
	}
	return -1;
}

int drawAI() {
	char i;
	int type;
	char row;
	int slot;
	int Blockoffset = offset / 8;
	int diff;

	if (level != lastlevel) {
		lastlevel = level;
		for (i = 0; i < NUMOFSLOTS; i++) {
			Slots[i][0] = -1;
		}
	}

	// Adding new Enemys to AI System
	for (i = Blockoffset; i < (Blockoffset + 16); i++) {
		for (type = 0; type < HOWMANYENEMYS; type++) {
			for (row = 0; row < 8; row++) {
				if (isEnemyRaw(level, i, row, type) == 1) {
					slot = getFreeSlot();
					if (slot != -1) {
						Slots[slot][0] = type;
						Slots[slot][2] = (row * 8);
						Slots[slot][3] = 0;
						Slots[slot][4] = 0;
						diff = i - Blockoffset;
						Slots[slot][1] = offset + (diff * 8);
						removeEnemyRaw(level, i, row, type); // CHANGED API!!!
					}
				}
			}
		}
	}

	// Removing deleted Enemys and updating existing ones...
	for (i = 0; i < NUMOFSLOTS; i++) {
		if (Slots[i][2] > 58) {
			Slots[i][3] = 1;
		}
		if (Slots[i][3] == 1) {
			Slots[i][0] = -1;
			continue;
		}
		switch(Slots[i][0]) {
			case -1:
				break;
			case 0:
				AI_EnemyA(i);
				break;
		}
	}

	drawThem();

}

int drawThem() {
	int i;
	for (i = 0; i < NUMOFSLOTS; i++) {
		if ((Slots[i][0] != -1) && (Slots[i][3] != 1)) {
			drawEnemy((Slots[i][1] - offset), Slots[i][2], Slots[i][0]);
		}
	}
}

int whatsAt(char x, char y) {
	
	if (isPlayer(level, x, y) == 1) {
		return 2;
	} else if ((isBox(level, x, y)) || (isBlock(level, x, y))) {
		return 1;
	} else {
		return 0;
	}
}

int isPlayer(char x, char y) {
	int i;
	char xP = xPlayer;
	while ((xP % 8) != 0) {
		xP--;
		i++;
	}
	xP /= 8;
	if ((xP == x) || (((xP + 1) == x) && (i > 0))) {
		xP = yPlayer;
		i = 0;
		while ((xP % 8) != 0) {
			xP--;
			i++;
		}
		xP /= 8;
		if ((xP == y) || (((xP + 1) == y) && (i > 0))) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

int colLeft(char x, char y) {
	int i;
	int flag = 0;
	for (i = y; i < (y + 8); i++) {
		if (getPixel1((x - 1), i)) {
			flag++;
		}
	}
	if (flag == 0) {
		return 0;
	} else {
		y /= 8;
		x /= 8;
		return whatsAt((x - 1), y);
	}
}

int colRight(char x, char y) {
	int i;
	int flag = 0;
	for (i = y; i < (y + 8); i++) {
		if (getPixel1((x + 8), i)) {
			flag++;
		}
	}
	if (flag == 0) {
		return 0;
	} else {
		y /= 8;
		x /= 8;
		return whatsAt((x + 1), y);
	}
}

int colDown(char x, char y) {
	int i;
	int flag = 0;
	for (i = x; i < (x + 8); i++) {
		if (getPixel1(i, (y + 8))) {
			flag++;
		}
	}
	return whatsAt(x, (y + 1));
}

int AI_EnemyA(int slot) {
	int temp;
	if (Slots[slot][4] == 1) {
		// Walking Left
		temp = colLeft(Slots[slot][1], Slots[slot][2]);
		if (temp == 1) {
			Slots[slot][4] = 0;
		} else if (temp == 2) {
			die();
		} else {
			Slots[slot][1] -= 1;
		}
	} else {
		// Walking Right
		temp = colRight(Slots[slot][1], Slots[slot][2]);
		if (temp == 1) {
			Slots[slot][4] = 1;
		} else if (temp == 2) {
			die();
		} else {
			Slots[slot][1] += 1;
		}
	}
	temp = colDown(Slots[slot][1], Slots[slot][2]);
	if (temp == 1) {
		// Nothing, there is a floor under us
	} else if (temp == 2) {
		die();
	} else {
		Slots[slot][2] += 1;
	}
}

int isEnemy(int level2, char x, char y, int whichEnemy) {
	int i;
	int off = 0;
	int tempx;
	int tempy;
	if (level2 != lastlevel) {
		return 0;
	}
	for (i = 0; i < NUMOFSLOTS; i++) {
		tempx = Slots[i][1];
		while ((tempx % 8) != 0) {
			off++;
			tempx--;
		}
		tempx /= 8;
		tempy = Slots[i][2] / 8;
		if (Slots[i][0] == whichEnemy) {
			if ((tempx == x) || ((off > 4) && (tempx == (x + 1)))) {
				if (tempy == y) {
					if (Slots[i][3] == 0) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int removeEnemy(int level2, char x, char y, int whichEnemy) {
	int i;
	int off;
	int tempx;
	int tempy;
	if (level2 != lastlevel) {
		return 0;
	}
	for (i = 0; i < NUMOFSLOTS; i++) {
		tempx = Slots[i][1];
		while ((tempx % 8) != 0) {
			off++;
			tempx--;
		}
		tempx /= 8;
		tempy = Slots[i][2] / 8;
		if (Slots[i][0] == whichEnemy) {
			if ((tempx == x) || ((off > 4) && (tempx == (x + 1)))) {
				if (tempy == y) {
					Slots[i][3] == 1;
				}
			}
		}
	}
	return 0;
}
