#include "acllib.h"
#include<string.h>
#include<math.h>
#include<stdio.h>

/*

*/
#define WINX 800
#define WINY 600
#define MAXTANK 10
#define MAXLASER 100
#define MAXEXISTTIME 5
#define Pi 3.1415926

typedef struct _tankClass{
	int x,y;// position
	int dx,dy;// direction
	int speed;
	double angle;// Laser gun's angle
	int len;//laser gun's length
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
int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};
int mousex,mousey;

void printTank(nodeClass *);
void printLaser(nodeClass *);
void printMap(int );

int insertTank(tankClass );
int changeTank(tankClass ,tankClass );
int cancelTank(tankClass );

void controlTank(int ,int );

void initMap(void);
void initTank(void);
void updateTube(int,int);

void printTank(nodeClass *node)
{
	int leftx,lefty,rightx,righty;
	tankClass tank=allTank[node->id];
	updateTube(mousex,mousey);
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

void updateTube(int x,int y)
{
	
	tankClass *tank=&allTank[1];
	double a,b,theta;
	a=-(tank->y-y);
	b=-(tank->x-x);
	if (b==0)  theta=(a/fabs(a))*Pi/2; else theta=a/b;
	tank->angle=atan(theta);
	if (b<0) tank->angle+=Pi;
}

void printLaser(nodeClass *node)
{

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
	beginPaint();
	clearDevice();
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
			case LASER: printLaser(&map[i][j]); break;
			}
		}
	}
	counter++;
	if (counter==MAXEXISTTIME*1000) 
	{
		cancelTimer(0);
	}
}

void controlTank(int key,int event)
{
	tankClass tank1,tank2;
	char s[100];

	tank1=tank2=allTank[1];
	sprintf(s,"Key -> %d",key);
	beginPaint();
	paintText(700,500,s);
	endPaint();
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
		beginPaint();
		sprintf(s,"x->%d,y->%d",tank2.x,tank2.y);
		paintText(700,100,s);
		endPaint();
		tank2.action=1;
		break;
	case KEY_UP:
		tank2.action=0;
		break;
	}
	changeTank(tank1,tank2);
}
void updateMouse(int x,int y,int button,int event){
	mousex=x;
	mousey=y;
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

void initMap(void)
{
	initTank();
	insertTank(allTank[1]);
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
	map[tank.x][tank.y].obj=TANK;
	map[tank.x][tank.y].id=tank.id;
	allTank[tank.id]=tank;
	return 1;
}

int cancelTank(tankClass tank){
	map[tank.x][tank.y].obj=NOPE;
	return 0;
}

int changeTank(tankClass tank1,tankClass tank2){
	int ret;
	cancelTank(tank1);
	ret=insertTank(tank2);
	return ret;
}

void updateTubeSB(int id)
{
	updateTube(mousex,mousey);
}

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
