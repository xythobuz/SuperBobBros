/*
 * models.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */

/*
 * 		|-------------------------------|
 * Bit	|128|64	|32	|16	|8	|4	|2	|1	|
 * Value|0	|0	|1	|1	|1	|0	|0	|0	|
 * Means|x	|x+1|x+2|x+3|x+4|x+5|x+6|x+7|
 * 		|-------------------------------|	
 */

/*
 *	Player width: 7 (x+7 = 0)
 *	Player heigth: 8
 *	Box width: 7 (x+7 = 0)
 *	Box heigth: 7 (x+7 = 0)
 *	Block width: 8
 *	Block heigth: 8
 *	Coin width: 8
 *	Coin heigth: 8
 */

// KONSTANTEN!

const char bobStanding[8] = { 56, 108, 84, 68, 56, 40, 40, 238 };
const char bobWalkingA[8] = { 56, 116, 118, 78, 56, 16, 48, 60 };
const char bobWalkingB[8] = { 56, 116, 118, 78, 56, 16, 120, 12 };
const char bobJumpStand[8] = { 56, 84, 68, 68, 56, 16, 124, 0 };
const char bobJumpSide[8] = { 56, 116, 118, 78, 56, 16, 24, 0 };
const char *bob[5] = { bobStanding, bobWalkingA, bobWalkingB, bobJumpStand, bobJumpSide };
const char **playerData[1] = { bob };

const char coin[8] = { 0, 60, 66, 90, 90, 66, 60, 0 };
const char box[7] = { 198, 184, 250, 198, 238, 255, 238 };
const char block[8] = { 255, 255, 255, 255, 255, 255, 255, 255 };
