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

int checkColPlayer(int x, int y, char direction, int level, int Pixeloffset) {
	// Player has 7x8px
	int check = 0;
	int i = 0;
	int lt = 0; //less than
	char which = 0;
	char is = 0;
	char counter = 0;
	int offset = 0;
	int atx = 0;
	int aty = 0;
	int isblocknext = -1;
	int iscoinnext = -1;
	int isboxnext = -1;
	int isblock = 0;
	int iscoin = 0;
	int isbox = 0;

	switch (direction) {
		case 1:
			// Left
			check = x - 1;
			i = y;
			lt = y + 8;
			which = 0;
			break;
		case 2:
			// Right
			check = x + 7;
			i = y;
			lt = y + 8;
			which = 0;
			break;
		case 3:
			// Up
			check = y - 1;
			i = x;
			lt = x + 7;
			which = 1;
			break;
		case 4:
			// Down
			check = y + 8;
			i = x;
			lt = x + 7;
			which = 1;
			break;
	}
	for (; i < lt; i++) {
		if (which == 1) {
			is = getPixel(i, check);
		} else {
			is = getPixel(check, i);
		}
		if (is != 0) {
			counter++;
		}
	}
	if (counter == 0) {
		// All pixels in the given direction are white:
		return 0;
	}

	if (which == 0) {
		x = translatepixelval(x, &offset);
		y = translatepixelval(y, &offset);
	} else {
		y = translatepixelval(y, &offset);
		x = translatepixelval(x, &offset);
	}
	if (offset > 1) { // Player is only 7px wide, block has 8px... We ignore this... <--Not anymore....
						// Well yea, i thought of that also and came to the conclusion that it's bad...
						// I don't remember why ;-)
		// Check next position also
		switch (direction) {
			case 1:
				// Left
				atx = (x - 1);
				aty = (y + 1);
				break;
			case 2:
				// Right
				aty = (y + 1);
				atx = (x + 1);
				break;
			case 3:
				// Up
				aty = (y - 1);
				atx = (x + 1);
				break;
			case 4:
				// Down
				aty = (y + 1);
				atx = (x + 1);
				break;
		}
		isblocknext = isBlock(level, (atx + (Pixeloffset / 8)), aty);
		isboxnext = isBox(level, (atx + (Pixeloffset / 8)), aty);
		iscoinnext = isCoin(level, (atx + (Pixeloffset / 8)), aty);
	}
	switch (direction) {
		case 1:
			atx = (x - 1);
			aty = y;
			break;
		case 2:
			atx = (x + 1);
			aty = y;
			break;
		case 3:
			atx = x;
			aty = (y - 1);
			break;
		case 4:
			atx = x;
			aty = (y + 1);
			break;
	}
	isblock = isBlock(level, (atx + (Pixeloffset / 8)), aty);
	isbox = isBox(level, (atx + (Pixeloffset / 8)), aty);
	iscoin = isCoin(level, (atx + (Pixeloffset / 8)), aty);

	// Priority: Block > Box > Coin > Nothing
	if (isblock != 0) {
		return 1;
	}
	if (isbox != 0) {
		return 2;
	}
	if (iscoin != 0) {
		return 3;
	}

	if (isblocknext != 0) {
		return 4;
	}
	if (isboxnext != 0) {
		return 5;
	}
	if (iscoinnext != 0) {
		return 6;
	}
	return -1; // Logical Error: Some pixels are black but we have not found something...
			// This was changed to 3. Who did it? Why?
}
