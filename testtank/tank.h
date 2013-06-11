#ifndef TANK_H
#define TANK_H

#define MAXTANK 10
typedef struct _tankClass{
	int x,y;// position
	int dx,dy;// direction
	int speed;
	double angle;// Laser gun's angle
	double RollSpeed;
	int len;//laser gun's length
	int width;
	int radius;
	int id;
	int action;
	//new properties
	int move;
	char tubeLock;
	char fireCD;
	void (*ctrl) (int);
} tankClass;

extern tankClass allTank[MAXTANK];
extern int tankCount;

int autoRun();
void controlTank(int ,int );

int insertTank(tankClass );

int changeTank(tankClass,tankClass);

int cancelTank(tankClass );

void controlTube(int,int,int);

void initTank(int id);

double getAngle(int,int,int,int);
#endif