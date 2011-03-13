/*
 * models.h
 * By: Thomas Buck <taucher.bodensee@googlemail.com>
 * Visit: www.xythobuz.org
 *Defines the look of Penis, boex and block, etc....
 */

// player[pl.model][anim][y]
// pl.model: Which player model (0 = Bob)
// anim: 0=bobStanding; 1=bobWalkingA; 2=bobWalkingB; 3=bobJumpStand; 4=bobJumpSide
// 0 <= y <= 7
extern const char **playerData[1];

extern const char coin[8];
extern const char box[7];
extern const char block[8];
