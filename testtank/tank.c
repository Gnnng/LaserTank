#include "tank.h"
#include "laser.h"
#include <math.h>
#include "acllib.h"
#include "watch.h"
#include "update.h"
#include "map.h"

tankClass allTank[MAXTANK];
int tankCount;

void controlTube(int i,int x,int y)
{
	tankClass tank=allTank[1];
	double a,b,theta;
	a=-(tank.y-y);
	b=-(tank.x-x);
	if (b==0)  theta=(a/fabs(a))*Pi/2; else theta=a/b;
	tank.angle=atan(theta);
	if (b<0) tank.angle+=Pi;
	allTank[1]=tank;
}

void initTank(void)
{
	tankClass *tank;
	allTank[++tankCount];
	tank=allTank+tankCount;
	tank->x=getWidth()/2;
	tank->y=getHeight()/2;
	tank->width=40;
	tank->speed=5;
	tank->radius=15;
	tank->angle=0;
	tank->id=1;
	tank->dx=1;
	tank->len=30;
	tank->dy=0;
}

int insertTank(tankClass tank)
{
	int leftx,lefty,rightx,righty;
	int i,j;
	leftx=tank.x-tank.width/2;
	lefty=tank.y-tank.width/2;
	rightx=tank.x+tank.width/2;
	righty=tank.y+tank.width/2;
	for(i=leftx;i<=rightx;i++)
		for(j=lefty;j<=righty;j++)
			if (map[i][j].obj!=NOPE)
			{
					/*flag=1;*/
					return 0;
			}
	for(i=leftx;i<=rightx;i++)
		for(j=lefty;j<=righty;j++)
		{
			map[i][j].obj=TANKBODY;
			map[i][j].id=tank.id;
		}
				
	map[tank.x][tank.y].obj=TANK;
	map[tank.x][tank.y].id=tank.id;
	allTank[tank.id]=tank;
	return 1;
}

int cancelTank(tankClass tank){
	int leftx,lefty,rightx,righty;
	int i,j;
	map[tank.x][tank.y].obj=NOPE;
	leftx=tank.x-tank.width/2;
	lefty=tank.y-tank.width/2;
	rightx=tank.x+tank.width/2;
	righty=tank.y+tank.width/2;
	for(i=leftx;i<=rightx;i++)
		for(j=lefty;j<=righty;j++)
		{
			map[i][j].obj=NOPE;
		}
	return 0;
}

int changeTank(tankClass tank1,tankClass tank2){
	int ret;
	cancelTank(tank1);
	ret=insertTank(tank2);
	if (ret==0)
	{
		insertTank(tank1);
	}
	return ret;
}