#include "head.h"
#include "extern.h"

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
	beginPaint();
	line(allLaser[i].x0,allLaser[i].y0,allLaser[i].x0+allLaser[i].len*allLaser[i].xt,allLaser[i].y0+allLaser[i].len*allLaser[i].yt);
	endPaint();

}

void printCount(void)
{
	char s[100];
	beginPaint();
	setTextSize(10);
	setTextColor(BLACK);
	sprintf(s,"Counter -> %d",counter);
	paintText(100,100,s);
	endPaint();
}
void printMap(int tid)
{
	int i,j;
	static int cc;
	timeupdate();
	beginPaint();
	cc++;
	if (cc==15)
	{
		clearDevice();
		cc=0;
	}
	endPaint();
	printCount();

	for(i=0;i<WINX;i++)
	{
		for(j=0;j<WINY;j++)
		{
			switch (map[i][j].obj)
			{
			case NOPE: break;
			case WALL: break;
			case TANK: printTank(&map[i][j]); break;
			case LASER: if (allLaser[map[i][j].id].t>0) printLaser(map[i][j].id); break;
			}
		}
	}
	counter++;
	if (counter==MAXEXISTTIME*1000) 
	{
		cancelTimer(0);
	}
}
