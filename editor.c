/*
 * editor.c
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
#include "editor.h"
#include "levels.h"
#include "fxlib.h"
#include "filebios.h"
#include <stdlib.h>
#include "mechanics.h"

const FONTCHARACTER Path[18] = { '\\', '\\', 'f', 'l', 's', '0',
	'\\', 'b', 'o', 'b', '.', 'l', 'v', 'l', '\0' }; // "bob.lvl" in Storage

char* levelB;
char* tmplevel;
char** currentLev[8];
int size;

int levelEditor() {
	int fh, i, mode;

	fh = Bfile_OpenFile(Path, _OPENMODE_READ);
	if (fh < 0) {
		PopUpWin(2);
		locate(7, 3);
		Print((unsigned char*)"Error: 21");
		locate(3, 4);
		Print((unsigned char*)"Start game once");
		Bdisp_PutDisp_DD();
		Sleep(2000);
		return -1;
	}
	size = Bfile_GetFileSize(fh);
	Bdisp_AllClr_DDVRAM();
		
	levelB = (char*)malloc(size * sizeof(char));
	Bfile_ReadFile(fh, levelB, size, 0);
	Bfile_CloseFile(fh);
	
	drawMen();
	locate(1, 5);
	while(1) {
		if (IsKeyDown(KEY_CTRL_F1)) {
			mode = 1;
			break;
		}
		if (IsKeyDown(KEY_CTRL_F2)) {
			mode = 2;
			break;
		}
		if (IsKeyDown(KEY_CTRL_EXIT)) {
			mode = -1;
			break;
		}
	}
	if (mode == 1) {
		editLevel();
	}
	if (mode == 2) {
		addLevel();
	}

	free(levelB);
	return 0;
}

int editLevel() {
	int level;
	int offset;

	Print((unsigned char*)"Which Level to Edit?");
	Bdisp_PutDisp_DD();
	locate(1, 6);
	level = getNumber();
	Bdisp_AllClr_DDVRAM();
	locate(1, 1);
	Print((unsigned char*)"Press EXE to start!");
	locate(1, 2);
	Print((unsigned char*)"F1: Block");
	locate(1, 3);
	Print((unsigned char*)"F2: Box");
	locate(1, 4);
	Print((unsigned char*)"F3: Coin");
	locate(1, 5);
	Print((unsigned char*)"F4-F6: Enemy A-C");
	locate(1, 6);
	Print((unsigned char*)"tan: En. D; cos: Exit");
	locate(1, 7);
	Print((unsigned char*)"Cursor: Arrows");
	locate(1, 8);
	Print((unsigned char*)"DEL: Abort; AC: Save");
	Bdisp_PutDisp_DD();
	while(IsKeyUp(KEY_CTRL_EXE));
	load(level);

	drawEditScreen(0);
	Sleep(5000);

	unload();
}

int addLevel() {
	
}

int load(int level) {
	// Load level into currentLev
	int pos = 0, i, j, size;
	int* sizes[8];

	for (i = 0; i < 8; i++) {
		currentLev[i] = (char*)malloc(8 * sizeof(char*));
		sizes[i] = (int*)malloc(8 * sizeof(int));
	}

	while(level > 0) {
		while(levelB[pos++] != -4);
		level--;
	}

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			sizes[i][j] = 0;
			while(levelB[pos + sizes[i][j]] != -1) {
				sizes[i][j]++;
			}
			sizes[i][j]++;
			currentLev[i][j] = (char*)malloc(sizes[i][j] * sizeof(char));
			for (size = 0; size < sizes[i][j]; size++) {
				currentLev[i][j][size] = levelB[pos + size];
			}
			pos += sizes[i][j];
		}
	}

	for (i = 0; i < 8; i++) {
		free(sizes[i]);
	}
	return 0;
}

int unload() {
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			free(currentLev[i][j]);
		}
		free(currentLev[i]);
	}
}

int drawEditScreen(int offset) {
	int y, type, i, xPos, yPos, size;
	for (type = 0; type < 8; type++) {
		for (y = 0; y < 8; y++) {
			if (y == 3) {
				continue;
			}
			size = 0;
			while(currentLev[type][y][size] != -1) {
				size++;
			}
			size++;
			yPos = y * 8;
			for (i = 0; i < size; i++) {
				xPos = currentLev[type][y][size] * 8;
				xPos = xPos - offset;
				if ((xPos < -8) || (xPos > 128)) {
					continue;
				}
				switch (type) {
					case 0:
						drawBlock(xPos, yPos);
						break;
					case 1:
						drawBox(xPos, yPos);
						break;
					case 2:
						drawCoin(xPos, yPos);
						break;
					case 4: case 5: case 6: case 7:
						drawEnemy(xPos, yPos, (type - 4));
						break;
				}
			}
		}
	}
	
}

int drawMen() {
	int i;
	locate(1, 1);
	Print((unsigned char*)"F1: EDIT Level");
	locate(1, 2);
	Print((unsigned char*)"F2: ADD Level");
	locate(1, 3);
	i = 0;
	while (1) {
		if (existLevel(i) == 1) {
			i++;
		} else {
			break;
		}
	}
	numToString(i);
	Print(stri);
	Print((unsigned char*)" Levels!");
	Bdisp_PutDisp_DD();
	return 0;
}

int copyLevel(int add) {
	int i;
	tmplevel = (char*)malloc((size + add) * sizeof(char));
	for (i = 0; i < size; i++) {
		tmplevel[i] = levelB[i];
	}
	free(levelB);
	levelB = tmplevel;
	return 0;
}
