/*
 * collisions.h
 *
 * Copyright 2011 Thomas Buck, Max Nuding
 *
 * This file is part of SuperBobBros.
 * SuperBobBros is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SuperBobBros is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SuperBobBros. If not, see <http://www.gnu.org/licenses/>.
 *
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
