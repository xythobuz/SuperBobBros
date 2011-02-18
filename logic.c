/*
 * logic.c
 * by xythobuz
 */
#include "fxlib.h"
#include "Draw.h"
#include "levels.h"
#include "timer.h"
#include "button.h"

#define T1_TIMEOUT 4 // Alle 100ms
#define BELOW 0
#define ABOVE 1
#define RIGHT 2
#define LEFT 3
#define JUMPHEIGHT 18

int hp = 5;
int score = 0;
char xPlayer = 16;
char yPlayer = 40;
char dirPlayer = 0;
unsigned int viewOffset = 0;

unsigned char HUDstring[4];

int isJumping = 0;

unsigned int timer1 = 0;
unsigned int timer1Flag = 0;

char getBlock1(char x, char y) {
	switch(y) {
		case 0:
			return lvl1_Block_0[x];
		case 1:
			return lvl1_Block_1[x];
		case 2:
			return lvl1_Block_2[x];
		case 3:
			return lvl1_Block_3[x];
		case 4:
			return lvl1_Block_4[x];
		case 5:
			return lvl1_Block_5[x];
		case 6:
			return lvl1_Block_6[x];
		case 7:
			return lvl1_Block_7[x];

		default:
			return -1;
	}
}

char getBox1(char x, char y) {
	switch(y) {
		case 0:
			return lvl1_Box_0[x];
		case 1:
			return lvl1_Box_1[x];
		case 2:
			return lvl1_Box_2[x];
		case 3:
			return lvl1_Box_3[x];
		case 4:
			return lvl1_Box_4[x];
		case 5:
			return lvl1_Box_5[x];
		case 6:
			return lvl1_Box_6[x];
		case 7:
			return lvl1_Box_7[x];

		default:
			return -1;
	}
}

char getCoin1(char x, char y) {
	switch(y) {
		case 0:
			return lvl1_Coin_0[x];
		case 1:
			return lvl1_Coin_1[x];
		case 2:
			return lvl1_Coin_2[x];
		case 3:
			return lvl1_Coin_3[x];
		case 4:
			return lvl1_Coin_4[x];
		case 5:
			return lvl1_Coin_5[x];
		case 6:
			return lvl1_Coin_6[x];
		case 7:
			return lvl1_Coin_7[x];

		default:
			return -1;
	}
}

void setCoin1(char x, char y, char val) {
	switch(y) {
		case 0:
			lvl1_Coin_0[x] = val;
			break;
		case 1:
			lvl1_Coin_1[x] = val;
			break;
		case 2:
			lvl1_Coin_2[x] = val;
			break;
		case 3:
			lvl1_Coin_3[x] = val;
			break;
		case 4:
			lvl1_Coin_4[x] = val;
			break;
		case 5:
			lvl1_Coin_5[x] = val;
			break;
		case 6:
			lvl1_Coin_6[x] = val;
			break;
		case 7:
			lvl1_Coin_7[x] = val;
			break;

		default:
			break;
	}
}

void setBox1(char x, char y, char val) {
	switch(y) {
		case 0:
			lvl1_Box_0[x] = val;
			break;
		case 1:
			lvl1_Box_1[x] = val;
			break;
		case 2:
			lvl1_Box_2[x] = val;
			break;
		case 3:
			lvl1_Box_3[x] = val;
			break;
		case 4:
			lvl1_Box_4[x] = val;
			break;
		case 5:
			lvl1_Box_5[x] = val;
			break;
		case 6:
			lvl1_Box_6[x] = val;
			break;
		case 7:
			lvl1_Box_7[x] = val;
			break;

		default:
			break;
	}
}

void DrawLevel1() {
	// Draw all the elements, according to view-offset
	int length;
	int i;
	int res;
	int a;
	for (a = 0; a < 8; a++) {
		length = getsizeBlock1(a);
		for (i = 0; i < length; i++) {
			res = getBlock1(i, a) - viewOffset;
			if ((res >= 0) && (res < 16)) {
				DrawBlock(res, a);
			}
		}

		length = getsizeBox1(a);
		for (i = 0; i < length; i++) {
			res = getBox1(i, a) - viewOffset;
			if ((res >= 0) && (res < 16)) {
				DrawBox(res, a);
			}
		}

		length = getsizeCoin1(a);
		for (i = 0; i < length; i++) {
			res = getCoin1(i, a) - viewOffset;
			if ((res >= 0) && (res < 16)) {
				DrawCoin(res, a);
			}
		}
	}
	DrawPlayer(xPlayer, yPlayer, dirPlayer);
}

void timer_1() {
	timer1++;
	timer1Flag++;
}

