/*
 * collisions.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */
#include "collisions.h"
#include "fxlib.h"
#include "levels.h"

/* Return Values:
 * -1 = Error
 *  0 = Nothing
 *  1 = Block
 *  2 = Box
 *  3 = Coin
 *  4 = Block at next Position
 *  5 = Box at next Position
 *  6 = Coin at next Position
 *
 *  Next Position:
 *     x+01234567	When checking (1|0) for Up
 *    y+|--------|--------|   |
 *     0|        |        |   |
 *     1|        |        |<--|
 *     2|        |        |
 *     3| (0|0)  |  (1|0) |
 *     4|        |        |
 *     5|        |        |
 *     6|        |        |
 *     7|        |        |
 *      |--------|--------|
 *     0|        |        |
 *     1|        |        |
 *     2|        |        |
 *     3|        |        |
 *     4| (0|1)  |  (1|1) |<---This is next pos when checking Right for (0|0) or checking down for (0|0)
 *     5|        |        |
 *     6|        |        |
 *     7|        |        |
 *      |--------|--------|
 *        /|\
 *         |---This is next pos when checking Left for (1|0)
 *
 * We only check the next position if we are not standing directly on a block...
 */

// (0|0) <= (x|y) < (128|64)
// Directions: 1 = Left; 2 = Right; 3 = Up; 4 = Down;

char colX; // New Plan: Instead of calculating where we should remove something in mechanics, we use the same
char colY; // values for x and y that found a something in the beginning. These coordinates get stored here.

char getPixel(int x, int y) {
	return (char)Bdisp_GetPoint_VRAM(x, y);
}

int translatepixelval(int x, int *off) {
	int counter = 0;
	while ((x % 8) != 0) {
		x--;
		counter++;
	}
	*off = counter;
	return (x / 8);
}

int checkColPlayerUp(int x, int y, int level, int offset) {
	int i;
	int count = 0;
	// First, we check the pixels directly above the player...
	for (i = 1; i < 7; i++) {
		if (getPixel((x + i), (y - 1))) {
			count++;
		}
	}
	if (count == 0) {
		return 0; // All pixels above the player are white. There is nothing!
	}

	if (count > 0) {
		y = translatepixelval(y, &count);
		x = translatepixelval((x + offset), &count);
		colY = y;
		colX = x;
		if (isBlock(level, x, y) != 0) {
			return 1;
		}
		if (count > 1) { // Player is 7px wide...
			// We are off...
			if (isBlock(level, (x + 1), y) != 0) {
				colX++;
				return 4;
			}
		}
		if (isBox(level, x, y) != 0) {
			return 2;
		}
		if (count > 1) {
			if (isBox(level, (x + 1), y) != 0) {
				colX++;
				return 5;
			}
		}
		if (isCoin(level, x, y) != 0) {
			return 3;
		}
		if (count > 1) {
			if (isCoin(level, (x + 1), y) != 0) {
				colX++;
				return 6;
			}
		}
	}
}

int checkColPlayerDown(int x, int y, int level, int offset) {
	int i;
	int count = 0;
	// First, we check the pixels directly below the player...
	for (i = 1; i < 7; i++) { // I don't know why, but if you start at 0, you can jump 1px into the wall.
								// Because Bob is only 7px wide...
		if (getPixel((x + i), (y + 8)) != 0) {
			count++;
		}
	}
	if (count == 0) {
		return 0; // All pixels below the player are white. There is nothing!
	}

	if (count > 0) {
		y = translatepixelval(y, &count) + 1; // Remember: Below!
		x = translatepixelval((x + offset), &count);
		colY = y;
		colX = x;
		if (isBlock(level, x, y) != 0) {
			return 1;
		}
		if (count > 1) { // Player is 7px wide...
			// We are off...
			if (isBlock(level, (x + 1), y) != 0) {
				colX++;
				return 4;
			}
		}
		if (isBox(level, x, y) != 0) {
			return 2;
		}
		if (count > 1) {
			if (isBox(level, (x + 1), y) != 0) {
				colX++;
				return 5;
			}
		}
		if (isCoin(level, x, y) != 0) {
			return 3;
		}
		if (count > 1) {
			if (isCoin(level, (x + 1), y) != 0) {
				colX++;
				return 6;
			}
		}
	}
}

int checkColPlayerRight(int x, int y, int level, int offset) {
	int i;
	int count = 0;
	for (i = 0; i < 8; i++) {
		if (getPixel((x + 7), (y + i)) != 0) {
			count++;
		}
	}
	if (count == 0) {
		return 0;
	}
	if (count > 0) {
		x = translatepixelval((x + offset), &count) + 1;
		y = translatepixelval(y, &count);
		colY = y;
		colX = x;
		if (isBlock(level, x, y) != 0) {
			return 1;
		}
		if (count > 0) {
			if (isBlock(level, x, (y + 1)) != 0) {
				colY++;
				return 4;
			}
		}
		if (isBox(level, x, y) != 0) {
			return 2;
		}
		if (count > 0) {
			if (isBox(level, x, (y + 1)) != 0) {
				colY++;
				return 5;
			}
		}
		if (isCoin(level, x, y) != 0) {
			return 3;
		}
		if (count > 0) {
			if (isBox(level, x, (y + 1)) != 0) {
				colY++;
				return 6;
			}
		}
	}
}

int checkColPlayerLeft(int x, int y, int level, int offset) {
	int i;
	int count = 0;
	for (i = 0; i < 8; i++) {
		if (getPixel((x - 1), (y + i)) != 0) {
			count++;
		}
	}
	if (count == 0) {
		return 0;
	}
	if (count > 0) {
		x = translatepixelval((x + offset), &count);
		y = translatepixelval(y, &count);
		colY = y;
		colX = x;
		if (isBlock(level, x, y) != 0) {
			return 1;
		}
		if (count > 0) {
			if (isBlock(level, x, (y + 1)) != 0) {
				colY++;
				return 4;
			}
		}
		if (isBox(level, x, y) != 0) {
			return 2;
		}
		if (count > 0) {
			if (isBox(level, x, (y + 1)) != 0) {
				colY++;
				return 5;
			}
		}
		if (isCoin(level, x, y) != 0) {
			return 3;
		}
		if (count > 0) {
			if (isBox(level, x, (y + 1)) != 0) {
				colY++;
				return 6;
			}
		}
	}
}
