/*
 * Draw.h
 * by xythobuz
 *
 * Draw Blocks, Boxes, Coins and the Player!
 */

// X and Y must lie between (0|0) and (127|63) (both inclusive!)
int drawBlock(char x, char y);
int drawBox(char x, char y);
int drawCoin(char x, char y);

// Dir is the players direction:
// 0 = standing
// 1 = walking right
// 2 = walking left
// 3 = jumping right
// 4 = jumping left
// 5 = jumping
void drawPlayer(char player, char direction, char x, char y);


