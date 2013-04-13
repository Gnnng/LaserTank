#include"acllib.h"
#include<string.h>
#include<stdio.h>

typedef enum {
	LEFT=37,
	UP,
	RIGHT,
	DOWN
};

void drawWhenClick(int x,int y,int button,int event)
{
	if (event!=5) return;
	beginPaint();
	clearDevice();
	moveTo(0,0);
	lineTo(x,y);
	endPaint();
}

void draw1(int x,int y,int button,int event)
{
	static int ux=0,uy=0;
	if (button=LEFT_BUTTON &&( event==MOUSEMOVE || event==BUTTON_DOWN))
	{
		if (ux==0&&uy==0) 
		{
			ux=x;
			uy=y;
			return;
		}
		beginPaint();
		line(ux,uy,x,y);
		ux=x,uy=y;
		endPaint();
	}
}

void testkeyvalue(int key,int event)
{
	static int ux,uy;
	char s[100]="haha";
	if (ux==0&&uy==0)
	{
		ux=100;
		uy=getHeight()/2;
		return;
	}
	if (event=KEY_DOWN||event==KEY_UP)
	{
		beginPaint();
		sprintf(s,"%d",key);
		paintText(ux,uy,s);
		ux+=40;
		if (ux>=700)
		{
			uy+=20;
			ux=100;
		}
		endPaint();
	}
}

void movePoint(int key,int event)
{
	static int x,y;
	int dir;
	int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
	const int delta=5;
	if (!x&&!y) x=getWidth()/2,y=getHeight()/2;
	if (!event&&key>=LEFT&&key<=DOWN)
	{
		dir=key-LEFT;
		beginPaint();
		clearDevice();
		setPenWidth(100);
		/*ux=x+delta*dx[dir];
		uy=y+delta*dy[dir];*/
		line(x,y,x,y);
		x=x+delta*dx[dir];
		y=y-delta*dy[dir];
		setPenWidth(1);
		endPaint();
	}
}

//
//int Main()
//{
//	initWindow("Move Tank",DEFAULT,DEFAULT,800,600);
//	beginPaint();
//	setTextSize(100);
//	paintText(200,300,"This is a test of moving a tank");
//	endPaint();
//	registerMouseEvent(draw1);
//	registerKeyboardEvent(movePoint);
//
//	return 0;
//}