#include "welcome.h"
#include "acllib.h"
//remaining delete

//remaining delete
void run(int tid)
{
	static int times=0;
	int startx=220,starty=400;
	runbar(startx,starty,times*5,30);
	++times;
	if (times==150) cancelTimer(0);
}
//remaining delete
void runbar(int x,int y,int wid,int hei){
	ACL_Image bar;
	char src[]=".\\image.bmp";
	beginPaint();
	//clearDevice();
	loadImage(src,&bar);
	putImageScale(&bar,x,y,wid,hei);
	endPaint();
}

void welcome()
{
	registerTimerEvent(run);
	startTimer(1,10);
}