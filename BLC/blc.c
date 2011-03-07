/*
 * Bob Level Creator
 * by xythobuz
 *
 * This program takes a draft for a Level and converts it to a .c File.
 * Refer to the Readme for more informations on the level-draft.
 */

#include <stdio.h>
#define MAXROWLENGTH 1000
#define MAXRAWLENGTH 8100
#define MAXBLOCKPROW 256
#define MAXCOINBOXPR 50

/*
#define DEBUG
*/

int rawLevelData[MAXRAWLENGTH];
int block0[MAXBLOCKPROW];
int block1[MAXBLOCKPROW];
int block2[MAXBLOCKPROW];
int block3[MAXBLOCKPROW];
int block4[MAXBLOCKPROW];
int block5[MAXBLOCKPROW];
int block6[MAXBLOCKPROW];
int block7[MAXBLOCKPROW];
int box0[MAXCOINBOXPR];
int box1[MAXCOINBOXPR];
int box2[MAXCOINBOXPR];
int box3[MAXCOINBOXPR];
int box4[MAXCOINBOXPR];
int box5[MAXCOINBOXPR];
int box6[MAXCOINBOXPR];
int box7[MAXCOINBOXPR];
int coin0[MAXCOINBOXPR];
int coin1[MAXCOINBOXPR];
int coin2[MAXCOINBOXPR];
int coin3[MAXCOINBOXPR];
int coin4[MAXCOINBOXPR];
int coin5[MAXCOINBOXPR];
int coin6[MAXCOINBOXPR];
int coin7[MAXCOINBOXPR];
int *blocks[8] = {block0, block1, block2, block3, block4, block5, block6, block7};
int *boxes[8] = {box0, box1, box2, box3, box4, box5, box6, box7};
int *coins[8] = {coin0, coin1, coin2, coin3, coin4, coin5, coin6, coin7};
int **all[3] = {blocks, boxes, coins};

char OutputHeader[] = "/*\n * generated with xythobuz' BobLevelCreator\n */\n";

/*
 * Copy contents of level file into rawLevelData[].
 * @arg name String with level file path
 * @return length if all is okay, -1 if file could not be opened, -2 if file is too large.
 */
int readLevelFile(char *name);

/*
 * Check if the header in rawLevelData is okay.
 * @return 0 if ok, 1 if not.
 */
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
	int size;
	for (i = 0; i < 3; i++) {
		if (i > 0) {
			size = MAXCOINBOXPR;
		} else {
			size = MAXBLOCKPROW;
		}
		for (j = 0; j < 8; j++) {
			for (k = 0; k < MAXBLOCKPROW; k++) {
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
		printf("Error while formating data!\n");
		return 1;
	}
	if (formatData('b') == -1) {
		printf("Error while formating data!\n");
		return 1;
	}
	if (formatData('c') == -1) {
		printf("Error while formating data!\n");
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
	int i;
	for (i = 0; i < MAXRAWLENGTH - 2; i++) {
		if ( (rawLevelData[i] == ((char)row + '0')) && (rawLevelData[i + 1] == '|') ) {
			return (i + 2);
		}
	}
	return -1;
}

int findEnd(int row) {
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
	int size;
	int count = 0;
	switch (character) {
		case 'x':
			first = 0;
			size = MAXBLOCKPROW;
			break;
		case 'b':
			first = 1;
			size = MAXCOINBOXPR;
			break;
		case 'c':
			first = 2;
			size = MAXCOINBOXPR;
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
	
	for (first = 0; first < 3; first++) {
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

	for (first = 0; first < 3; first++) {
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
	
	fprintf(fp, "char **level%i[4] = { lvl%i_Block, lvl%i_Box, lvl%i_Coin, lvl%i_Exit };\n", levelnum, levelnum, levelnum, levelnum, levelnum);

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
	fprintf(fp, "extern char **level%i[4];\n", levelnum);

	fclose(fp);
	return 0;
}
