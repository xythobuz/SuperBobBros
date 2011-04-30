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
	for (i = 0; i < size; i++) {
		Bfile_ReadFile(fh, &levelB[i], 1, i);
	}
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

	}

	free(levelB);
	return 0;
}

int editLevel() {
	int level;

	Print((unsigned char*)"Which Level to Edit?");
	Bdisp_PutDisp_DD();
	locate(1, 6);
	level = getNumber();
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
