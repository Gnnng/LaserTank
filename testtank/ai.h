#ifndef AI_H
#define AI_H
#include "tank.h"
#include "map.h"
#include "Laser.h"
#include "watch.h"

enum {
	BASIC
} AItype;

int initAI(int level);
int addAI(int x,int y,void (*ctrl) (int));
void killAI(int id);
int myRand(int x);
/*================= Basic AI Action ==================*/

//int aiTurnRight(tankClass *ai,int angle/*=1,2,3*/);
int aiForward(tankClass *ai);
int aiFire(tankClass *ai);
/*================= AI Control Mode ===================*/
void aiDead(int id);
void aiControl1(int id);
void aiControl2(int id);
void ai3(int id);
void ai4(int id);
void ai5(int id);
#endif