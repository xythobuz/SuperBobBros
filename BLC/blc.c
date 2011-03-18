/*
 * Bob Level Creator
 * by xythobuz
 *
 * This program takes a draft for a Level and converts it to a .c File.
 * Refer to the Readme for more informations on the level-draft.
 */

#include <stdio.h>
#define MAXRAWLENGTH 1100
#define MAX 127

// Uncomment for Debug Output:
/*
#define DEBUG
*/

int rawLevelData[MAX];
int block0[MAX];
int block1[MAX];
int block2[MAX];
int block3[MAX];
int block4[MAX];
int block5[MAX];
int block6[MAX];
int block7[MAX];
int box0[MAX];
int box1[MAX];
int box2[MAX];
int box3[MAX];
int box4[MAX];
int box5[MAX];
int box6[MAX];
int box7[MAX];
int coin0[MAX];
int coin1[MAX];
int coin2[MAX];
int coin3[MAX];
int coin4[MAX];
int coin5[MAX];
int coin6[MAX];
int coin7[MAX];
int enemyA0[MAX];
int enemyA1[MAX];
int enemyA2[MAX];
int enemyA3[MAX];
int enemyA4[MAX];
int enemyA5[MAX];
int enemyA6[MAX];
int enemyA7[MAX];
int enemyB0[MAX];
int enemyB1[MAX];
int enemyB2[MAX];
int enemyB3[MAX];
int enemyB4[MAX];
int enemyB5[MAX];
int enemyB6[MAX];
int enemyB7[MAX];
int enemyC0[MAX];
int enemyC1[MAX];
int enemyC2[MAX];
int enemyC3[MAX];
int enemyC4[MAX];
int enemyC5[MAX];
int enemyC6[MAX];
int enemyC7[MAX];
int enemyD0[MAX];
int enemyD1[MAX];
int enemyD2[MAX];
int enemyD3[MAX];
int enemyD4[MAX];
int enemyD5[MAX];
int enemyD6[MAX];
int enemyD7[MAX];
int *blocks[8] = {block0, block1, block2, block3, block4, block5, block6, block7};
int *boxes[8] = {box0, box1, box2, box3, box4, box5, box6, box7};
int *coins[8] = {coin0, coin1, coin2, coin3, coin4, coin5, coin6, coin7};
int *enemyA[8] = {enemyA0, enemyA1, enemyA2, enemyA3, enemyA4, enemyA5, enemyA6, enemyA7};
int *enemyB[8] = {enemyB0, enemyB1, enemyB2, enemyB3, enemyB4, enemyB5, enemyB6, enemyB7};
int *enemyC[8] = {enemyC0, enemyC1, enemyC2, enemyC3, enemyC4, enemyC5, enemyC6, enemyC7};
int *enemyD[8] = {enemyD0, enemyD1, enemyD2, enemyD3, enemyD4, enemyD5, enemyD6, enemyD7};
int **all[7] = {blocks, boxes, coins, enemyA, enemyB, enemyC, enemyD};

char OutputHeader[] = "/*\n * generated with xythobuz' BobLevelCreator\n */\n";

int readLevelFile(char *name);
int checkHeader();
void clearMemory();
void removeStuff(int length);
int findRow(int row);
int findEnd(int row);
int countCharRaw(int row, char character);
int formatData(int character);
int countChar(int row, char character);
int writeC(int levelnum, int xEnd, int yEnd);
int writeH(int levelnum);

void clearMemory() {
	int i, j, k;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 8; j++) {
			for (k = 0; k < MAX; k++) {
				all[i][j][k] = -1;
			}
		}
	}
}

