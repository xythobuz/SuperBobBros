/*
 * Bob.c
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
#include "fxlib.h"
#include "timer.h"
#include "keybios.h"
#include "mechanics.h"
#include "Draw.h"

char menu_data[1024] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 128, 15, 0, 12, 192, 7, 0, 0,
    0, 192, 3, 31, 0, 0, 0, 0, 224, 31, 0, 12, 240, 15, 0, 0, 0, 192, 131, 63, 0,
    0, 0, 0, 224, 56, 0, 12, 112, 28, 0, 0, 0, 192, 195, 49, 0, 252, 128, 7, 192,
    56, 28, 12, 96, 28, 0, 14, 30, 192, 195, 1, 198, 252, 193, 47, 199, 30, 62,
    236, 97, 79, 14, 31, 63, 192, 131, 3, 198, 28, 227, 236, 207, 31, 127, 252,
    225, 207, 159, 63, 51, 192, 131, 15, 67, 12, 99, 206, 205, 143, 115, 28, 227,
    135, 219, 57, 3, 192, 3, 30, 99, 12, 115, 199, 192, 143, 99, 12, 227, 135, 193,
    49, 14, 192, 3, 56, 99, 12, 243, 195, 192, 156, 97, 12, 99, 142, 193, 48, 60, 192,
    99, 48, 99, 204, 241, 192, 192, 152, 113, 12, 99, 140, 193, 56, 56, 192, 227, 49,
    115, 252, 96, 198, 192, 156, 51, 140, 99, 142, 193, 25, 113, 198, 195, 63, 254, 124,
    224, 207, 192, 15, 63, 254, 225, 135, 129, 31, 115, 206, 3, 31, 220, 12, 192, 195,
    192, 7, 30, 254, 224, 131, 1, 15, 63, 198, 3, 0, 0, 12, 0, 192, 0, 0, 12, 0, 0, 128,
    1, 6, 30, 192, 3, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 12, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 204, 255, 255, 241, 255, 255, 255, 255, 127,
    192, 31, 0, 192, 3, 0, 0, 192, 255, 255, 247, 255, 255, 255, 255, 127, 192, 63, 0, 192,
    3, 0, 0, 0, 126, 240, 135, 63, 240, 63, 127, 124, 224, 127, 0, 192, 3, 0, 0, 0, 254,
    255, 131, 255, 1, 62, 127, 124, 240, 126, 0, 192, 3, 0, 0, 0, 254, 255, 131, 255, 1,
    0, 127, 0, 240, 255, 0, 192, 3, 0, 0, 0, 126, 240, 135, 63, 240, 1, 127, 0, 248, 255,
    1, 192, 3, 0, 0, 0, 126, 240, 135, 63, 240, 1, 127, 0, 60, 252, 3, 192, 3, 0, 0, 192,
    255, 255, 247, 255, 255, 193, 255, 131, 255, 254, 31, 192, 3, 0, 0, 192, 255, 255, 243,
    255, 255, 193, 255, 131, 255, 254, 31, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 192, 195, 135, 0, 120, 4, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 192, 67, 192, 0, 132, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 192, 67, 160, 16,
    132, 206, 209, 3, 0, 0, 0, 0, 0, 0, 0, 0, 192, 67, 128, 0, 4, 36, 50, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 192, 195, 131, 0, 120, 4, 18, 1, 0, 0, 0, 0, 0, 0, 0, 0, 192, 67, 128, 0, 128,
    196, 19, 1, 0, 0, 0, 0, 0, 0, 0, 0, 192, 67, 128, 0, 132, 36, 18, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 192, 67, 128, 0, 132, 36, 19, 1, 0, 0, 0, 0, 0, 0, 0, 0, 192, 67, 128, 16, 120, 204, 18,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 252, 3, 0, 0, 0, 0, 192, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 100, 2, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 148, 2, 0, 0, 0,
    0, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 132, 2, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 100,
    2, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 192, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 2, 0, 0, 0, 0, 192, 3, 192, 1, 0, 0, 0, 0, 0, 0, 252, 3, 0, 224, 31, 0, 192, 3,
    224, 2, 0, 0, 240, 120, 0, 0, 0, 0, 0, 224, 31, 0, 192, 3, 96, 6, 0, 0, 8, 133, 0, 0, 0, 0,
    0, 224, 31, 0, 192, 3, 32, 2, 0, 0, 104, 181, 0, 0, 0, 0, 0, 224, 31, 0, 192, 3, 192, 1, 0,
    0, 104, 181, 0, 0, 0, 0, 0, 224, 31, 0, 192, 3, 128, 0, 0, 0, 8, 133, 0, 0, 0, 0, 0, 224,
    31, 0, 192, 3, 224, 1, 0, 0, 240, 120, 0, 0, 0, 0, 0, 224, 31, 0, 192, 3, 0, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 224, 31, 0, 192, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 255, 255, 255 };

int menuPixel(int x, int y) {
    int realval = x + (y * 128);
    int off = realval % 8;
    realval /= 8;
    switch (off) {
        case 0:
            off = 0x01;
            break;
        case 1:
            off = 0x02;
            break;
        case 2:
            off = 0x04;
            break;
        case 3:
            off = 0x08;
            break;
        case 4:
            off = 0x10;
            break;
        case 5:
            off = 0x20;
            break;
        case 6:
            off = 0x40;
            break;
        case 7:
            off = 0x80;
            break;
    }
    return (menu_data[realval] & off);
}

/*
 * AddIn_main()
 * Parameters are ignored!
 * Returns 1 if no error, 0 if error.
 */
int AddIn_main(int isAppli, unsigned short OptionNum) {
    
    unsigned int key;
    int x;
    int y;
Bdisp_AllClr_DDVRAM();
        for (y = 0; y < 64; y++) {
            for (x = 0; x < 128; x++) {
                if (menuPixel(x, y) != 0) {
                    Bdisp_SetPoint_VRAM(x, y, 1);
                }
            }
        }
        drawEnemy(60, 48, 0);
        locate(10, 5);
        Print((unsigned char*)"F2:AI");
        Bdisp_PutDisp_DD();

    while(1) {
        
        GetKey(&key);
        if (key == KEY_CTRL_F1) {
            playLevel(1, 0, 0);
Bdisp_AllClr_DDVRAM();
        for (y = 0; y < 64; y++) {
            for (x = 0; x < 128; x++) {
                if (menuPixel(x, y) != 0) {
                    Bdisp_SetPoint_VRAM(x, y, 1);
                }
            }
        }
        drawEnemy(60, 48, 0);
        locate(10, 5);
        Print((unsigned char*)"F2:AI");
        Bdisp_PutDisp_DD();
        } else if (key == KEY_CTRL_F2) {
            playLevel(1, 0, 1);
Bdisp_AllClr_DDVRAM();
        for (y = 0; y < 64; y++) {
            for (x = 0; x < 128; x++) {
                if (menuPixel(x, y) != 0) {
                    Bdisp_SetPoint_VRAM(x, y, 1);
                }
            }
        }
        drawEnemy(60, 48, 0);
        locate(10, 5);
        Print((unsigned char*)"F2:AI");
        Bdisp_PutDisp_DD();
        }
    }
    return 1;
}

// Casio's initialization code:
#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum) {
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section

