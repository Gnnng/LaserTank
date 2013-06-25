#include "acllib.h"
#include "tank.h"
#include "laser.h"
#include "watch.h"
#include "update.h"
#include "map.h"
#include <math.h>
#include <string.h>
#include "winmode.h"
#include "ai.h"
#include <stdio.h>

nodeClass map[WINX+1][WINY+1];
int counter=0;
int destroyCounter=0;

int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};

int wallx[]={600,600,750,750};
int wally[]={100,500,500,100};
int level;

ACL_Sound laserFire,laserReflect,tankMove,hit;
ACL_Image floorImg,imgTankV,imgTankH,imgAITankH,imgAITankV;
ACL_Image imgTank0;
ACL_Image imgTank1;
ACL_Image imgTank2;
ACL_Image imgTank3;
ACL_Image imgAITank0;
ACL_Image imgAITank1;
ACL_Image imgAITank2;
ACL_Image imgAITank3;
void printTank(nodeClass *node)
{
	int leftx,lefty,rightx,righty;
	ACL_Image *mainTank,*AITank;
	tankClass *tank=&allTank[node->id];
	if (tank->tubeLock==1)
	{
		if (tank->dy==1) tank->angle=Pi/2;
		if (tank->dy==-1) tank->angle=3*Pi/2;
		if (tank->dx==1) tank->angle=0;
		if (tank->dx==-1) tank->angle=Pi;
	}
	leftx=tank->x-tank->width/2;
	lefty=tank->y-tank->width/2;
	rightx=tank->x+tank->width/2;
	righty=tank->y+tank->width/2;
	beginPaint();
	setBrushColor(EMPTY);
	switch(tank->dy) {
	case -1:
		mainTank=&imgTank0;
		AITank=&imgAITank0;
		break;
	case 1:
		mainTank=&imgTank2;
		AITank=&imgAITank2;
		break;
	}
	switch(tank->dx) {
	case -1:
		mainTank=&imgTank3;
		AITank=&imgAITank3;
		break;
	case 1:
		mainTank=&imgTank1;
		AITank=&imgAITank1;
		break;
	}
	switch(tank->id) {
	case 1:
		putImageTransparent(mainTank,leftx,lefty,tank->width,tank->width,WHITE);
		break;
	default:
		putImageTransparent(AITank,leftx,lefty,tank->width,tank->width,WHITE);
		break;
	}
	setPenWidth(2);
	line(tank->x,tank->y,tank->x+(int)(tank->len*cos(tank->angle)),tank->y+(int)(tank->len*sin(tank->angle)));
	setPenWidth(1);
	endPaint();
}

void printLaser(int i)
{
	if (allLaser[i].pflag) return;
	allLaser[i].pflag=1;
	beginPaint();
	switch(allLaser[i].tankID) {
	case 1:
		setPenColor(WHITE);
		break;
	default:
		setPenColor(RGB(200,0,0));
	}
	setPenWidth(2);
	line(allLaser[i].x0,allLaser[i].y0,allLaser[i].x0+allLaser[i].len*allLaser[i].xt,allLaser[i].y0+allLaser[i].len*allLaser[i].yt);
	setPenColor(BLACK);
	setPenWidth(1);
	endPaint();
}

void printCounter() {
	char s[255];
	beginPaint();
	setTextBkColor(EMPTY);
	setTextFont("Î¢ÈíÑÅºÚ");
	setTextSize(30);
	setTextColor(WHITE);
	sprintf(s,"Game Time %6d.%02d s",counter/100,counter%100);
	paintText(20,20,s);
	endPaint();
}

void printKill() {
	char s[255];
	beginPaint();
	setTextBkColor(EMPTY);
	setTextFont("Î¢ÈíÑÅºÚ");
	setTextSize(30);
	setTextColor(WHITE);
	sprintf(s,"You have killed %d enem%s",destroyCounter,destroyCounter>1?"ies":"y");
	paintText(500,20,s);
	endPaint();
}