int main(int argc, char **argv) {
	int length;
	int levelnum;
	int xEnd;
	int yEnd;
	int i;
	int j;
	
	clearMemory();

	if (argc != 2) {
		printf("Aufruf:\n%s level.txt\n", argv[0]);
		return 1;
	}
	length = readLevelFile(argv[1]);
#ifdef DEBUG
	printf("[D]Length: %i\n", length);
#endif
	if (length == -1) {
		printf("Level File could not be opened!\n");
		return 1;
	}
	if (length == -2) {
		printf("Level File too large...!\n");
		return 1;
	}
	if (checkHeader() != 0) {
		printf("Header wrong!\n");
		return 1;
	}
	removeStuff(length);
	printf("Enter Levelnumber: ");
	scanf("%i", &levelnum);
	printf("Enter levels Exit as x and y (0 <= y <  8)\nx: ");
	scanf("%i", &xEnd);
	printf("y: ");
	scanf("%i", &yEnd);

	if ((xEnd < 0) || (yEnd < 0) || (yEnd > 7)) {
		printf("Levels Exit out of range!\n");
		return 1;
	}
	
	if (formatData('x') == -1) {
		printf("Error while formating Block data!\n");
		return 1;
	}
	if (formatData('b') == -1) {
		printf("Error while formating Box data!\n");
		return 1;
	}
	if (formatData('c') == -1) {
		printf("Error while formating Coin data!\n");
		return 1;
	}
	if (formatData('1') == -1) {
		printf("Error while formating EnemyA data!\n");
		return 1;
	}
	if (formatData('2') == -1) {
		printf("Error while formating EnemyB data!\n");
		return 1;
	}
	if (formatData('3') == -1) {
		printf("Error while formating EnemyC data!\n");
		return 1;
	}
	if (formatData('4') == -1) {
		printf("Error while formating EnemyD data!\n");
		return 1;
	}

	if (writeC(levelnum, xEnd, yEnd) == -1) {
		printf("Error while writing c file!\n");
		return 1;
	}
	if (writeH(levelnum) == -1) {
		printf("Error while writing h file!\n");
		return 1;
	}

	return 0;
}

int readLevelFile(char *name) {
	// Read levelfile, put contents into rawLevelData[]
	int counter = 0;
	int temp;
	FILE *fp;
	
	if ((fp = fopen(name, "r")) == NULL) {
		return -1;
	}
	do {
		temp = fgetc(fp);
		rawLevelData[counter] = temp;
		counter++;
	} while (temp != EOF);
	
	fclose(fp);

	if (counter > MAXRAWLENGTH) {
		return -2;
	}

	return counter;
}

int checkHeader() {
	// Check if levelfile starts with the String "level"...
	char temp[] = "level";
	int i;
	int flag = 0;
	for (i = 0; i < 5; i++) {
		if (temp[i] != rawLevelData[i]) {
			flag++;
		}
	}
	if (flag != 0) {
		return 1;
	}
	return 0;
}

void removeStuff(int length) {
	// Remove all \n and \r from rawLevelData[], also remove "Header"
	int i;
	for (i = 0; i < length; i++) {
		if (rawLevelData[i] == '\n') {
			rawLevelData[i] = -1;
		}
		if (rawLevelData[i] == '\r') {
			rawLevelData[i] = -1;
		}
	}
	for (i = 0; i < 5; i++) {
		rawLevelData[i] = -1;
	}
}

int findRow(int row) {
	// Returns start of a row in rawLevelData[]. Searches for rownumber and | after it...
	int i;
	for (i = 0; i < MAXRAWLENGTH - 2; i++) {
		if ( (rawLevelData[i] == ((char)row + '0')) && (rawLevelData[i + 1] == '|') ) {
			return (i + 2);
		}
	}
	return -1;
}

int findEnd(int row) {
	// Returns position of last filled byte of a row...
	int i;
	int j = findRow(row);
	if (j == -1) {
		return -1;
	}
	for (i = j; i < MAXRAWLENGTH; i++) {
		if (rawLevelData[i] == -1) {
			return (i - 1);
		}
	}
	return -1;
}

