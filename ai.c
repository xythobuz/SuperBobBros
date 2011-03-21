/*
 * ai.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */
#include "ai.h"
#include "Draw.h"

#define NUMOFSLOTS 4

// Four 'slots' for enemys, SlotX[4] = { type, x, y, toDelete, originX, originY, lastDir };
// Meaning of type:
// -1 = inactive
// 0 -> (HOWMANYENEMYS - 1) = Slot in use, thats the enemy type.

char Slot1[7] = { -1, 0, 0, 0, 0, 0, 0 };
char Slot2[7] = { -1, 0, 0, 0, 0, 0, 0 };
char Slot3[7] = { -1, 0, 0, 0, 0, 0, 0 };
char Slot4[7] = { -1, 0, 0, 0, 0, 0, 0 };
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
	int i;
	int type;
	int row;
	int slot;
	int Blockoffset = offset / 8;
	int diff;

	// Adding new Enemys to AI System
	for (i = Blockoffset; i < (Blockoffset + 16); i++) {
		for (type = 0; type < HOWMANYENEMYS; type++) {
			for (row = 0; row < 8; row++) {
				if (isEnemyRaw(level, i, row, type)) {
					slot = getFreeSlot();
					if (slot != -1) {
						Slots[slot][0] = type;
						Slots[slot][2] = (row * 8);
						Slots[slot][3] = 0;
						Slots[slot][4] = i;
						Slots[slot][5] = row;
						Slots[slot][6] = 0;
						diff = i - Blockoffset;
						Slots[slot][1] = offset + (diff * 8);
						removeEnemyRaw(level, Slots[slot][4], Slots[slot][5], Slots[slot][0]);
						
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

int colLeft(char x, char y) {
	int i;
	int flag = 0;
	for (i = y; i < (y + 8); i++) {
		if (getPixel1((x - 1), i)) {
			flag++;
		}
	}
	return flag;
}

int colRight(char x, char y) {
	int i;
	int flag = 0;
	for (i = y; i < (y + 8); i++) {
		if (getPixel1((x + 8), i)) {
			flag++;
		}
	}
	return flag;
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

int AI_EnemyA(int slot) {
	if (Slots[slot][6] == 0) {
		// Walking Left
		if (colLeft(Slots[slot][1], Slots[slot][2])) {
			Slots[slot][6] = 1;
		} else {
			Slots[slot][1] -= 1;
		}
	} else {
		// Walking Right
		if (colRight(Slots[slot][1], Slots[slot][2])) {
			Slots[slot][6] = 0;
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
	for (i = 0; i < NUMOFSLOTS; i++) {
		int tempx = Slots[i][1] / 8;
		int tempy = Slots[i][2] / 8;
		if (Slots[i][0] == whichEnemy) {
			if (tempx == x) {
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
	for (i = 0; i < NUMOFSLOTS; i++) {
		int tempx = Slots[i][1] / 8;
		int tempy = Slots[i][2] / 8;
		if (Slots[i][0] == whichEnemy) {
			if (tempx == x) {
				if (tempy == y) {
					Slots[i][3] == 1;
				}
			}
		}
	}
	return 0;
}
