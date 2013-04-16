#include"acllib.h"
#include<string.h>
#include<stdio.h>

typedef enum {
	LEFT=37,
	UP,
	RIGHT,
	DOWN
};

struct round{
	int x,y;
	int dx,dy;
	int action;
	int speed;
} big;

int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};

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
	int dir;
	if (key<LEFT||key>DOWN) return;
	if (event==KEY_DOWN){
		dir=key-LEFT;
		big.x+=big.speed*dx[dir];
		big.y+=big.speed*dy[dir];
		big.dx=dx[dir];
		big.dy=dy[dir];
		big.action=1;
	} 
	else big.action=0;
}

void printPoint(int x,int y)
{
	int leftx,lefty,rightx,righty;
	leftx=x-20;
	lefty=y-20;
	rightx=x+20;
	righty=y+20;
	beginPaint();
	setBrushColor(EMPTY);
	rectangle(leftx,lefty,rightx,righty);
	endPaint();
}
void paintBlock(int id)
{
	beginPaint();
	clearDevice();
	endPaint();
	if (big.action)
	{
		big.x+=big.speed*big.dx;
		big.y+=big.speed*big.dy;
		printPoint(big.x,big.y);
	} 
	else
	{
		printPoint(big.x,big.y);
	}
}

int Main()
{
	initWindow("Move Tank",DEFAULT,DEFAULT,800,600);
	beginPaint();
	//setTextSize(100);
	paintText(200,300,"This is a test of moving a tank");
	endPaint();
	big.x=getWidth()/2;
	big.y=getHeight()/2;
	registerTimerEvent(paintBlock);
	startTimer(0,100);
	//registerMouseEvent(draw1);
	registerKeyboardEvent(movePoint);

	return 0;
}
