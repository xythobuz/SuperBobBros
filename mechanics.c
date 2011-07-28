/*
 * mechanics.c
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
#include "mechanics.h"
#include "fxlib.h"
#include "Draw.h"
#include "levels.h"
#include "timer.h"
#include "button.h"
#include "collisions.h"
#include "ai.h"

#define TIMEOUT 5

unsigned int timer1;
int hp = 3;
int points = 0;
unsigned char stri[4];
char backToMenu = 0;
int offset = 0;
int xPlayer = 16;
int yPlayer = 40;
char direction = 0;
char jump = 0;
int level;
char activateAI;
char playermodel;

void timer_1(void) {
	timer1++;
}

int playLevel(int levelLoc, char playermodelloc, char activateAIloc) {
	char button = 0; 
	char temp = 0;

	freeMem();
	loadedLevel = -1;

	backToMenu = 0;
	if (hp == 0) {
		hp = 3;
	}

	level = levelLoc;
	activateAI = activateAIloc;
	playermodel = playermodelloc;

	level--; // Arrays start at 0, Levelnumbers start at 1!

	SetTimer(ID_USER_TIMER1, TIMEOUT, *timer_1);

	drawLevel();

	while(1) {
		temp = getButtons();
		if (temp != 0) {
			button = temp;
			
			/*
			 * 1 = up
			 * 2 = right
			 * 3 = left
			 * 4 = down
			 */
		}

		if (timer1 != 0) {
			// All 100ms...
			timer1 = 0;
			temp = movePlayer(button);
			if (temp == 1) {
				backToMenu = 1;
			}
			button = 0;
			
			// Scroll
			if (xPlayer > 100) {
				offset++;
				xPlayer--; // movePlayer() already moved it right, we move to its old pos...
			}
			if (xPlayer < 9) {
				xPlayer++;
				if (offset > 0) {
					offset--;
				}
			}
			
			gravityPlayer(); // Schwerkraft
			if (yPlayer > 58) {
				die(); // Unten rausgefallen
			}

			if (curLevel[3][0][0] == ((xPlayer / 8) + (offset / 8))) { // Levelende erreicht?
				if (curLevel[3][0][1] == (yPlayer / 8)) {
					if (existLevel(level + 1)) {
						level++;
						offset = 0;
						xPlayer = 16;
						yPlayer = 40;
						jump = 0;
						hp++;
					} else {
						backToMenu = 1;
					}
				}
			}

			drawLevel(); // Zeichne Bildschirm

			if (backToMenu != 0) {
				xPlayer = 16;
				yPlayer = 40;
				jump = 0;
				offset = 0;
				break;
			}
		}
	}

	freeMem();
	KillTimer(ID_USER_TIMER1);
	return 0;
}

int die() {
	if (hp > 0) {
		xPlayer = 16;
		yPlayer = 40;
		jump = 0;
		offset = 0;
		hp--;
	} else {
		backToMenu = 1;
	}
}

// Draw the Text (Hp, lvl, score)
int drawGUI() {
	locate(0, 0);
	numToString(hp);
	Print((unsigned char*)"HP:");
	Print((unsigned char*)&stri);
	locate(7, 0);
	Print((unsigned char*)"LVL:");
	numToString(level + 1);
	Print((unsigned char*)&stri);
	locate(13, 0);
	Print((unsigned char*)"SCORE:");
	numToString(points);
	Print((unsigned char*)&stri);
	return 0;
}

// Give it a number. It stores it as a String in global var. 'stri'
int numToString(int number) {
	int counter = 0;
	if (number < 10) {
		stri[0] = number + '0';
		stri[1] = '\0';
		return 0;
	} else if (number < 100) {
		while ((number % 10) != 0) {
			number--;
			counter++;
		}
		number /= 10;
		stri[0] = number + '0';
		stri[1] = counter + '0';
		stri[2] = '\0';
		return 0;
	} else if (number < 1000) {
		while ((number % 10) != 0) {
			number--;
			counter++;
		}
		stri[2] = counter + '0';
		counter = 0;
		number /= 10;
		while ((number % 10) != 0) {
			number--;
			counter++;
		}
		stri[1] = counter + '0';
		stri[0] = (number / 10) + '0';
		stri[3] = '\0';
		return 0;
	} else {
		stri[0] = '?';
		stri[1] = '?';
		stri[2] = '?';
		stri[3] = '\0';
		return 1;
	}
}

