#include "acllib.h"
#include<string.h>
#include<math.h>
#include<stdio.h>

#define WINX 800
#define WINY 600
#define MAXTANK 10
#define MAXLASER 100
#define MAXEXISTTIME 5
#define LASERLEN 100
#define LASERT 30
#define LASERSPEED 15
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
	int fx0,fy0;
	int x0,y0; //beginning position
	int len;
	double xt,yt; // direction of laser
	int t; // time count after shoot
	int id;
} laserClass;

typedef enum{
	NOPE,
	WALL,
	TANK,
	LASER,
	TANKBODY
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
void updateTube(int,int,int);
void timeupdate();

void insertLaser(laserClass);
void initLaser(int,int,double,double,int);
void cancelLaser(laserClass);
void changeLaser(laserClass,laserClass);
void updateLaser();
