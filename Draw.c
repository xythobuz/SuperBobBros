/*
 * Draw.c
 * by xythobuz
 * visit: www.xythobuz.org
 *
 * Defines some functions for drawing the world
 */
#include "fxlib.h"
#include "Draw.h"

#define WalkingStateA 1
#define WalkingStateB 2
#define MINX 0
#define MINY 0
#define MAXX 15
#define MAXY 7

int lastWalkingState = WalkingStateA;

void set(char x, char y) {
	if (x >= 0) {
		if (x <= 127) {
			if (y >= 0) {
				if (y <= 63) {
					Bdisp_SetPoint_VRAM(x, y, 1);
				}
			}
		}
	}
}

void unset(char x, char y) {
	if (x >= 0) {
		if (x <= 127) {
			if (y >= 0) {
				if (y <= 63) {
					Bdisp_SetPoint_VRAM(x, y, 0);
				}
			}
		}
	}
}

char translate(char x) {
	// Translates a Block Coordinate to a Pixle Coordinate!
	// Takes 0 <= x <= 16
	// Gives 0 <= x <= 127
	return (x * 8);
}

void DrawBlock(char x, char y) {
	if ((x >= MINX) && (y >= MINY)) {
		if ((x <= MAXX) && (y <= MAXY)) {
			char i;
			char j;
			x = translate(x);
			y = translate(y);
	
			// Fill 8x8px with black!
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					set(x + i, y + j);
				}
			}
			for (i = 0; i < 6; i++) {
				unset(x + 1 + i, y + 1);
				unset(x + 1 + i, y + 6);
				unset(x + 1, y + 1 + i);
				unset(x + 6, y + 1 + i);
			}
		}
	}
}

void DrawBox(char x, char y) {
	if ((x >= MINX) && (y >= MINY)) {
		if ((x <= MAXX) && (y <= MAXY)) {
			int i;
			int j;
			x = translate(x);
			y = translate(y);

			// Fill block, unset question mark:
			for (i = 0; i < 8; i++) {
				for (j = 0; j < 8; j++) {
					set(x + i, y + j);
				}
			}
			for (i = 0; i < 8; i++) {
				unset(x + i, y);
				unset(x, y + i);
				unset(x + i, y + 7);
				unset(x + 7, y + i);
			}

			unset(x + 3, y + 1);
			unset(x + 4, y + 1);
			unset(x + 2, y + 2);
			unset(x + 5, y + 2);
			unset(x + 5, y + 3);
			unset(x + 3, y + 4);
			unset(x + 4, y + 4);
			unset(x + 3, y + 6);
			unset(x + 4, y + 6);
			unset(x + 3, y + 7);
			unset(x + 4, y + 7);
		}
	}
}

void DrawCoin(char x, char y) {
	char i;
	if ((x >= MINX) && (y >= MINY)) {
		if ((x <= MAXX) && (y <= MAXY)) {
			x = translate(x);
			y = translate(y);
			for (i = 2; i < 6; i++) {
				set(x + i, y + 1);
				set(x + i, y + 6);
				set(x + 1, y + i);
				set(x + 6, y + i);
			}
			set(x + 3, y + 3);
			set(x + 3, y + 4);
			set(x + 4, y + 3);
			set(x + 4, y + 4);
		}
	}
}

void clear() {
	Bdisp_AllClr_VRAM();
}

void draw() {
	Bdisp_AllClr_DD();
	Bdisp_PutDisp_DD();
}

void DrawPlayer(char x, char y, char dir) {
	// Whatever direction the player is faceing, it's head is always at the same pos!
	char i;
	if ((x >= 0) && (y >= 0)) {
		if ((x <= 127) && (y <= 63)) {
			// head:
			for (i = 1; i < 4; i++) {
				set(x + 1, y + i);
				set(x + 5, y + i);
				set(x + 1 + i, y);
				set(x + 1 + i, y + 4);
			}
		
			// nose + hair + legs + face:
			if ((dir == 1) || (dir == 3)) {
				// Player facing right
				set(x + 6, y + 2);
				set(x + 2, y + 1);
				set(x + 2, y + 2);
				set(x + 3, y + 1);
				set(x + 3, y + 5);
				set(x + 3, y + 6);
				set(x + 2, y + 6);
				if (dir == 1) {
					set(x + 4, y + 7);
					set(x + 5, y + 7);
					// Walking right
					if (lastWalkingState == WalkingStateA) {
						set(x + 1, y + 6);
						set(x + 4, y + 6);
						lastWalkingState = WalkingStateB;
					} else {
						set(x + 2, y + 7);
						set(x + 3, y + 7);
						lastWalkingState = WalkingStateA;
					}
				} else {
					set(x + 1, y + 6);
					set(x + 4, y + 6);
					set(x + 5, y + 6);
				}
			}
			if ((dir == 2) || (dir == 4)) {
				// Player facing left
				set(x, y + 2);
				set(x + 3, y + 1);
				set(x + 4, y + 1);
				set(x + 4, y + 2);
				set(x + 3, y + 5);
				set(x + 3, y + 6);
				set(x + 4, y + 6);
				if (dir == 2) {
					// Player walking left
					set(x + 1, y + 7);
					set(x + 2, y + 7);
					if (lastWalkingState == WalkingStateA) {
						set(x + 2, y + 6);
						set(x + 5, y + 6);
						lastWalkingState = WalkingStateB;
					} else {
						set(x + 3, y + 7);
						set(x + 4, y + 7);
						lastWalkingState = WalkingStateA;
					}
				} else {
					// Player jumping left
					set(x + 1, y + 6);
					set(x + 2, y + 6);
					set(x + 5, y + 6);
				}
			}
			if ((dir == 0) || (dir == 5)) {
				// Player standing or jumping on its place
				set(x + 2, y + 1);
				set(x + 4, y + 1);
				set(x + 3, y + 2);
				if (dir == 0) {
					// Standing
					set(x + 2, y + 5);
					set(x + 2, y + 6);
					set(x + 2, y + 7);
					set(x + 4, y + 5);
					set(x + 4, y + 6);
					set(x + 4, y + 7);
					set(x + 1, y + 7);
					set(x, y + 7);
					set(x + 5, y + 7);
					set(x + 6, y + 7);
				} else {
					// Jumping
					set(x + 3, y + 5);
					set(x + 3, y + 6);
					set(x + 1, y + 6);
					set(x + 2, y + 6);
					set(x + 4, y + 6);
					set(x + 5, y + 6);
				}
			}
		}
	}
}