// Pull player down & move it up while jumping
int gravityPlayer() {
	int result;
	int rmCheck;
	
	if (jump > 0) {
		result = checkColPlayerUp(xPlayer, yPlayer, level, offset);
		switch (result) {
			case 0:
				yPlayer = (yPlayer - 1);
				jump = (jump - 1);
				break;
			case 2: case 5:
				jump = 0;
				rmCheck = removeBox(level, colX, colY);
				if(rmCheck != -1){
					hp++;
				}
				break;
			case 1: case 4:
				jump = 0;
				break;
			case 3: case 6:
				rmCheck = removeCoin(level, colX, colY);
				if(rmCheck != -1){
					points++;
				}
				jump = 0;
				break;
			case 7: case 8:
				die();
				break;
		}
	} else {
		result = checkColPlayerDown(xPlayer, yPlayer, level, offset);
		switch (result) {
			case 0:
				yPlayer = yPlayer + 1;
				break;
			case 3: case 6:
				yPlayer = yPlayer + 1;
				rmCheck = removeCoin(level, colX, colY);
				if(rmCheck != -1){
					points++;
				};
				break;
			case 7: case 8:
				for (rmCheck = 0; rmCheck < HOWMANYENEMYS; rmCheck++) {
					if (isEnemy(level, colX, colY, rmCheck)) {
						removeEnemy(level, colX, colY, rmCheck);
					}
				}
		}
	}
	return 0;
}

int movePlayer(char button) {
	/*
	 * 0 = stehen
     * 1 = gehen rechts
     * 2 = gehen links
     * 3 = springen rechts
     * 4 = springen links
     * 5 = springen gerade
	 */
	int result;
	int xval = xPlayer; //block-values
	switch (button) {
		case 0:
			if (jump == 0) {
				direction = 0; // down/gravity
			} else {
				direction = 5; //jump straight up
			}
			break;
		case 1:
			// Jump...
			result = checkColPlayerDown(xPlayer, yPlayer, level, offset);
			if (  (result != 0) && (jump == 0) ) {
				jump = 18;
			}
			break;
		case 2: // Right
			if (jump == 0) {
				direction = 1; //walk right
			} else {
				direction = 3; //jump right
			}
			result = checkColPlayerRight(xPlayer, yPlayer, level, offset);
			if (result == 0) {
				xval += 1;
			} else if ((result == 3) || (result == 6)) {
				xval += 1;
				removeCoin(level, colX, colY);
				points++;
			} else if ((result == 7) || (result == 8)) {
				die();
			}
			break;
		case 3: // Left
			if (jump == 0) {
				direction = 2;
			} else {
				direction = 4;
			}
			result = checkColPlayerLeft(xPlayer, yPlayer, level, offset);
			if (result == 0) {
				xval -= 1;
			} else if ((result == 3) || (result == 6)) {
				xval -= 1;
				removeCoin(level, colX, colY);
				points++;
			} else if ((result == 7) || (result == 8)) {
				die();
			}
			break;
		case 4:
			// Down...
			break;
		case -1:
			return 1;
			break;
	}
	xPlayer = xval;
	return 0;
}

int drawLevel() {
	int length;
	int y;
	int i;
	int tempx;
	int tempy;

	clear();
	for (y = 0; y < 8; y++) {
		length = getsizeBlocks(level, y);
		tempy = y * 8;
		for (i = 0; i < length; i++) {
			tempx = curLevel[0][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= -7) && (tempx < 128)) {
				drawBlock(tempx, tempy);
			}
		}
		length = getsizeBox(level, y);
		for (i = 0; i < length; i++) {
			tempx = curLevel[1][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= -7) && (tempx < 128)) {
				drawBox(tempx, tempy);
			}
		}
		length = getsizeCoin(level, y);
		for (i = 0; i <= length; i++) {
			tempx = curLevel[2][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= -7) && (tempx < 128)) {
				drawCoin(tempx, tempy);
			}
		}
	}
	drawPlayer(playermodel, direction, xPlayer, yPlayer);
	if (activateAI == 1) {
		drawAI(level, offset);
	}
	drawGUI(level);
	draw();
}
