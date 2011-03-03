/*
 * levels.c
 * By: Thomas Buck <taucher.bodensee@googlemail.com>
 * Visit: www.xythobuz.org
 */
#include "levels.h"
#define BLOCK 0
#define BOX 1
#define COIN 2

// levels[lvl.num.][type][y][index]
char ***levels[1] = { level1 };

int getSize(int level, int what, char y) {
	int size = (sizeof(levels[level][what][y]) / sizeof(levels[level][what][y][0]));
	if ((size == 1) && (levels[level][what][y][0] == -1)) {
		return 0;
	} else {
		return size;
	}
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


