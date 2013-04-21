#include "head.h"

/*
张宇昊到此一游
*/
nodeClass map[WINX+1][WINY+1];
tankClass allTank[MAXTANK];
int tankCount;
laserClass allLaser[MAXLASER];
int laserCount;
int counter=0;
int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};
int mousex,mousey;
void initMap(void)
{
	int i,j;
	for (i=0;i<=WINX;i++)
	{
		map[i][0].obj=WALL;
		map[i][WINY].obj=WALL;
	}
	for (j=0;j<=WINY;j++)
	{
		map[0][j].obj=WALL;
		map[WINX][j].obj=WALL;
	}
	tankCount=0;
	initTank();
	insertTank(allTank[1]);
	laserCount=0;
}

/*void updateTubeSB(int id)
{
	updateTube(mousex,mousey);
}*/

int Main()
{
	initWindow("LaserTank",DEFAULT,DEFAULT,WINX,WINY);
	//Menu
	//
	initMap();
	registerTimerEvent(printMap);
	startTimer(0,10);
	//registerTimerEvent(updateTubeSB);
	//startTimer(1,50);
	registerKeyboardEvent(controlTank);
	registerMouseEvent(updateMouse);
	return 0;
}
