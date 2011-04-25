/*
 * levels.c
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
#include "levels.h"
#include "ai.h"

#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

#define BLOCK 0
#define BOX 1
#define COIN 2
#define ENEMYA 3
#define ENEMYB 4
#define ENEMYC 5
#define ENEMYD 6


// levels[lvl.num.][type][y][index]
char ***levels[HOWMANYLEVELS] = { level1, level2, level3, level4 };

int getSize(int level, int what, char y) {
	// Unfortunately, we can not use sizeof(), because it works only in the same context the array was declared...
	// So now every level array has to end with -1. This works like \0 in a String...!
	
	/*
	int size = (sizeof(levels[level][what][y]) / sizeof(levels[level][what][y][0]));
	if ((size == 1) && (levels[level][what][y][0] == -1)) {
		return 0;
	} else {
		return size;
	}
	*/

	int i = 0;
	if ((what < 0) || (what > 6) || (y < 0) || (y > 7)) { 
		return 0;
	}
	if ((level < 0) || (level >= HOWMANYLEVELS)) {
		return 0;
	}
	while (levels[level][what][y][i] != -1) {
		i++;
	}
	return i;
}

int getsizeBlocks(int level, char y) {
	return getSize(level, BLOCK, y);
}

int getsizeBox(int level, char y) {
	return getSize(level, BOX, y);
}

int getsizeCoin(int level, char y) {
	return getSize(level, COIN, y);
}

int getsizeEnemy(int level, char y, int whichEnemy) {
	if ((whichEnemy < 0) || (whichEnemy > 3)) {
		return 0;
	}
	
	
	return getSize(level, (ENEMYA + whichEnemy), y);
}

int removeBox(int level, char x, char y) {
	int size;
	int i;
	if ((x >= 0) && (y >= 0) && (y <= 7)) {
		size = getsizeBox(level, y);
		for (i = 0; i < size; i++) {
			if (levels[level][BOX][y][i] == x) {
				levels[level][BOX][y][i] = -2; // Setting deleted ones to -1 was bad, because -1 is the end marker...
				return 0;
			}
		}
	} else {
		return 0;
	}
}

int removeCoin(int level, char x, char y) {
	int size;
	int i;
	if ((x >= 0) && (y >= 0) && (y <= 7)) {
		size = getsizeCoin(level, y);
		for (i = 0; i < size; i++) {
			if (levels[level][COIN][y][i] == x) { // Commenting this out was a stupid idea, because all coins then got removed. Also, this is only removing coins, not detecting them...
				levels[level][COIN][y][i] = -2;
				return 0;
			}
		}
	} else {
		return 0;
	}
}

int removeEnemyRaw(int level, char x, char y, int whichEnemy) {
	int size;
	int i;
	// char temp2;
	size = getsizeEnemy(level, y, whichEnemy);
	// temp2 = ENEMYA + whichEnemy;
	whichEnemy += ENEMYA;
	for (i = 0; i < size; i++) {
		// WTF? I can't remember writing this... Max?
		// if ((levels[level][temp2][y][i] == x) && (x > 8)) {	
		if (levels[level][whichEnemy][y][i] == x) {
			levels[level][whichEnemy][y][i] = -2;
			return 0;
		}
	}
}


int isThere(int level, int what, char x, char y) {
	int i;
	int size;

	if ((x >= 0) && (y >= 0) && (y <= 7)) {
		size = getSize(level, what, y);
		for (i = 0; i < size; i++) {
			if (levels[level][what][y][i] == x) {
				return 1;
			}
		}
		return 0;
	} else {
		return 0;
	}
}

int isBox(int level, char x, char y) {
	return isThere(level, BOX, x, y);
}

int isBlock(int level, char x, char y) {
	return isThere(level, BLOCK, x, y);
}

int isCoin(int level, char x, char y) {
	return isThere(level, COIN, x, y);
}

int isEnemyRaw(int level, char x, char y, int whichEnemy) {
	if ((whichEnemy < 0) || (whichEnemy > (HOWMANYENEMYS - 1))) {
		return 0;
	}
	return isThere(level, (ENEMYA + whichEnemy), x, y);
}
