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
	addAI(100,100,aiControl1);
	addAI(300,300,aiControl2);
	addAI(100,400,ai3);
}

int addAI(int x,int y,void (*ctrl) (int))
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
	aitank->RollSpeed=Pi/180;
	aitank->move=50;
	aitank->fireCD=myRand(MAXCD);
	insertTank(*aitank);
	aitank->ctrl=ctrl;
	return i;
}

int aiTurnRight(tankClass *ai,int angle){
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

int myRand(int x){
	srand((int)clock());
	return rand()%x;
}

int aiTubeRoll(tankClass *ai) {
	ai->tubeLock=0;
	ai->angle+=ai->RollSpeed;
	if (ai->angle>=2*Pi) ai->angle-=2*Pi;
}

int aiTubeTurnTo(tankClass *ai,double goal) {
	double delta;
	ai->tubeLock=0;
	delta=fabs(goal-ai->angle);
	ai->angle+=ai->RollSpeed*(goal>=ai->angle?1:-1)*(delta<=Pi?1:-1);
	if (ai->angle>=2*Pi) ai->angle-=2*Pi;
	if (ai->angle<0) ai->angle+=2*Pi;
}

int aiFireSeeing(tankClass *ai)
{
	const double fireScope=Pi/12;
	double dangle;
	dangle=ai->angle-getAngle(ai->x,ai->y,allTank[1].x,allTank[1].y);
	if (dangle<=fireScope&&dangle>=-fireScope){
		if (ai->fireCD) return;
		aiFire(ai);
	}
	watch("getangle",getAngle(ai->x,ai->y,allTank[1].x,allTank[1].y)/Pi*180);
}

int aiForward(tankClass *ai){
	//playSound(tankMove,0);
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
	
	initLaser(x0,y0,cos(ai->angle),sin(ai->angle),LASERSPEED,LASERLIFE,ai->id);
	watch("ai angle",ai->angle/Pi);
	watch("ai tubelock",ai->tubeLock);
	insertLaser(allLaser[laserCount]);
	allLaser[laserCount].tankID=ai->id;
	//playSound(laserFire,0);
	ai->fireCD=MAXCD;
}

void aiControl1(int id) //正方形路线+自动射击
{
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
	aiTubeTurnTo(allTank+id,getAngle(tank2.x,tank2.y,allTank[1].x,allTank[1].y));
	if (tank2.fireCD) return;
	aiFire(allTank+id);
}

void aiControl2(int id)  //遇到障碍物就掉头+见人就射击
{
	tankClass tank1,tank2,*ai=allTank+id;
	tank1=tank2=allTank[id];
	aiForward(&tank2);
	if (changeTank(tank1,tank2)==0) {
		tank1=tank2=allTank[id];
		aiTurnRight(&tank2,2);
		changeTank(tank1,tank2);
	}
	
	//aiTubeRoll(ai);
	aiTubeTurnTo(ai,getAngle(allTank[id].x,allTank[id].y,allTank[1].x,allTank[1].y));
	aiFireSeeing(ai);
	//if (!myRand(100)) aiFire(allTank+id);
}


void ai3(int id) //遇到障碍就右转+自动射击
{
	tankClass tank1,tank2;
	tank1=tank2=allTank[id];
	aiForward(&tank2);
	if (changeTank(tank1,tank2)==0) {
		tank1=tank2=allTank[id];
		aiTurnRight(&tank2,1);
		changeTank(tank1,tank2);
	}
	if (allTank[id].fireCD) return;
	aiFire(allTank+id);
}

//void ai4(int id) //完全随机行走
//{
//