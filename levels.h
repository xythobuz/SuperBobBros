/*
 * levels.h
 * By: Thomas Buck <taucher.bodensee@googlemail.com>
 * Visit: www.xythobuz.org
 */
#define HOWMANYLEVELS 4

// levels[lvl.num.][type][y][index]
extern char ***levels[HOWMANYLEVELS];

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
