/*
 * mechanics.c
 * By: Thomas Buck <taucher.bodensee@gmail.com>
 * Visit: www.xythobuz.org
 * The actual game
 */
extern int hp;
extern int points;
extern int xPlayer;
extern int yPlayer;
extern int offset;
extern int level;

int playLevel(int level, char playermodel, char activateAI);
int die();
