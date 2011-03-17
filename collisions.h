/*
 * collisions.h
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 * Check if there's any kind of crap in your way
 */

/* Return Values:
 * -1 = Error
 *  0 = Nothing
 *  1 = Block
 *  2 = Box
 *  3 = Coin
 *  4 = Block at next Position
 *  5 = Box at next Position
 *  6 = Coin at next Position
 */

// (0|0) <= (x|y) < (Endless?)
// Directions: 1 = Left; 2 = Right; 3 = Up; 4 = Down;

extern char colX;
extern char colY;

int checkColPlayerUp(int x, int y, int level, int offset);
int checkColPlayerDown(int x, int y, int level, int offset);
int checkColPlayerRight(int x, int y, int level, int offset);
int checkColPlayerLeft(int x, int y, int level, int offset);