void printLevel() {
	char s[255];
	beginPaint();
	setTextBkColor(EMPTY);
	setTextFont("Î¢ÈíÑÅºÚ");
	setTextSize(30);
	setTextColor(WHITE);
	sprintf(s,"Level %2d",level);
	paintText(350,20,s);
	endPaint();
}
void printMap(int tid)
{
	int i,j;
	static int cc;

	if (over==1) return;
	beginPaint(); 
#ifdef SHADOW
	cc++;
	if (cc==15)
	{
#endif
		//clearDevice();
		//setBrushColor(WHITE);
		//rectangle(0,0,WINX,WINY);
		putImage(&floorImg,0,0);
#ifdef SHADOW
		cc=0;
	}
#endif
	endPaint();
	printCounter();
	printKill();
	printLevel();
	//watch("Map Timer -->",counter);
	printWall();
	for(i=0;i<WINX;i++)
	{
		for(j=0;j<WINY;j++)
		{
			switch (map[i][j].obj)
			{
			case NOPE: break;
			case WALL: break;
			case TANK: printTank(&map[i][j]); break;
			case LASER: if (allLaser[map[i][j].id].life>0) printLaser(map[i][j].id); break;
			}
		}
	}
	for(i=1;i<=tankCount;i++){
		if (allTank[i].living) printCDBar(allTank[i]);
	}
	counter++;

	if (counter==MAXEXISTTIME*1000) 
	{
		cancelTimer(0);
	}
}

void setWall(int fx,int fy,int tx,int ty){
	if (fx==tx) {
		for(;fy!=ty;fy<ty?fy++:fy--)
			map[fx][fy].obj=WALL;
	}
	map[fx][ty].obj=WALL;
	map[tx][fy].obj=WALL;
	if (fy==ty) {
		for(;fx!=tx;fx<tx?fx++:fx--)
			map[fx][fy].obj=WALL;
	}
}

void setLongWall(int n,int* xset,int *yset){
	int i;
	for(i=0;i<n-1;i++)
		setWall(*(xset+i),*(yset+i),*(xset+i+1),*(yset+i+1));
}

void printWall(){
	int i,j;
	int ii,jj;
	int size=1;
	beginPaint();
	for(i=0;i<WINX;i++)
		for(j=0;j<WINY;j++)
			if (map[i][j].obj==WALL) 
				/*for(ii=i-size;ii<=i+size;ii++)
					for(jj=j-size;jj<=j+size;jj++)*/
			{
						putPixel(i,j,WHITE);
						//putPixel(i,j+1,GREEN);
						//putPixel(i+1,j,GREEN);
			}
	endPaint();
}

void initMap(int level)
{
	int i,j;
	//clear map
	memset(map,0,sizeof(map));
	if (level==1) counter=destroyCounter=0;
	tankCount=0;
	laserCount=0;
	//set WALL
	for (i=0;i<=WINX;i++)
	{
		map[i][1].obj=WALL;
		map[i][WINY-1].obj=WALL;
	}
	for (j=0;j<=WINY;j++)
	{
		map[1][j].obj=WALL;
		map[WINX-1][j].obj=WALL;
	}
	//set inside wall
	switch(level) {
	case 5:
		break;
	case 2:
		//setLongWall(4,wallx,wally);
		break;
	case 3:
		setWall(200,400,600,400);
		break;
	case 4:
		//setLongWall(4,wallx,wally);
		setWall(300,200,300,400);
		setWall(300,400,500,400);
		setWall(500,400,500,200);
		break;
	case 1:
		setWall(700,200,300,200);
		setWall(300,200,300,400);
		setWall(300,400,700,400);
		//setWall(500,400,500,200);
		break;
	default:
		break;
	}
	//set MAN
	initTank(tankCount++);
	insertTank(allTank[1]);
	allTank[1].tubeLock=0;
	//set AI
	initAI(level);
}