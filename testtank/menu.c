#include "acllib.h"
#include "menu.h"
#include <string.h>
#include "map.h"

buttonClass allButton[MAXBUTTON];
ACL_Image *menuback;
int buttonCount;

int findButton(int x,int y)
{
	int p,flag;
	buttonClass a;
	flag=0;
	for (p=0;p<buttonCount;p++)
	{
		a=allButton[p];
		if (x>=a.x-a.width/2 && x<a.x+a.width/2 && y>=a.y-a.height/2 && a.y+a.height/2)
		{
			flag=1;
			break;
		}
	}
	if (flag==0)
	{
		return -1;
	}
	else
	{
		return p;
	}
}

void printBackground()
{
	beginPaint();
	//putImageScale(menuback,0,0,WINX,WINY); 
	putImage(menuback,0,0);
	endPaint();
}

void printMenu(){
	int i;
	printBackground();
	for(i=0;i<buttonCount;i++){
		printButton(i);
	}
}

void addButton(int x,int y,int width,int height,char* name,int jump,eventType event,char* up,char* down)
{
	buttonClass a;
	a.x=x;
	a.y=y;
	a.width=width;
	a.height=height;
	a.event=event;
	a.up=1;
	a.upimg=(ACL_Image*)malloc(sizeof(ACL_Image));
	a.downimg=(ACL_Image*)malloc(sizeof(ACL_Image));
	loadImage(up,a.upimg);
	loadImage(down,a.downimg);
	strncpy(a.str,name,80);
	allButton[buttonCount++]=a;
}

void printButton(int id){
	buttonClass a;
	int len;
	a=allButton[id];
	len=strlen(a.str);
	beginPaint();
	//rectangle(a.x-a.width/2,a.y-a.height/2,a.x+a.width/2,a.y+a.height/2);
	//paintText(a.x-strlen(a.str)*3,a.y-a.height/2+10,a.str);
	if (a.up==1)
	{
		//putImageScale(a.upimg,a.x-a.width/2,a.y-a.height/2,a.width,a.height);
		putImage(a.upimg,a.x-a.width/2,a.y-a.height/2);
	}
	else
	{
		//putImageScale(a.downimg,a.x-a.width/2,a.y-a.height/2,a.width,a.height);
		putImage(a.downimg,a.x-a.width/2,a.y-a.height/2);
	}
	endPaint();
}

void initMenu(){
	menuback=(ACL_Image*)malloc(sizeof(ACL_Image));
	loadImage("img\\menuback_f.jpg",menuback);
	addButton(WINX/2,WINY/2+200,111,38,"START!!!!",0,PLAY,"img\\buttonup1.jpg","img\\buttondown1.jpg");
}