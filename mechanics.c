/*
 * mechanics.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */
#include "mechanics.h"
#include "Draw.h"
#include "levels.h"
#include "timer.h"
#include "button.h"

#define TIMEOUT 4

unsigned int timer1;

void timer_1() {
	timer1++;
}

int playLevel(int level, char playermodel) {
	int offset = 0; // In Pixel...
	int xPlayer = 16;
	int yPlayer = 40;
	char button = 0;
	char temp = 0;
	char direction = 0;
	char jump = 0;

	level--; // Arrays start at 0, Levelnumbers start at 1!

	SetTimer(ID_USER_TIMER1, TIMEOUT, *timer_1);

	drawLevel(level, offset, xPlayer, yPlayer, direction, playermodel);

	while(1) {
		temp = getButtons();
		if (temp != 0) {
			button = temp;
		}

		if (timer1 != 0) {
			// All 100ms...
			timer1 = 0;
			temp = movePlayer(button, &xPlayer, &yPlayer, &direction, offset, level, &jump);
			if (temp == 1) {
				break;
			}
			button = 0;
			
			// Scroll
			if (xPlayer > 118) {
				offset++;
				xPlayer--; // movePlayer() already moved it right, we move to its old pos...
			}
			if (xPlayer < 10) {
				xPlayer++;
				if (offset > 0) {
					offset--;
				}
			}
			
			gravityPlayer(&xPlayer, &yPlayer, offset, level, &jump);
			if (yPlayer > 58) {
				break;
			}
			if (levels[level][3][0][0] == ((xPlayer / 8) + (offset / 8))) {
				if (levels[level][3][0][1] == (yPlayer / 8)) {
					if ((level + 1) < HOWMANYLEVELS) {
						level++;
						offset = 0;
						xPlayer = 16;
						yPlayer = 40;
						jump = 0;
					} else {
						break;
					}
				}
			}
			drawLevel(level, offset, xPlayer, yPlayer, direction, playermodel);
		}
	}

	KillTimer(ID_USER_TIMER1);
	return 0;
}

int gravityPlayer(int *x, int *y, int offset, int level, char *jump) {
	int result;
	
	if (*jump > 0) {
		result = checkColPlayer(*x, *y, 3, level, offset);
		switch (result) {
			case 0:
				*y = (*y - 1);
				*jump = (*jump - 1);
				break;
			case 2:
				*jump = 0;
				removeBox(level, (*x / 8), ((*y / 8) - 1));
				break;
			case 1: case 4:
				*jump = 0;
				break;
			case 3:
				removeCoin(level, (*x / 8), ((*y / 8) - 1));
				*jump = 0;
				break;
			case 5:
				*jump = 0;
				removeBox(level, ((*x / 8) + 1), ((*y / 8) - 1));
				break;
			case 6:
				*jump = 0;
				removeBox(level, ((*x / 8) + 1), ((*y / 8) - 1));
				break;
		}
	} else {
		result = checkColPlayer(*x, *y, 4, level, offset);
		switch (result) {
			case 0:
				*y = *y + 1;
				break;
			case 3:
				*y = *y + 1;
				removeCoin(level, (*x / 8), ((*y / 8) + 1));
				break;
			case 6:
				*y = *y + 1;
				removeCoin(level, ((*x / 8) + 1), ((*y / 8) + 1));
				break;
		}
	}
	return 0;
}

int movePlayer(char button, int *x, int *y, int *direction, int offset, int level, char *jump) {
	int result;
	int xval = *x;
	switch (button) {
		case 0:
			*direction = 0;
			break;
		case 1:
			// Jump...
			result = checkColPlayer(*x, *y, 4, level, offset);
			if (  (result != 0) && (*jump == 0) ) {
				*jump = 18;
			}
			break;
		case 2: // Right
			*direction = 1;
			result = checkColPlayer(*x, *y, 2, level, offset);
			if (result == 0) {
				xval += 1;
			} else if (result == 3) {
				xval += 1;
				removeCoin(level, ((*x / 8) + 1), (*y / 8));
			} else if (result == 6) {
				xval += 1;
				removeCoin(level, ((*x / 8) + 1), ((*y / 8) + 1));
			}
			break;
		case 3: // Left
			*direction = 2;
			result = checkColPlayer(*x, *y, 1, level, offset);
			if (result == 0) {
				xval -= 1;
			} else if (result == 3) {
				xval -= 1;
				removeCoin(level, ((*x / 8) - 1), (*y / 8));
			} else if (result == 6) {
				xval -= 1;
				removeCoin(level, ((*x / 8) - 1), ((*y / 8) + 1));
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
			if ((tempx >= 0) && (tempx < 128)) {
				drawBlock(tempx, tempy);
			}
		}
		length = getsizeBox(level, y);
		for (i = 0; i < length; i++) {
			tempx = levels[level][1][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= 0) && (tempx < 128)) {
				drawBox(tempx, tempy);
			}
		}
		length = getsizeCoin(level, y);
		for (i = 0; i < length; i++) {
			tempx = levels[level][1][y][i];
			tempx *= 8;
			tempx -= offset;
			if ((tempx >= 0) && (tempx < 128)) {
				drawCoin(tempx, tempy);
			}
		}
	}
	drawPlayer(model, direction, xPlayer, yPlayer);
	draw();
}
