/*
 * mechanics.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */
#include "mechanics.h"
#include "fxlib.h"
#include "Draw.h"
#include "levels.h"
#include "timer.h"
#include "button.h"
#include "collisions.h"

#define TIMEOUT 4

unsigned int timer1;
int hp = 3;
int points = 0;
unsigned char stri[4];

void timer_1(void) {
	timer1++;
}

int playLevel(int level, char playermodel) {
	int offset = 0; // In pixels...
	int xPlayer = 16; 
	int yPlayer = 40;
	char button = 0; 
	char temp = 0;
	char direction = 0;
	char jump = 0;
	char backToMenu = 0;

	if (hp < 3) {
		hp = 3;
	}

	level--; // Arrays start at 0, Levelnumbers start at 1!

	SetTimer(ID_USER_TIMER1, TIMEOUT, *timer_1);

	drawLevel(level, offset, xPlayer, yPlayer, direction, playermodel);

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
			temp = movePlayer(button, &xPlayer, &yPlayer, &direction, offset, level, &jump);
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
			
			gravityPlayer(&xPlayer, &yPlayer, offset, level, &jump);
			if (yPlayer > 58) {
				if (hp > 0) {
					hp--;
					offset = 0;
					xPlayer = 16;
					yPlayer = 40;
					jump = 0;
				} else {
					backToMenu = 1;
				}
			}
			if (levels[level][3][0][0] == ((xPlayer / 8) + (offset / 8))) {
				if (levels[level][3][0][1] == (yPlayer / 8)) {
					if ((level + 1) < HOWMANYLEVELS) {
						level++;
						offset = 0;
						xPlayer = 16;
						yPlayer = 40;
						jump = 0;
						if (hp < 3) {
							hp = 3;
						}
					} else {
						backToMenu = 1;
					}
				}
			}
			drawLevel(level, offset, xPlayer, yPlayer, direction, playermodel);
			if (backToMenu != 0) {
				break;
			}
		}
	}

	KillTimer(ID_USER_TIMER1);
	return 0;
}

// Draw the Text (Hp, lvl, score)
int drawGUI(int level) {
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
int gravityPlayer(int *x, int *y, int offset, int level, char *jump) {
	int result;
	int rmCheck;
	
	if (*jump > 0) {
		result = checkColPlayerUp(*x, *y, level, offset);
		switch (result) {
			case 0:
				*y = (*y - 1);
				*jump = (*jump - 1);
				break;
			case 2: case 5:
				*jump = 0;
				rmCheck = removeBox(level, colX, colY);
				if(rmCheck != -1){
					hp++;
				}
				break;
			case 1: case 4:
				*jump = 0;
				break;
			case 3: case 6:
				rmCheck = removeCoin(level, colX, colY);
				if(rmCheck != -1){
					points++;
				}
				*jump = 0;
				break;
		}
	} else {
		result = checkColPlayerDown(*x, *y, level, offset);
		switch (result) {
			case 0:
				*y = *y + 1;
				break;
			case 3:
				*y = *y + 1;
				rmCheck = removeCoin(level, colX, colY);
				if(rmCheck != -1){
					points++;
				};
				break;
			case 6:
				*y = *y + 1;
				rmCheck = removeCoin(level, colX, colY);
				if(rmCheck != -1){
					points++;
				}
				break;
		}
	}
	return 0;
}

int movePlayer(char button, int *x, int *y, char *direction, int offset, int level, char *jump) {
	/*
	 * 0 = stehen
     * 1 = gehen rechts
     * 2 = gehen links
     * 3 = springen rechts
     * 4 = springen links
     * 5 = springen gerade
	 */
	int result;
	int xval = *x; //block-values
	switch (button) {
		case 0:
			if (*jump == 0) {
				*direction = 0; // down/gravity
			} else {
				*direction = 5; //jump straight up
			}
			break;
		case 1:
			// Jump...
			result = checkColPlayerDown(*x, *y, level, offset);
			if (  (result != 0) && (*jump == 0) ) {
				*jump = 18;
			}
			break;
		case 2: // Right
			if (*jump == 0) {
				*direction = 1; //walk right
			} else {
				*direction = 3; //jump right
			}
			result = checkColPlayerRight(*x, *y, level, offset);
			if (result == 0) {
				xval += 1;
			} else if ((result == 3) || (result == 6)) {
				xval += 1;
				removeCoin(level, colX, colY);
				points++;
			}
			break;
		case 3: // Left
			if (*jump == 0) {
				*direction = 2;
			} else {
				*direction = 4;
			}
			result = checkColPlayerLeft(*x, *y, level, offset);
			if (result == 0) {
				xval -= 1;
			} else if ((result == 3) || (result == 6)) {
				xval -= 1;
				removeCoin(level, colX, colY);
				points++;
			}
			break;
		case 4:
			// Down...
			break;
		case -1:
			return 1;
			break;
	}
	*x = xval;
	return 0;
}

int drawLevel(int level, int offset, int xPlayer, int yPlayer, char direction, char model) {
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
			tempx = levels[level][0][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= -7) && (tempx < 128)) {
				drawBlock(tempx, tempy);
			}
		}
		length = getsizeBox(level, y);
		for (i = 0; i < length; i++) {
			tempx = levels[level][1][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= -7) && (tempx < 128)) {
				drawBox(tempx, tempy);
			}
		}
		length = getsizeCoin(level, y);
		for (i = 0; i <= length; i++) {
			tempx = levels[level][2][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= -7) && (tempx < 128)) {
				drawCoin(tempx, tempy);
			}
		}
	}
	drawPlayer(model, direction, xPlayer, yPlayer);
	drawGUI(level);
	draw();
}
