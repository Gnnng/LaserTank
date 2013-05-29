#include "acllib.h"
#include "menu.h"
#include <string.h>
#include "map.h"

buttonClass allButton[MAXBUTTON];
int buttonCount;

void printMenu(int tid){
	int i;

	for(i=0;i<buttonCount;i++){
		printButton(i);
	}
}

void addButton(int x,int y,int width,int height,char* name,int jump){
	buttonClass a;
	a.x=x;
	a.y=y;
	a.width=width;
	a.height=height;
	strncpy(name,a.str,80);
	allButton[buttonCount++]=a;
}

void printButton(int id){
	buttonClass a;
	a=allButton[id];
	int len;
	len=strlen(a.str);
	beginPaint();
	rectangle(a.x-a.width/2,a.y-a.height/2,a.x+a.width/2,a.y+a.height/2);
	paintText(a.x-a.width/2+10,a.y-a.height/2+10,a.str);
	endPaint();
}

void initMenu(){
	addButton(WINX/2,WINY/2,100,30,"Play",0);
}