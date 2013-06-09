#ifndef AI_H
#define AI_H
#include "tank.h"
#include "map.h"
#include "Laser.h"
#include "watch.h"

enum {
	BASIC
} AItype;

int initAI();
void addAI();
void aiControl1(int id);
void aiControl2(int id);
void ai3(int id);
#endif