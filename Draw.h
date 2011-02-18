/*
 * Draw.h
 * by xythobuz
 *
 * Draw Blocks, Boxes, Coins and the Player!
 */

// X and Y must lie between (0|0) and (15|7) (both inclusive!)
void DrawBlock(char x, char y);
void DrawBox(char x, char y);
void DrawCoin(char x, char y);

// Dir is the players direction:
// 0 = standing
// 1 = walking right
// 2 = walking left
// 3 = jumping right
// 4 = jumping left
// 5 = jumping
void DrawPlayer(char x, char y, char dir);

// Clear Buffer
void clear();
// Clear screen, transmit buffer!
void draw();
