
#include "set.h"
#include "Laser.h"
#include "tank.h"
#include "print.h"
#include "update.h"
/*
张宇昊到此一游
*/
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
	startTimer(0,50);
	//registerTimerEvent(updateTubeSB);
	//startTimer(1,50);
	registerKeyboardEvent(controlTank);
	registerMouseEvent(updateMouse);
	return 0;
}
