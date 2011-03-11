/*
 * collisions.h
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
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

int checkColPlayer(int x, int y, char direction, int level, int Pixeloffset);
