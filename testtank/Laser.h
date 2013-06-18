#ifndef LASER_H
#define LASER_H

#define MAXLASER 1000
#define LASERLEN 50
#define LASERLIFE 50
#define LASERSPEED 15
#define LEVELNUM 2;

typedef struct _laserClass{
	int ox,oy; //original coordinates
	int x0,y0; //beginning position
	int len;
	double xt,yt; // direction of laser
	int life; // lifetime count after shooting
	int span;
	int id;
	int tankID;
	int pflag;
} laserClass;

extern laserClass allLaser[];
extern int laserCount;

void insertLaser(laserClass );

void initLaser(int,int,double,double,int,int,int);

void cancelLaser(laserClass);

void changeLaser(laserClass,laserClass);

void updateLaser();

void reflection (laserClass*,int,int);

#endif