int countCharRaw(int row, char character) {
	// Looks how many 'character's are found in a 'row'
	int a = findRow(row);
	int b = findEnd(row);
	int i;
	int counter = 0;
	if ((a == -1) || (b == -1)) {
		return -1;
	}
	for (i = a; i <= b; i++) {
		if (rawLevelData[i] == character) {
			counter++;
		}
	}
	return counter;
}

int formatData(int character) {
	// Puts Data from rawLevelData apart...
	// blocks[row][coords]
	int i;
	int row;
	int which;
	int begin;
	int end;
	int amount;
	int pointer;

	switch (character) {
		case 'x':
			which = 0;
			break;
		case 'b':
			which = 1;
			break;
		case 'c':
			which = 2;
			break;

		case '1':
			which = 3;
			break;
		case '2':
			which = 4;
			break;
		case '3':
			which = 5;
			break;
		case '4':
			which = 6;
			break;

		default:
			return -1;
	}

	for (row = 0; row < 8; row++) {
		amount = countCharRaw(row, character);
		pointer = 0;
		if (amount == -1) {
			return -1;
		}
#ifdef DEBUG
		printf("%i times %c in row %i...\n", amount, character, row);
#endif
		begin = findRow(row);
		end = findEnd(row);
		if ((begin == -1) || (end == -1)) {
			return -1;
		}
		for (i = begin; i <= end; i++) {
			if (rawLevelData[i] == character) {
				all[which][row][pointer] = (i - begin);
				pointer++;
			}
		}
	}
	return 0;
}

int countChar(int row, char character) {
	// Count number of elements in the formatted data, as opposed to countCharRaw()...
	int first;
	int i;
	int size = MAX;
	int count = 0;
	switch (character) {
		case 'x':
			first = 0;
			break;
		case 'b':
			first = 1;
			break;
		case 'c':
			first = 2;
			break;
		case '1':
			first = 3;
			break;
		case '2':
			first = 4;
			break;
		case '3':
			first = 5;
			break;
		case '4':
			first = 6;
			break;

		default:
			return -1;
	}
	for (i = 0; i < size; i++) {
		if (all[first][row][i] != -1) {
			count++;
		} else {
			break;
		}
	}
	if (count > 0) {
		return count;
	} else {
		return 1; // We have to fill empty ones with one -1!
	}
}

