#include "ai.h"
#include "tank.h"
#include "map.h"
#include "Laser.h"
#include "watch.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

int initAI()
{
	//addAI(100,100);
	//allTank[tankCount].ctrl=aiControl1;
	//addAI(60,500);
	//allTank[tankCount].ctrl=aiControl2;
	addAI(100,400);
	allTank[tankCount].ctrl=ai3;
}

void addAI(int x,int y)
{
	int i;
	tankClass *aitank;

	initTank(++tankCount);
	i=tankCount;
	aitank=&allTank[i];
	watch("AI i=",i);
	aitank->x=x;
	aitank->y=y;
	aitank->dx=1;
	aitank->dy=0;
	aitank->tubeLock=1;
	aitank->move=50;
	insertTank(*aitank);
}

void aiControl1(int id){
	tankClass *ai=&allTank[id];
	tankClass tank1,tank2;
	int dx0,dy0;
	if (ai->move==0) {
		ai->move=50;
		/* version 1
		dx0=ai->dx;
		dy0=ai->dy;
		ai->dx=-dy0;
		ai->dy=dx0;
		*/
		aiTurnRight(&allTank[id],1);
		//if (ai->dy==1) ai->angle=Pi/2;
		//if (ai->dy==-1) ai->angle=3*Pi/2;
		//if (ai->dx==1) ai->angle=0;
		//if (ai->dx==-1) ai->angle=Pi;
	}
	ai->move--;
	tank1=tank2=allTank[id];
	tank2.x+=tank2.speed*tank2.dx;
	tank2.y+=tank2.speed*tank2.dy;
	changeTank(tank1,tank2);
}

int myRand(int x){
	srand((int)clock());
	return rand()%x;
}

int aiTurnRight(tankClass *ai,int angle/*=1,2,3*/){
	int dx0,dy0;
	dx0=ai->dx;
	dy0=ai->dy;
	switch(angle) {
	case 1:
		ai->dx=-dy0;
		ai->dy=dx0;
		break;
	case 2:
		ai->dx=-dx0;
		ai->dy=-dy0;
		break;
	case 3:
		ai->dx=dy0;
		ai->dy=-dx0;
		break;
	}
	return 0;
}

int aiForward(tankClass *ai){
	ai->x+=ai->speed*ai->dx;
	ai->y+=ai->speed*ai->dy;
	return 0;
}

int aiFire(tankClass *ai) {
	int x0,y0;
	double len;
	int x,y;
	//x=mousex;
	//y=mousey;
	x0=ai->x;
	y0=ai->y;
	//len=sqrt((double)((x-x0)*(x-x0)+(y-y0)*(y-y0)));
	x0=x0+cos(ai->angle)*(ai->len);
	y0=y0+sin(ai->angle)*(ai->len);
	//watch("New laser X0",x0);
	//watch("New laser Y0",y0);
	initLaser(x0,y0,cos(ai->angle),sin(ai->angle),LASERSPEED);
	watch("ai angle",ai->angle/Pi);
	watch("ai tubelock",ai->tubeLock);
	insertLaser(allLaser[laserCount]);
}
void aiControl2(int id)  //遇到障碍物就掉头
{
	tankClass tank1,tank2;
	tank1=tank2=allTank[id];
	aiForward(&tank2);
	if (changeTank(tank1,tank2)==0) {
		tank1=tank2=allTank[id];
		aiTurnRight(&tank2,2);
		changeTank(tank1,tank2);
	}
	if (!myRand(100)) aiFire(allTank+id);
}

void ai3(int id) //遇到障碍就右转
{
	static int tt;
	tankClass tank1,tank2;
	tank1=tank2=allTank[id];
	aiForward(&tank2);
	if (changeTank(tank1,tank2)==0) {
		tank1=tank2=allTank[id];
		aiTurnRight(&tank2,1);
		changeTank(tank1,tank2);
	}
	if(tt==100) 
	{
		aiFire(allTank+id);
		tt=0;
	}
	tt++;
}