int PlayLevel1() {
	char buttons;
	int res;
	int off;

	SetTimer(ID_USER_TIMER1, T1_TIMEOUT, *timer_1);
	while (1) {
		if (hp < 0) {
			break;
		}
		if (timer1 >= 10) {
			timer1 = 0;
			// Gets executed every second...
			
		}
		
		if (timer1Flag != 0) {
			timer1Flag = 0;
			
			buttons = getButtons();
			switch (buttons) {
				case -1:
					return 0;
					break;
				case RIGHT:
					// Right
					dirPlayer = 1;
					res = colPlayerHori1(RIGHT);
					switch(res) {
						case 0:
							// Nothing
							move(RIGHT);
							break;
						case 1:
							// Box or Block
							break;
						case 2:
							// Coin
							score++;
							removeCoin1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer, &off));
							move(RIGHT);
							break;
						case 3:
							// Coin at the next pos.
							score++;
							removeCoin1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer + 8, &off));
							move(RIGHT);
							break;
						case 4:
							score += 2;
							removeCoin1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer, &off));
							removeCoin1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer + 8, &off));
							move(RIGHT);
							break;
					}
					break;
				case LEFT:
					// Left
					dirPlayer = 2;
					res = colPlayerHori1(LEFT);
					switch(res) {
						case 0:
							move(LEFT);
							break;
						case 1:
							// Box or Block
							break;
						case 2:
							// Coin
							score++;
							removeCoin1(translateBack(xPlayer, &off), translateBack(yPlayer, &off));
							move(LEFT);
							break;
						case 3:
							// Coin at the next pos.
							score++;
							removeCoin1(translateBack(xPlayer, &off), translateBack(yPlayer + 8, &off));
							move(LEFT);
							break;
						case 4:
							score += 2;
							removeCoin1(translateBack(xPlayer, &off), translateBack(yPlayer, &off));
							removeCoin1(translateBack(xPlayer, &off), translateBack(yPlayer + 8, &off));
							move(LEFT);
							break;
					}
					break;
				case 4:
					// Down
					break;
				case 0:
					// Nothing
					dirPlayer = 0;
					break;
				case 1:
					// Jump only if we have something solid under us...
					if (isJumping == 0) {
						if (colPlayerVert1(BELOW) == 1) {
							isJumping = JUMPHEIGHT;
						}
					}
					break;

				default:
					break;
			}
			gravity1();
			clear();
			DrawLevel1();
			drawHUD();
			draw();
		}
	}
}

int move(int dir) {
	if (dir == LEFT) {
		if (xPlayer > 8) {
			xPlayer--;
		} else {
			if (viewOffset > 0) {
				viewOffset--;
				xPlayer += 8;
			}
		}
	} else {
		if (xPlayer < 120) {
			xPlayer++;
		} else {
			viewOffset++;
			xPlayer -= 8;
		}
	}
}

int drawHUD() {
	locate(1, 1);
	intToString(hp);
	Print((unsigned char*)"HP:");
	Print(HUDstring);
	locate(13, 1);
	Print((unsigned char*)"SCORE:");
	intToString(score);
	Print(HUDstring);
}

int intToString(int a) {
	int i;
	for (i = 0; i < 3; i++) {
		HUDstring[i] = '0';
	}
	HUDstring[3] = '\0';
	if (a < 10) {
		HUDstring[2] += a;
		return 0;
	}
	if (a > 999) {
		HUDstring[0] = 'B';
		HUDstring[1] = 'I';
		HUDstring[2] = 'G';
		return 0;
	}
	while (a >= 100) {
		HUDstring[0]++;
		a -= 100;
	}
	while (a >= 10) {
		HUDstring[1]++;
		a -= 10;
	}
	while (a >= 1) {
		HUDstring[2]++;
		a -= 1;
	}
	return 1;
}

char getPixel(int x, int y) {
	return (char)Bdisp_GetPoint_VRAM(x, y);
}

int isBlock1(char x, char y) {
	// is there a Block at (x|y)?
	int flag = 0;
	int i;
	for (i = 0; i < getsizeBlock1(y); i++) {
		if (getBlock1(i, y) == x + viewOffset) {
			flag++;
		}
	}
	return flag;
}

int isBox1(char x, char y) {
	// is there a Box at (x|y)?
	int flag = 0;
	int i;
	for (i = 0; i < getsizeBox1(y); i++) {
		if (getBox1(i, y) == x + viewOffset) {
			flag++;
		}
	}
	return flag;
}

int isCoin1(char x, char y) {
	// is there a Block at (x|y)?
	int flag = 0;
	int i;
	for (i = 0; i < getsizeCoin1(y); i++) {
		if (getCoin1(i, y) == x + viewOffset) {
			flag++;
		}
	}
	return flag;
}

