#ifndef LASER_H
#define LASER_H


#include "head.h"


void insertLaser(laserClass);

void initLaser(int,int,double,double,int);

void cancelLaser(laserClass);

void changeLaser(laserClass,laserClass);

void updateLaser();
#endif