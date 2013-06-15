#include "tank.h"
#include "laser.h"
#include <math.h>
#include "acllib.h"
#include "watch.h"
#include "update.h"
#include "map.h"

tankClass allTank[MAXTANK];
int tankCount;


double getAngle(int ax,int ay,int bx,int by) //angle from a to b
{
	double ans;
	double ux,uy,theta;
	uy=by-ay;
	ux=bx-ax;
	if (ux==0) {
		if (uy>0) ans=Pi/2; else ans=3*Pi/2;
		return ans;
	}
	else theta=uy/ux;
	ans=atan(theta);
	if (ux<0) ans+=Pi;
	if (ans<0) ans+=Pi*2;
	return ans;
}

void controlTube(int i,int x,int y)
{
	tankClass tank=allTank[1];
	/*double a,b,theta;
	a=-(tank.y-y);
	b=-(tank.x-x);
	if (b==0)  theta=(a/fabs(a))*Pi/2; else theta=a/b;
	tank.angle=atan(theta);
	if (b<0) tank.angle+=Pi;
	*/
	tank.angle=getAngle(tank.x,tank.y,x,y);
	allTank[1]=tank;

}
  
void initTank(int id)
{
	tankClass *tank=&allTank[id];
	//++tankCount;
	tank=allTank+tankCount;
	tank->x=getWidth()/2;
	tank->y=getHeight()/2;
	tank->width=40;
	tank->speed=5;
	tank->radius=15;
	tank->angle=0;
	tank->id=tankCount;
	tank->dx=1;
	tank->len=31;
	tank->dy=0;
	tank->fireCD=MAXCD;
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

int autoRun()
{
	tankClass tank1,tank2;
	tank1=tank2=allTank[1];
	if (tank1.action) {
		tank2.x+=tank2.speed*tank2.dx;
		tank2.y+=tank2.speed*tank2.dy;
	}
	changeTank(tank1,tank2);
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