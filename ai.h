/*
 * ai.h
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 */

#define HOWMANYENEMYS 1

int isEnemy(int level, char x, char y, int whichEnemy);
int removeEnemy(int level, char x, char y, int whichEnemy);
int drawAI(int level, int offset);
