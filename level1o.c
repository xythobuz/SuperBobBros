/*
 * level 1
 * generated with xythobuz' BobLevelCreator
 */
#include "level1.h"

char lvl1_Block_0[3] = { 0, 20, 35 };
char lvl1_Block_1[3] = { 0, 20, 35 };
char lvl1_Block_2[3] = { 0, 20, 35 };
char lvl1_Block_3[3] = { 0, 20, 35 };
char lvl1_Block_4[3] = { 0, 20, 35 };
char lvl1_Block_5[4] = { 0, 11, 20, 35 };
char lvl1_Block_6[4] = { 0, 10, 11, 35 };
char lvl1_Block_7[36] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };

char lvl1_Box_0[1] = { -1 };
char lvl1_Box_1[1] = { -1 };
char lvl1_Box_2[1] = { -1 };
char lvl1_Box_3[1] = { -1 };
char lvl1_Box_4[1] = { -1 };
char lvl1_Box_5[4] = { 23, 24, 25, 28 };
char lvl1_Box_6[1] = { -1 };
char lvl1_Box_7[1] = { -1 };

char lvl1_Coin_0[1] = { -1 };
char lvl1_Coin_1[1] = { -1 };
char lvl1_Coin_2[1] = { -1 };
char lvl1_Coin_3[1] = { -1 };
char lvl1_Coin_4[3] = { 4, 5, 6 };
char lvl1_Coin_5[1] = { -1 };
char lvl1_Coin_6[1] = { 7 };
char lvl1_Coin_7[1] = { -1 };

char *lvl1_Block[8] = { lvl1_Block_0, lvl1_Block_1, lvl1_Block_2, lvl1_Block_3, lvl1_Block_4, lvl1_Block_5, lvl1_Block_6, lvl1_Block_7 };
char *lvl1_Box[8] = { lvl1_Box_0, lvl1_Box_1, lvl1_Box_2, lvl1_Box_3, lvl1_Box_4, lvl1_Box_5, lvl1_Box_6, lvl1_Box_7 };
char *lvl1_Coin[8] = { lvl1_Coin_0, lvl1_Coin_1, lvl1_Coin_2, lvl1_Coin_3, lvl1_Coin_4, lvl1_Coin_5, lvl1_Coin_6, lvl1_Coin_7 };

char **level1[3] = { lvl1_Block, lvl1_Box, lvl1_Coin };

int getsizeBlock1(char y) {
	int size = (sizeof(level1[0][y]) / sizeof(level1[0][y][0]));
	if ((size == 1) && (level1[0][y][0] == -1)) {
		return 0;
	} else {
		return size;
	}
}

int getsizeBox1(char y) {
	int size = (sizeof(level1[1][y]) / sizeof(level1[1][y][0]));
	if ((size == 1) && (level1[1][y][0] == -1)) {
		return 0;
	} else {
		return size;
	}
}

int getsizeCoin1(char y) {
	int size = (sizeof(level1[2][y]) / sizeof(level1[2][y][0]));
	if ((size == 1) && (level1[2][y][0] == -1)) {
		return 0;
	} else {
		return size;
	}
}

