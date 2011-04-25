/*
 * models.h
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

// player[pl.model][anim][y]
// pl.model: Which player model (0 = Bob)
// anim: 0=bobStanding; 1=bobWalkingA; 2=bobWalkingB; 3=bobJumpStand; 4=bobJumpSide
// 0 <= y <= 7
extern const unsigned char **playerData[1];

extern const unsigned char coin[8];
extern const unsigned char box[7];
extern const unsigned char block[8];

extern const unsigned char *enemys[1];
