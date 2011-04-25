/*
 * Draw.h
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

// X and Y must lie between (0|0) and (127|63) (both inclusive!)
int drawBlock(char x, char y);
int drawBox(char x, char y);
int drawCoin(char x, char y);
int drawEnemy(char x, char y, char enemy);

// Dir is the players direction:
// 0 = standing
// 1 = walking right
// 2 = walking left
// 3 = jumping right
// 4 = jumping left
// 5 = jumping
int drawPlayer(char player, char direction, char x, char y);
void clear();
void draw();
