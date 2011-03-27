/*
 * ai.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */
#include "ai.h"
#include "Draw.h"
#include "levels.h"

#define NUMOFSLOTS 4

// Four 'slots' for enemys, SlotX[4] = { type, x, y, toDelete, lastDir };
// Meaning of type:
// -1 = inactive
// 0 -> (HOWMANYENEMYS - 1) = Slot in use, thats the enemy type.

char Slot1[5] = { -1, 0, 0, 0, 0 };
char Slot2[5] = { -1, 0, 0, 0, 0 };
char Slot3[5] = { -1, 0, 0, 0, 0 };
char Slot4[5] = { -1, 0, 0, 0, 0 };
char *Slots[NUMOFSLOTS] = { Slot1, Slot2, Slot3, Slot4 };

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

int drawAI(int level, int offset) {
	char i;
	int type;
	char row;
	int slot;
	int Blockoffset = offset / 8;
	int diff;

	// Adding new Enemys to AI System
	for (i = Blockoffset; i < (Blockoffset + 16); i++) {
		for (type = 0; type < HOWMANYENEMYS; type++) {
			for (row = 0; row < 8; row++) {
				if (isEnemyRaw(level, i, row, type) > 0) {
					slot = getFreeSlot();
					if (slot != -1) {
						Slots[slot][0] = type;
						Slots[slot][2] = (row * 8);
						Slots[slot][3] = 0;
						Slots[slot][4] = 0;
						diff = i - Blockoffset;
						Slots[slot][1] = offset + (diff * 8);
						removeEnemyRaw(level, i, row, type);
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
				AI_EnemyA(level, i);
				break;
		}
	}

	drawThem(offset);

}

int drawThem(int offset) {
	int i;
	for (i = 0; i < NUMOFSLOTS; i++) {
		if ((Slots[i][0] != -1) && (Slots[i][3] != 1)) {
			drawEnemy((Slots[i][1] - offset), Slots[i][2], Slots[i][0]);
		}
	}
}

int whatsAt(int level, char x, char y) {
	if ((isBox(level, x, y)) || (isBlock(level, x, y))) {
		return 1;
	} else {
		return 0;
	}
}

int colLeft(int level, char x, char y) {
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
		return whatsAt(level, (x - 1), y);
	}
}

int colRight(int level, char x, char y) {
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
		return whatsAt(level, (x + 1), y);
		return 0;
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
	return flag;
}

int AI_EnemyA(int level, int slot) {
	if (Slots[slot][4] == 1) {
		// Walking Left
		if (colLeft(level, Slots[slot][1], Slots[slot][2])) {
			Slots[slot][4] = 0;
		} else {
			Slots[slot][1] -= 1;
		}
	} else {
		// Walking Right
		if (colRight(level, Slots[slot][1], Slots[slot][2])) {
			Slots[slot][4] = 1;
		} else {
			Slots[slot][1] += 1;
		}
	}
	if (colDown(Slots[slot][1], Slots[slot][2])) {
		// Nothing, there is a floor under us
	} else {
		Slots[slot][2] += 1;
	}
}

int isEnemy(int level, char x, char y, int whichEnemy) {
	int i;
	int off = 0;
	int tempx;
	int tempy;
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

int removeEnemy(int level, char x, char y, int whichEnemy) {
	int i;
	int off;
	int tempx;
	int tempy;
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
