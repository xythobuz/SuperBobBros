/*
 * models.c
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

/*
 * 		|-------------------------------|
 * Bit	|128|64	|32	|16	|8	|4	|2	|1	|
 * Value|0	|0	|1	|1	|1	|0	|0	|0	| The numbers in this column are the pixels, as they look later...
 * Means|x	|x+1|x+2|x+3|x+4|x+5|x+6|x+7| The result of this would be 56...
 * 		|-------------------------------|	
 */

/*
 *	Player width: 7 (x+7 = 0)
 *	Player heigth: 8
 *	Box width: 7 (x+7 = 0)
 *	Box heigth: 7 (y+7 = 0)
 *	Block width: 8
 *	Block heigth: 8
 *	Coin width: 8
 *	Coin heigth: 8
 */

// KONSTANTEN!

const unsigned char bobStanding[8] = { 56, 108, 84, 68, 56, 40, 40, 238 };
const unsigned char bobWalkingA[8] = { 56, 116, 118, 78, 56, 16, 48, 60 };
const unsigned char bobWalkingB[8] = { 56, 116, 118, 78, 56, 16, 120, 12 };
const unsigned char bobJumpStand[8] = { 56, 84, 68, 68, 56, 16, 124, 0 };
const unsigned char bobJumpSide[8] = { 56, 116, 118, 78, 56, 16, 24, 0 };
const unsigned char *bob[5] = { bobStanding, bobWalkingA, bobWalkingB, bobJumpStand, bobJumpSide };
const unsigned char **playerData[1] = { bob };

const unsigned char coin[8] = { 0, 60, 66, 90, 90, 66, 60, 0 };
const unsigned char box[7] = { 198, 184, 250, 198, 238, 255, 238 };
const unsigned char block[8] = { 255, 255, 255, 255, 255, 255, 255, 255 };

const unsigned char enemyA[8] = { 195, 36, 24, 60, 90, 153, 153, 126 };
const unsigned char *enemys[1] = { enemyA };
