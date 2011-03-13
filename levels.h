/*
 * levels.h
 * By: Thomas Buck <taucher.bodensee@googlemail.com>
 * Visit: www.xythobuz.org
 */
#define HOWMANYLEVELS 3 // Jetzt noch speichern, level3 reinkopieren, und fertig

// levels[lvl.num.][type][y][index]
extern char ***levels[HOWMANYLEVELS];

int getsizeBlocks(int level, char y);
int getsizeBox(int level, char y);
int getsizeCoin(int level, char y);

int removeBox(int level, char x, char y);
int removeCoin(int level, char x, char y);

int isBox(int level, char x, char y);
int isBlock(int level, char x, char y);
int isCoin(int level, char x, char y);
