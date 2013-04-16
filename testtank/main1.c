//#include "acllib.h"
//#include<math.h>
//
//const double PI=3.1415926;
//typedef struct tanktank {
//	//private
//	double angle;
//	int width,length,radius;	
//	int x,y;
//	//public
//	MouseEventCallback mouse;
//	KeyboardEventCallback keyboard;
//} TankType;
//
//struct tanktank lijiacheng;
//void rect(int startx,int starty,int width,int height)
//{
//	beginPaint();
//	setPenWidth(4);
//	moveTo(startx-width/2,starty-height/2);
//	lineTo(startx-width/2,starty+height/2);
//	lineTo(startx+width/2,starty+height/2);
//	lineTo(startx+width/2,starty-height/2);
//	lineTo(startx-width/2,starty-height/2);
//	setPenWidth(1);
//	endPaint();
//}
//int circle(int x,int y,int r)
//{
//	beginPaint();
//	setBrushColor(WHITE);
//	setPenWidth(4);
//	ellipse(x-r,y-r,x+r,y+r); 
//	setPenWidth(1);
//	endPaint();
//	return 0;
//}
//
//int tube(int startx,int starty,int endx,int endy)
//{
//	beginPaint();
//	setPenWidth(4);
//	line(startx,starty,endx,endy);
//	setPenWidth(1);
//	endPaint();
//	return 0;
//}
//
//int insertTank(TankType tank){
//	rect(tank.x,tank.y,tank.width,tank.width);
//	circle(tank.x,tank.y,tank.radius);
//	tube(tank.x,tank.y,tank.x+tank.length*cos(tank.angle),tank.y+tank.length*sin(tank.angle));
//	return 0;
//}
//
//void tuberotate(int tid)
//{
//	static int times=0;
//	const double delta=PI/180*5;
//
//	beginPaint();
//	clearDevice();
//	endPaint();
//	lijiacheng.angle+=delta;
//	lijiacheng.x+=5;
//	times++;
//	insertTank(lijiacheng);
//	if (times==100) cancelTimer(0);
//}
///*
//int Main() // Setup
//{
//	lijiacheng.angle=PI/6;
//	lijiacheng.length=20*4;
//	lijiacheng.width=20*4;
//	lijiacheng.radius=8*4;
//	lijiacheng.x=80;
//	lijiacheng.y=80;
//	initWindow("Tank LJC!!!",DEFAULT,DEFAULT,800,600);
//	//insertTank(lijiacheng);
//	registerTimerEvent(tuberotate);
//	startTimer(0,100);
//	return 0;
//}
//*/