int removeCoin1(char x, char y) {
	int i;
	for (i = 0; i < getsizeCoin1(y); i++) {
		if (getCoin1(i, y) == x + viewOffset) {
			setCoin1(i, y, -1);
		}
	}
}

int removeBox1(char x, char y) {
	int i;
	for (i = 0; i < getsizeBox1(y); i++) {
		if (getBox1(i, y) == x + viewOffset) {
			setBox1(i, y, -1);
		}
	}
}

int colPlayerHori1(char dir) {
	// Check what is (dir) the player:
	// 0 = Nothing
	// 1 = Box / Block
	// 2 = Coin
	// 3 = Coin at next pos.
	// 4 = Coin at both
	// dir:
	// use definitions RIGHT and LEFT
	int i;
	int flag = 0;
	char x = xPlayer;
	char y = yPlayer;
	char off;
	int tmp;
	char ret1 = 0;
	char ret2 = 0;

	switch(dir) {
		case RIGHT:
			tmp = (xPlayer + 7);
			break;
		case LEFT:
			tmp = (xPlayer - 1);
			break;
	}
	for (i = yPlayer; i < (yPlayer + 8); i++) {
		if (getPixel(tmp, i) == 1) {
			flag++;
		}
	}
	if (flag == 0) {
		// All the pixels right/left the player are white. There is nothing...
		return 0;
	} else {
		// There are pixels activated... We check what it is...
		// First translate the pixelvalues to our block-values (127|63) => (15|7)
		x = translateBack(x, &off);
		y = translateBack(y, &off);
		
		switch (dir) {
			case RIGHT:
				tmp = (x + 1);
				break;
			case LEFT:
				tmp = x - 1;
				break;
		}

		if (off > 0) {
			// We are not on ONE block. Check the next also...
			if (isBlock1(tmp, y + 1) != 0) {
				ret2 = 1;
			}
			if (dir == LEFT) {
				tmp = x;
			}
			if (isBox1(tmp, y + 1) != 0) {
				ret2 = 1;
			}
			if (isCoin1(tmp, y + 1) != 0) {
				ret2 = 3;
			}
		}
		if (dir == LEFT) {
			tmp = x - 1;
		}
		if (isBlock1(tmp, y) != 0) {
			// There is a Block...
			ret1 = 1;
		}
		if (dir == LEFT) {
			tmp = x;
		}
		if (isBox1(tmp, y) != 0) {
			// There is a Box...
			ret1 = 1;
		}
		if (isCoin1(tmp, y) != 0) {
			// Theres a Coin...
			ret1 = 2;
		}
		if ((ret1 == 1) || (ret2 == 1)) {
			return 1;
		} else if ((ret1 == 0) && (ret2 == 0)) {
			return 0;
		} else if ((ret1 == 2) && (ret2 == 3)) {
			return 4;
		} else if (ret1 == 0) {
			return ret2;
		} else {
			return ret1;
		}
	}
}

int colPlayerVert1(char dir) {
	// Check what is (dir) the player:
	// 0 = Nothing
	// 1 = Block (+ Box if dir = BELOW)
	// 2 = Coin
	// 3 = Coin at next
	// 4 = Box (if dir = ABOVE)
	// 5 = Box at next position (if dir = ABOVE)
	// 6 = two coins
	// 7 = two boxes
	// dir:
	// use definitions BELOW and ABOVE
	int i;
	int flag = 0;
	char x = xPlayer;
	char y = yPlayer;
	char off;
	int tmp;
	char ret1 = 0;
	char ret2 = 0;

	switch(dir) {
		case BELOW:
			tmp = (yPlayer + 8);
			break;
		case ABOVE:
			tmp = (yPlayer - 1);
			break;
	}
	for (i = xPlayer; i < (xPlayer + 7); i++) {
		if (getPixel(i, tmp) == 1) {
			flag++;
		}
	}
	if (flag == 0) {
		// All the pixels under/above the player are white. There is nothing...
		return 0;
	} else {
		// There are pixels activated under the player... We check what it is...
		// First translate the pixelvalues to our block-values (127|63) => (15|7)
		y = translateBack(y, &off);
		x = translateBack(x, &off);
		
		switch (dir) {
			case BELOW:
				tmp = y + 1;
				break;
			case ABOVE:
				tmp = y - 1;
				break;
		}

		if (off > 1) { // Player is only 7px wide, but block has 8px, so we only
					   // check the next block if we are at least 2 px off...

			// We are not on ONE block. Check the next also...
			if (isBlock1(x + 1, tmp) != 0) {
				ret1 = 1;
			}
			if (dir == ABOVE) {
				tmp = y;
			}
			if (isBox1(x + 1, tmp) != 0) {
				if (dir == ABOVE) {
					ret1 = 5;
				} else {
					ret1 = 1;
				}
			}
			if (isCoin1(x + 1, tmp) != 0) {
				ret1 = 3;
			}
		}
		if (dir == ABOVE) {
			tmp = y - 1;
		}
		if (isBlock1(x, tmp) != 0) {
			// There is a Block...
			ret2 = 1;
		}
		if (dir == ABOVE) {
			tmp = y;
		}
		if (isBox1(x, tmp) != 0) {
			// There is a Box...
			if (dir == ABOVE) {
				ret2 = 4;
			} else {
				ret2 = 1;
			}
		}
		if (isCoin1(x, tmp) != 0) {
			// Theres a Coin...
			ret2 = 2;
		}
		if ((ret1 == 0) && (ret2 == 0)) {
			return 0;
		}
		if ((ret1 == 1) || (ret2 == 1)) {
			return 1;
		}
		if ((ret1 == 2) && (ret2 == 3)) {
			return 6;
		}
		if (((ret1 == 2) || (ret2 == 3)) && ((ret1 == 0) || (ret2 == 0))) {
			if (ret1 == 0) {
				return 3;
			} else {
				return 2;
			}
		}
		if (dir == ABOVE) {
			if ((ret1 == 4) && (ret2 == 5)) {
				return 7;
			}
			if (((ret1 == 4) || (ret2 == 5)) && ((ret1 == 0) || (ret2 == 0))) {
				if (ret1 == 0) {
					return 5;
				} else {
					return 4;
				}
			}
		}
	}
}

