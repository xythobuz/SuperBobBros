/*
 * levels.h
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

int freeMem();
int existLevel(int level);
// curLevel[type][y][i]
extern char **curLevel[8];
extern int loadedLevel;

int getsizeBlocks(int level, char y);
int getsizeBox(int level, char y);
int getsizeCoin(int level, char y);
// Same as other size functions, but tell it which Enemy-Type you want to check (0 - 3)
int getsizeEnemy(int level, char y, int whichEnemy);

int removeBox(int level, char x, char y);
int removeCoin(int level, char x, char y);
int removeEnemyRaw(int level, char x, char y, int whichEnemy);

int isBox(int level, char x, char y);
int isBlock(int level, char x, char y);
int isCoin(int level, char x, char y);
int isEnemyRaw(int level, char x, char y, int whichEnemy);
