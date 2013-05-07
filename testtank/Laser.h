#ifndef LASER_H
#define LASER_H

#define MAXLASER 100
#define LASERLEN 100
#define LASERT 30
#define LASERSPEED 15

typedef struct _laserClass{
	int fx0,fy0;
	int x0,y0; //beginning position
	int len;
	double xt,yt; // direction of laser
	int t; // time count after shoot
	int id;
} laserClass;

extern laserClass allLaser[];
extern int laserCount;

void insertLaser(laserClass );

void initLaser(int,int,double,double,int);

void cancelLaser(laserClass);

void changeLaser(laserClass,laserClass);

void updateLaser();

#endif