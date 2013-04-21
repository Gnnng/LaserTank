#ifndef ACLIB_H
#define ACLIB_H
#include "acllib.h"
#endif

#ifndef STRING_H
#define STRING_H
#include<string.h>
#endif

#ifndef MATH_H
#define MATH_H
#include<math.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include<stdio.h>
#endif

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