int writeC(int levelnum, int xEnd, int yEnd) {
	char path[10];
	FILE *fp;
	int row;
	int first;
	int i;
	int size;
	int sizehack;

	path[0] = 'l';
	path[1] = 'e';
	path[2] = 'v';
	path[3] = 'e';
	path[4] = 'l';
	if (levelnum < 10) {
		path[5] = levelnum + '0';
		path[6] = '.';
		path[7] = 'c';
		path[8] = '\0';
	} else {
		path[6] = (levelnum % 10) + '0';
		path[5] = (levelnum / 10) + '0';
		path[7] = '.';
		path[8] = 'c';
		path[9] = '\0';
	}
	fp = fopen(path, "w");
	if (fp == NULL) {
		return -1;
	}

	fprintf(fp, "/*\n * level %i\n * generated with xythobuz' BobLevelCreator\n */\n#include \"level%i.h\"\n\n", levelnum, levelnum);
	
	for (first = 0; first < 7; first++) {
		for (row = 0; row < 8; row++) {
			fprintf(fp, "char lvl%i_", levelnum);
			switch (first) {
				case 0:
					fprintf(fp, "Block_");
					size = countChar(row, 'x');
					break;
				case 1:
					fprintf(fp, "Box_");
					size = countChar(row, 'b');
					break;
				case 2:
					fprintf(fp, "Coin_");
					size = countChar(row, 'c');
					break;
				case 3:
					fprintf(fp, "EnemyA_");
					size = countChar(row, '1');
					break;
				case 4:
					fprintf(fp, "EnemyB_");
					size = countChar(row, '2');
					break;
				case 5:
					fprintf(fp, "EnemyC_");
					size = countChar(row, '3');
					break;
				case 6:
					fprintf(fp, "EnemyD_");
					size = countChar(row, '4');
					break;

			}
			if (size == -1) {
				fclose(fp);
				return -1;
			}
			if ((size == 1) && (all[first][row][0] == -1)) {
				sizehack = size;
			} else {
				sizehack = (size + 1);
			}
			fprintf(fp, "%i[%i] = { ", row, sizehack);
			for (i = 0; i < size; i++) {
				fprintf(fp, "%i", (int)all[first][row][i]);
				if (i < (size - 1)) {
					fprintf(fp, ", ");
				}
			}
			if (sizehack != size) {
				fprintf(fp, " , -1 };\n");
			} else {
				fprintf(fp, " };\n");
			}
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");
	
	// Exit Informations:
	fprintf(fp, "char lvl%i_Exits[2] = { %i, %i };\n", levelnum, xEnd, yEnd);
	fprintf(fp, "char *lvl%i_Exit[1] = { lvl%i_Exits };\n\n", levelnum, levelnum); 

	for (first = 0; first < 7; first++) {
		fprintf(fp, "char *lvl%i_", levelnum);
		switch (first) {
			case 0:
				fprintf(fp, "Block");
				break;
			case 1:
				fprintf(fp, "Box");
				break;
			case 2:
				fprintf(fp, "Coin");
				break;
			case 3:
				fprintf(fp, "EnemyA");
				break;
			case 4:
				fprintf(fp, "EnemyB");
				break;
			case 5:
				fprintf(fp, "EnemyC");
				break;
			case 6:
				fprintf(fp, "EnemyD");
				break;
		}
		fprintf(fp, "[8] = { ");
		for (row = 0; row < 8; row++) {
			fprintf(fp, "lvl%i_", levelnum);
			switch (first) {
				case 0:
					fprintf(fp, "Block");
					break;
				case 1:
					fprintf(fp, "Box");
					break;
				case 2:
					fprintf(fp, "Coin");
					break;
				case 3:
					fprintf(fp, "EnemyA");
					break;
				case 4:
					fprintf(fp, "EnemyB");
					break;
				case 5:
					fprintf(fp, "EnemyC");
					break;
				case 6:
					fprintf(fp, "EnemyD");
					break;
			}
			fprintf(fp, "_%i", row);
			if (row < 7) {
				fprintf(fp, ", ");
			} else {
				fprintf(fp, " };\n");
			}
		}
	}
	fprintf(fp, "\n");
	
	fprintf(fp, "char **level%i[8] = { lvl%i_Block, lvl%i_Box, lvl%i_Coin, lvl%i_Exit, lvl%i_EnemyA, lvl%i_EnemyB, lvl%i_EnemyC, lvl%i_EnemyD };\n", levelnum, levelnum, levelnum, levelnum, levelnum, levelnum, levelnum, levelnum, levelnum);

	fclose(fp);
	return 0;
}

int writeH(int levelnum) {
	char path[10];
	FILE *fp;
	int row;
	int first;
	int i;
	int size;
	path[0] = 'l';
	path[1] = 'e';
	path[2] = 'v';
	path[3] = 'e';
	path[4] = 'l';
	if (levelnum < 10) {
		path[5] = levelnum + '0';
		path[6] = '.';
		path[7] = 'h';
		path[8] = '\0';
	} else {
		path[6] = (levelnum % 10) + '0';
		path[5] = (levelnum / 10) + '0';
		path[7] = '.';
		path[8] = 'h';
		path[9] = '\0';
	}
	fp = fopen(path, "w");
	if (fp == NULL) {
		return -1;
	}

	fprintf(fp, "/*\n * level %i\n * generated with xythobuz' BobLevelCreator\n */\n\n", levelnum);
	fprintf(fp, "extern char **level%i[8];\n", levelnum);

	fclose(fp);
	return 0;
}