int translateBack(char x, char *off) {
	*off = x;
	while((x % 8) != 0) {
		x--;
	}
	*off -= x;
	x /= 8;
	return x;
}

int gravity1() {
	// Calculate if Player should fall.
	// First check if there are any pixels under the player
	// If this is not the case, we reduce the yPlayer value...
	// Also check if we are out of the bounds of the screen. Then we die...
	// This is also handling the players jump...
	int res;
	char off; // We ignore the offset. The player will get it anyway...
	
	// Fell out of the screen...:
	if (yPlayer >= 56) {
		killed();
		return 0;
	}

	if (isJumping > 0) {
		// We are jumping up...
		res = colPlayerVert1(ABOVE);
		switch(res) {
			case 0:
				// Nothing
				isJumping--;
				yPlayer--;
				break;
			case 1:
				// Block
				isJumping = 0;
				break;
			case 2:
				// Coin
				score++;
				removeCoin1(translateBack(xPlayer, &off), translateBack(yPlayer, &off));
				isJumping--;
				yPlayer--;
				break;
			case 3:
				// Coin at the next pos.
				score++;
				removeCoin1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer, &off));
				isJumping--;
				yPlayer--;
				break;
			case 4:
				// Box
				hp++;
				removeBox1(translateBack(xPlayer, &off), translateBack(yPlayer, &off));
				isJumping = 0;
				break;
			case 5:
				// Box at next positon
				hp++;
				removeBox1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer, &off));
				isJumping = 0;
				break;
			case 6:
				// Two coins
				score += 2;
				removeCoin1(translateBack(xPlayer, &off), translateBack(yPlayer, &off));
				removeCoin1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer, &off));
				isJumping--;
				yPlayer--;
				break;
			case 7:
				hp += 2;
				removeBox1(translateBack(xPlayer, &off), translateBack(yPlayer, &off));
				removeBox1(translateBack(xPlayer, &off) + 1, translateBack(yPlayer, &off));
				isJumping = 0;
				break;
		}
	} else {
		// We are not jumping. Just fall correct
		res = colPlayerVert1(BELOW);
		switch (res) {
			case 0:
				yPlayer++;
				break;
			case 1:
				// Block / Box, do nothing
				break;
			case 2:
				yPlayer++;
				score++;
				removeCoin1(translateBack(xPlayer, &off), (translateBack(yPlayer, &off) + 1));
				break;
			case 3:
				yPlayer++;
				score++;
				removeCoin1(translateBack(xPlayer, &off) + 1, (translateBack(yPlayer, &off) + 1));
				break;
			case 6:
				yPlayer++;
				score += 2;
				removeCoin1(translateBack(xPlayer, &off), (translateBack(yPlayer, &off) + 1));
				removeCoin1(translateBack(xPlayer, &off) + 1, (translateBack(yPlayer, &off) + 1));
		}
	}
}

int killed() {
	hp--;
	dirPlayer = 0;
	xPlayer = 16;
	yPlayer = 40;
	viewOffset = 0;
	locate(3, 5);
	Print((unsigned char*)"Killed");
	draw();
	Sleep(1000);
}
