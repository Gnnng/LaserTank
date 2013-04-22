#include "head.h"
#include "extern.h"
#include "watch.h"

void updateTube(int i,int x,int y)
{
	
	tankClass tank=allTank[i];
	double a,b,theta;
	a=-(tank.y-y);
	b=-(tank.x-x);
	if (b==0)  theta=(a/fabs(a))*Pi/2; else theta=a/b;
	tank.angle=atan(theta);
	if (b<0) tank.angle+=Pi;
	allTank[i]=tank;
}

void controlTank(int key,int event)
{
	tankClass tank1,tank2;
	char s[100];

	tank1=tank2=allTank[1];
	watch("Key ->",key);
	/*sprintf(s,"Key -> %d",key);
	beginPaint();
	paintText(700,500,s);
	endPaint();*/
	switch(key)
	{
	case 87:key=UP;break;
	case 65:key=LEFT;break;
	case 83:key=DOWN;break;
	case 68:key=RIGHT;break;
	}
	switch(event){
	case KEY_DOWN:
		tank2.x+=tank2.speed*dx[key-LEFT];
		tank2.y+=tank2.speed*dy[key-LEFT];
		watch("tank x ->",tank2.x);
		watch("tank y ->",tank2.y);
		/*beginPaint();
		sprintf(s,"x->%d,y->%d",tank2.x,tank2.y);
		paintText(700,100,s);
		endPaint();*/
		tank2.action=1;
		break;
	case KEY_UP:
		tank2.action=0;
		break;
	}
	changeTank(tank1,tank2);
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