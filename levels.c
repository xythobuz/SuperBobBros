/*
 * levels.c
 * By: Thomas Buck <taucher.bodensee@googlemail.com>
 * Visit: www.xythobuz.org
 */
#include "levels.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"

#define BLOCK 0
#define BOX 1
#define COIN 2


// levels[lvl.num.][type][y][index]
char ***levels[HOWMANYLEVELS] = { level1, level2, level3 };

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
	if ((what < 0) || (what > 2) || (y < 0) || (y > 7)) { // Kann sein das ich mich verzählt hab, und das ende deshalb nicht funktioniert... und nun? schauen, obs in level2.txt richtig is...
		return -1;
	}
	if ((level < 0) || (level >= HOWMANYLEVELS)) {
		return -1;
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

int removeBox(int level, char x, char y) {
	int size;
	int i;
	if ((x >= 0) && (y >= 0) && (x <= 15) && (y <= 7)) {
		size = getsizeBox(level, y);
		for (i = 0; i < size; i++) {
			if (levels[level][BOX][y][i] == x) {
				levels[level][BOX][y][i] = -1;
			}
		}
	} else {
		return -1;
	}
}

int removeCoin(int level, char x, char y) {
	int size;
	int i;
	if ((x >= 0) && (y >= 0) && (x <= 15) && (y <= 7)) {
		size = getsizeCoin(level, y);
		for (i = 0; i < size; i++) {
			if (levels[level][COIN][y][i] == x) {
				levels[level][COIN][y][i] = -1;
			}
		}
	} else {
		return -1;
	}
}

int isThere(int level, int what, char x, char y) {
	int i;
	int size;
	int flag = 0;
	if ((x >= 0) && (y >= 0) && (x <= 15) && (y <= 7)) {
		size = getSize(level, what, y);
		for (i = 0; i < size; i++) {
			if (levels[level][what][y][i] == x) {
				flag++;
			}
		}
		return flag;
	} else {
		return -1;
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


