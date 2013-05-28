#include "ai.h"
#include "tank.h"
#include "map.h"
#include "Laser.h"
#include "watch.h"
#include <math.h>

int ai()
{
	int i;
	tankClass *aitank;
	initTank();
	i=tankCount;
	aitank=&allTank[i];
	watch("AI i=",i);
	aitank->x=100;
	aitank->y=100;
	aitank->dx=1;
	aitank->dy=0;
	aitank->move=50;
	insertTank(*aitank);
}
	
void aiControl(){
	tankClass *ai=&allTank[tankCount];
	tankClass tank1,tank2;
	static int accu;
	int dx0,dy0;
	//if (++accu<=10) return;
	if (ai->move==0) {
		ai->move=50;
		dx0=ai->dx;
		dy0=ai->dy;
		ai->dx=-dy0;
		ai->dy=dx0;
		if (ai->dy==1) ai->angle=Pi/2;
		if (ai->dy==-1) ai->angle=3*Pi/2;
		if (ai->dx==1) ai->angle=0;
		if (ai->dx==-1) ai->angle=Pi;
	}
	ai->move--;
	tank1=tank2=allTank[tankCount];
	tank2.x+=tank2.speed*tank2.dx;
	tank2.y+=tank2.speed*tank2.dy;
	changeTank(tank1,tank2);
	accu=0;
}