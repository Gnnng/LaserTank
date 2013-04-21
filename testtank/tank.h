#ifndef TANK_H
#define TANK_H

#include "head.h"

void controlTank(int ,int );

int insertTank(tankClass );

int changeTank(tankClass,tankClass);

int cancelTank(tankClass );

void updateTube(int,int,int);

void initTank(void);

#endif