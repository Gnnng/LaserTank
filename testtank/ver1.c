#include "acllib.h"
#include<string.h>

/*

*/
#define WINX 800
#define WINY 600
#define MAXTANK 10
#define MAXLASER 100
#define MAXEXISTTIME 5

typedef struct _tankClass{
	int x,y;// position
	int dx,dy;// direction
	int speed;
	double angle;// Laser gun's angle
	int width;
	int radius;
	int id;
	int action;
} tankClass;

typedef struct _laserClass{
	int x0,y0; //beginning position
	int len;
	int xt,yt; // direction of laser
	int t; // time count after shoot
} laserClass;

typedef enum{
	NOPE,
	WALL,
	TANK,
	LASER
} nodeObj;

typedef enum {
	LEFT=37,
	UP,
	RIGHT,
	DOWN
};

typedef struct _nodeClass{
	// the type of the map
	// x,y;
	nodeObj obj;
	int id;
} nodeClass;

nodeClass map[WINX+1][WINY+1];
tankClass allTank[MAXTANK];
int tankCount;
laserClass allLaser[MAXLASER];
int laserCount;
static int counter=0;



void printTank(int x,int y,nodeClass *node)
{

}

void printLaser(int x,int y,nodeClass *node)
{

}

void printMap(int tid)
{
	int i,j;
	beginPaint();
	clearDevice();
	endPaint();
	for(i=0;i<WINX;i++)
	{
		for(j=0;j<WINY;j++)
		{
			switch (map[i][j].obj)
			{
			case NOPE: break;
			case WALL: break;
			case TANK: printTank(i,j,&map[i][j]); break;
			case LASER: printLaser(i,j,&map[i][j]); break;
			}
		}
	}
	counter++;
	if (counter==MAXEXISTTIME*1000) 
	{
		cancelTimer(0);
	}
}

void readKey(int key,int event)
{

}

void initMap()
{

}

bool insertTank(int x,int y)
{
	int leftx,lefty,rightx,righty;
	bool ifTank;



	allTank[tankCount++];
	

}

int Main()
{
	initWindow("LaserTank",DEFAULT,DEFAULT,WINX,WINY);
	//Menu
	//
	initMap();
	startTimer(0,100);
	registerTimerEvent(printMap);
	registerKeyboardEvent(readKey);
}
