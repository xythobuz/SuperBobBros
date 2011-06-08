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
/*
 * Level Data is read from a binary file in the calculator memory. The current
 * level gets loaded out of this file and placed in RAM. While playing, it
 * gets manipulated there only. Level changes are detected automatically...
 *
 */
#include "levels.h"
#include "fxlib.h"
#include "filebios.h"
#include <stdlib.h>
#include "example.h"
#include "ai.h"

#define BLOCK 0
#define BOX 1
#define COIN 2
#define EXIT 3
#define ENEMYA 4
#define ENEMYB 5
#define ENEMYC 6
#define ENEMYD 7

const FONTCHARACTER levelFile[18] = { '\\', '\\', 'f', 'l', 's', '0',
	'\\', 'b', 'o', 'b', '.', 'l', 'v', 'l', '\0' }; // "bob.lvl" in Storage

char *bloc[8];
char *bo[8];
char *coi[8];
char *exi[1];
char *enemA[8];
char *enemB[8];
char *enemC[8];
char *enemD[8];

int loadedLevel = -1;

// curLevel[type][y][index]
char **curLevel[8] = { bloc, bo, coi, exi, enemA, enemB, enemC, enemD };

int loadLevel(int level) {
	// Loads given level into curLevel[][][]...
	int ret, type, y, i, tmp, count = 0, oldpos = 0, pos = 0, size;
	char buf = 0;

	ret = Bfile_OpenFile(levelFile, _OPENMODE_READ);
	if (ret < 0) {
		// Error! Try creating file
		ret = Bfile_CreateFile(levelFile, (exampleSize + 1)); // Some bytes for level end marker
		if (ret < 0) {
			// Error again. Aborting!
			PopUpWin(1);
			locate(7, 4);
			Print((unsigned char*)"Error: 42");
			Bdisp_PutDisp_DD();
			Sleep(2000);
			return -1;
		}
		ret = Bfile_OpenFile(levelFile, _OPENMODE_WRITE);
		if (ret < 0) {
			PopUpWin(1);
			locate(7, 4);
			Print((unsigned char*)"Error: 0");
			Bdisp_PutDisp_DD();
			Sleep(2000);
			return -1;
		}
		// File created, fill it with example.
		Bfile_WriteFile(ret, example, exampleSize);
		Bfile_CloseFile(ret);
		ret = Bfile_OpenFile(levelFile, _OPENMODE_READ);
		if (ret < 0) {
			return -1;
		}
	}

	loadedLevel = level;
	size = Bfile_GetFileSize(ret);
	// Search correct level in file
	while (level > 0) {
		pos += Bfile_ReadFile(ret, &buf, 1, pos);
		if (buf == -3) {
			level--;
		}
	}
	buf = 0;

	// Write level into buffer
	for (type = 0; type < 8; type++) {
		for (y = 0; y < 8; y++) {
			if (pos >= size) {
				pos = 0;
			}
			if ((type == 3) && (y > 0)) {
				break;
			}
			count = 0;
			buf = 0;
			oldpos = pos;
			for (i = 0; 1; i++) {
				if (type == 3) {
					break;
				}
				do {
					tmp = Bfile_ReadFile(ret, &buf, 1, pos);
				} while (tmp < 0);
				count += tmp;
				pos += tmp;
				if (buf == -1) {
					break;
				}
			}
			Bfile_SeekFile(ret, oldpos); // Rewind
			pos = oldpos;
			if (type == 3) {
				count = 2; // Level End Coordinates
			}
			if (curLevel[type][y] != 0) {
				free(curLevel[type][y]);
				curLevel[type][y] = 0;
			}

			curLevel[type][y] = (char*)malloc(count * sizeof(char));

			do {
				tmp = Bfile_ReadFile(ret, curLevel[type][y], count, pos);
			} while (tmp < 0);
			pos += tmp;
		}
	}
	Bfile_CloseFile(ret);
	return 0;
}

int existLevel(int level) {
	int ret, count = 0, left;
	char buf;
	ret = Bfile_OpenFile(levelFile, _OPENMODE_READ);
	if (ret < 0) {
		return 0;
	} else {
		do {
			left = Bfile_ReadFile(ret, &buf, 1, -1);
			if (buf == -4) {
				count++;
			}
		} while (left > 0);
		if (level <= count) {
			return 1;
		} else {
			return 0;
		}
	}
	Bfile_CloseFile(ret);
}

int freeMem() {
	int type, y;
	for (type = 0; type < 8; type++) {
		for (y = 0; y < 8; y++) {
			if (curLevel[type][y] != 0) {
				free(curLevel[type][y]);
				curLevel[type][y] = 0;
			}
		}
	}
}

int getSize(int level, int what, char y) {
	int i = 0;
	if ((what < 0) || (what > 7) || (y < 0) || (y > 7)) { 
		return 0;
	}
	if (what == 3) {
		return 2;
	}
	if (level != loadedLevel) {
		i = loadLevel(level);
		if (i == -1) {
			return 0;
		}
		i = 0;
	}
	while (curLevel[what][y][i] != -1) {
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
	if (level != loadedLevel) {
		i = loadLevel(level);
		if (i == -1) {
			return 0;
		}
		i = 0;
	}
	if ((x >= 0) && (y >= 0) && (y <= 7)) {
		size = getsizeBox(level, y);
		for (i = 0; i < size; i++) {
			if (curLevel[BOX][y][i] == x) {
				curLevel[BOX][y][i] = -2; // Setting deleted ones to -1 was bad, because -1 is the end marker...
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
	if (level != loadedLevel) {
		i = loadLevel(level);
		if (i == -1) {
			return 0;
		}
		i = 0;
	}
	if ((x >= 0) && (y >= 0) && (y <= 7)) {
		size = getsizeCoin(level, y);
		for (i = 0; i < size; i++) {
			if (curLevel[COIN][y][i] == x) { // Commenting this out was a stupid idea, because all coins then got removed. Also, this is only removing coins, not detecting them...
				curLevel[COIN][y][i] = -2;
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
	if (level != loadedLevel) {
		i = loadLevel(level);
		if (i == -1) {
			return -1;
		}
		i = 0;
	}
	// char temp2;
	size = getsizeEnemy(level, y, whichEnemy);
	// temp2 = ENEMYA + whichEnemy;
	whichEnemy += ENEMYA;
	for (i = 0; i < size; i++) {
		// WTF? I can't remember writing this... Max?
		// if ((levels[level][temp2][y][i] == x) && (x > 8)) {	
		if (curLevel[whichEnemy][y][i] == x) {
			curLevel[whichEnemy][y][i] = -2;
			return i;
		}
	}
	return -1;
}

int setEnemyRaw(int level, char x, char y, int whichEnemy, int pos) {
	if (level != loadedLevel) {
		if (loadLevel(level) == -1) {
			return -1;
		}
	}
	whichEnemy += ENEMYA;
	if (pos >= getsizeEnemy(level, y, whichEnemy)) {
		return -1;
	}
	curLevel[whichEnemy][y][pos] = x;
	return 0;
}

int isThere(int level, int what, char x, char y) {
	int i;
	int size;
	if (level != loadedLevel) {
		i = loadLevel(level);
		if (i == -1) {
			return 0;
		}
		i = 0;
	}
	if ((x >= 0) && (y >= 0) && (y <= 7)) {
		size = getSize(level, what, y);
		for (i = 0; i < size; i++) {
			if (curLevel[what][y][i] == x) {
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
