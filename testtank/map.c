#include "acllib.h"
#include "tank.h"
#include "laser.h"
#include "watch.h"
#include "update.h"
#include "map.h"
#include <math.h>

nodeClass map[WINX+1][WINY+1];
int counter=0;

int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};

void printTank(nodeClass *node)
{
	int leftx,lefty,rightx,righty;
	tankClass tank=allTank[node->id];
	leftx=tank.x-tank.width/2;
	lefty=tank.y-tank.width/2;
	rightx=tank.x+tank.width/2;
	righty=tank.y+tank.width/2;
	beginPaint();
	setBrushColor(EMPTY);
	rectangle(leftx,lefty,rightx,righty);
	ellipse(tank.x-tank.radius,tank.y-tank.radius,tank.x+tank.radius,tank.y+tank.radius);
	setPenWidth(3);
	line(tank.x,tank.y,tank.x+(int)(tank.len*cos(tank.angle)),tank.y+(int)(tank.len*sin(tank.angle)));
	setPenWidth(1);
	endPaint();
}
void printLaser(int i)
{
	if (allLaser[i].pflag) return;
	allLaser[i].pflag=1;
	beginPaint();
	line(allLaser[i].x0,allLaser[i].y0,allLaser[i].x0+allLaser[i].len*allLaser[i].xt,allLaser[i].y0+allLaser[i].len*allLaser[i].yt);
	endPaint();
}

void printMap(int tid)
{
	int i,j;
	static int cc;
	updateWithMap();
	beginPaint(); 
#ifdef SHADOW
	cc++;
	if (cc==15)
	{
#endif
		//clearDevice();
		setBrushColor(WHITE);
		rectangle(0,0,WINX,WINY);
#ifdef SHADOW
		cc=0;
	}
#endif
	endPaint();
	watch("Counter ->",counter);
	for(i=0;i<WINX;i++)
	{
		for(j=0;j<WINY;j++)
		{
			switch (map[i][j].obj)
			{
			case NOPE: break;
			case WALL: break;
			case TANK: printTank(&map[i][j]); break;
			case LASER: if (allLaser[map[i][j].id].life>0) printLaser(map[i][j].id); break;
			}
		}
	}
	counter++;
	if (counter==MAXEXISTTIME*1000) 
	{
		cancelTimer(0);
	}
}

void setWall(int fx,int fy,int tx,int ty){
	if (fx==tx) {
		for(;fy!=ty;fy<ty?fy++:fy--)
			map[fx][fy].obj=WALL;
	}
	if (fy==ty) {
		for(;fx!=tx;fx<tx?fx++:fx--)
			map[fx][fy].obj=WALL;
	}
}

void initMap()
{
	int i,j;
	for (i=0;i<=WINX;i++)
	{
		map[i][0].obj=WALL;
		map[i][WINY].obj=WALL;
	}
	//setWall(0,400,WINX/2,400);
	//setWall(WINX/2,400,WINX/2,100);
	for (j=0;j<=WINY;j++)
	{
		map[0][j].obj=WALL;
		map[WINX][j].obj=WALL;
	}
	tankCount=0;
	laserCount=0;
	initTank();
	insertTank(allTank[1]);
}