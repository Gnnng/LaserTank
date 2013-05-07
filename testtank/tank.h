#ifndef TANK_H
#define TANK_H

#define MAXTANK 10


extern int tankCount;

typedef struct _tankClass{
	int x,y;// position
	int dx,dy;// direction
	int speed;
	double angle;// Laser gun's angle
	int len;//laser gun's length
	int width;
	int radius;
	int id;
	int action;
} tankClass;

extern tankClass allTank[MAXTANK];

void controlTank(int ,int );

int insertTank(tankClass );

int changeTank(tankClass,tankClass);

int cancelTank(tankClass );

void controlTube(int,int,int);

void initTank(void);

#endif