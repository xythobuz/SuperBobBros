/*
 * level 1
 * generated with xythobuz' BobLevelCreator
 */
#include "levels.h"

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


int getsizeBlock1(char y) {
	switch(y) {
		case 0:
			return sizeof(lvl1_Block_0) / sizeof(lvl1_Block_0[0]);
		case 1:
			return sizeof(lvl1_Block_1) / sizeof(lvl1_Block_1[0]);
		case 2:
			return sizeof(lvl1_Block_2) / sizeof(lvl1_Block_2[0]);
		case 3:
			return sizeof(lvl1_Block_3) / sizeof(lvl1_Block_3[0]);
		case 4:
			return sizeof(lvl1_Block_4) / sizeof(lvl1_Block_4[0]);
		case 5:
			return sizeof(lvl1_Block_5) / sizeof(lvl1_Block_5[0]);
		case 6:
			return sizeof(lvl1_Block_6) / sizeof(lvl1_Block_6[0]);
		case 7:
			return sizeof(lvl1_Block_7) / sizeof(lvl1_Block_7[0]);

		default:
			return -1;
	}
}

int getsizeBox1(char y) {
	switch(y) {
		case 0:
			return sizeof(lvl1_Box_0) / sizeof(lvl1_Box_0[0]);
		case 1:
			return sizeof(lvl1_Box_1) / sizeof(lvl1_Box_1[0]);
		case 2:
			return sizeof(lvl1_Box_2) / sizeof(lvl1_Box_2[0]);
		case 3:
			return sizeof(lvl1_Box_3) / sizeof(lvl1_Box_3[0]);
		case 4:
			return sizeof(lvl1_Box_4) / sizeof(lvl1_Box_4[0]);
		case 5:
			return sizeof(lvl1_Box_5) / sizeof(lvl1_Box_5[0]);
		case 6:
			return sizeof(lvl1_Box_6) / sizeof(lvl1_Box_6[0]);
		case 7:
			return sizeof(lvl1_Box_7) / sizeof(lvl1_Box_7[0]);

		default:
			return -1;
	}
}

int getsizeCoin1(char y) {
	switch(y) {
		case 0:
			return sizeof(lvl1_Coin_0) / sizeof(lvl1_Coin_0[0]);
		case 1:
			return sizeof(lvl1_Coin_1) / sizeof(lvl1_Coin_1[0]);
		case 2:
			return sizeof(lvl1_Coin_2) / sizeof(lvl1_Coin_2[0]);
		case 3:
			return sizeof(lvl1_Coin_3) / sizeof(lvl1_Coin_3[0]);
		case 4:
			return sizeof(lvl1_Coin_4) / sizeof(lvl1_Coin_4[0]);
		case 5:
			return sizeof(lvl1_Coin_5) / sizeof(lvl1_Coin_5[0]);
		case 6:
			return sizeof(lvl1_Coin_6) / sizeof(lvl1_Coin_6[0]);
		case 7:
			return sizeof(lvl1_Coin_7) / sizeof(lvl1_Coin_7[0]);

		default:
			return -1;
	}
}

