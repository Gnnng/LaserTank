#include "acllib.h"
#include "watch.h"
#include "laser.h"
#include "tank.h"
#include <math.h>
#include "update.h"
#include "map.h"
#include "menu.h"
#include "winmode.h"
#include "ai.h"

#define MYKEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define MYKEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1) 

int mousex,mousey;
int stage;
int keyList[10]={87/*w*/,65/*a*/,83/*s*/,68/*d*/,UP,LEFT,DOWN,RIGHT};

void keyTimer(int tid){
	static int lastKey=0;
	short key;
	int i;
	int down,up;
	watch("lastkey",lastKey);
	down=up=0;
	//for(i=0;i<8;i++)
	//{
	//	if (MYKEYDOWN(keyList[i])) {
	//		updateKey(keyList[i],KEY_DOWN);
	//		lastKey=keyList[i];
	//		break;
	//	}
	//	if (MYKEYUP(keyList[i])&&keyList[i]==lastKey) {
	//		updateKey(keyList[i],KEY_UP);
	//		break;
	//	}

	//}

	for(i=0;i<8;i++)
	{
		if (lastKey==0) {
			if(MYKEYDOWN(keyList[i])) {
				lastKey=keyList[i];
				updateKey(lastKey,KEY_DOWN);
				break;
			}
		}
		else {
			if (lastKey==keyList[i]) {
				if (MYKEYDOWN(lastKey)) {
					lastKey=keyList[i];
					updateKey(lastKey,KEY_DOWN);
					break;
				}
				if (MYKEYUP(lastKey)) {
					lastKey=0;
					updateKey(keyList[i],KEY_UP);
					break;
				}
			}
			else {
				if (MYKEYDOWN(keyList[i])) {
					lastKey=keyList[i];
					updateKey(lastKey,KEY_DOWN);
					break;
				}
			}
		}
	}
}

void updateTimer(int tid){
	int i;
	static int cou=0;
	switch(tid){
	case 0:
		stage=0;
		keyTimer(tid);
		mapTimer(tid);
		break;
	case 1:
		stage=1;
		menuTimer(tid);
		break;
	case 2:
		cou++;
		stage=3;
		menuTimer(tid);
		if (cou==30)
		{
			cancelTimer(2);
			startTimer(0,10);
			initMap();
			cou=0;
			for(i=0;i<=buttonCount;i++)
			{
				allButton[i].up=1;
			}
		}
	}
}

void mapTimer(int tid){
	int i;
	//man control
	controlTube(1,mousex,mousey);
	//autoRun();//DON'T TOUCH
	updateLaser();
	//AI control
	for(i=2;i<=tankCount;i++)
		(*(allTank[i].ctrl))(i);
	//view 
	printMap(tid);
}

void menuTimer(int tid){
	printMenu();
}
void LeftClickinmenu()
{
	int i;
	i=findButton(mousex,mousey);
	if (i!=-1)
	{
		switch(allButton[i].event)
		{
			case PLAY:
				allButton[i].up=0;
				cancelTimer(1);
				startTimer(2,10);
				break;
		}
	}
}
void updateMouse(int x,int y,int button,int event)
{
	mousex=x;
	mousey=y;
	//watch("Mouse x",x);
	//watch("Mouse y",y);
	/*watch("Test the angle ",getAngle(400,300,x,y)*180/Pi);
	watch("Man tank angle ",allTank[1].angle*180/Pi);*/
	if (event==BUTTON_DOWN && button==LEFT_BUTTON)
	{
		if (stage==0)
		{
			LeftClickwhenFighting();
		}
		if (stage==1)
		{
			LeftClickinmenu();
		}
		if (stage==2)
		{
			startTimer(1,10);
			over=0;
		}
	}
	if (event==BUTTON_DOWN && button==RIGHT_BUTTON)
	{
		watch("laser x ->",allLaser[map[x][y].id].x0);
		watch("laser y ->",allLaser[map[x][y].id].y0);
	}
}  

void LeftClickwhenFighting()
{
	int x0,y0;
	double len;
	int x,y;
	x=mousex;
	y=mousey;
	x0=allTank[1].x;
	y0=allTank[1].y;
	len=sqrt((double)((x-x0)*(x-x0)+(y-y0)*(y-y0)));
	x0=x0+(x-x0)/len*allTank[1].len;
	y0=y0+(y-y0)/len*allTank[1].len;
	watch("New laser X0",x0);
	watch("New laser Y0",y0);
	if (len) {
		initLaser(x0,y0,(double)(x-x0)/len,(double)(y-y0)/len,LASERSPEED,LASERLIFE,1);
		insertLaser(allLaser[laserCount]);
	}
}

void updateKey(int key,int event)
{
	tankClass tank1,tank2;

	tank1=tank2=allTank[1];
	watch("Key ->",key);
	switch(key)
	{
	case 87:key=UP;break;
	case 65:key=LEFT;break;
	case 83:key=DOWN;break;
	case 68:key=RIGHT;break;
	}
	switch(event){
	case KEY_DOWN:
		//if(tank2.action==1) break;
		tank2.dx=dx[key-LEFT];
		tank2.dy=dy[key-LEFT];
		tank2.x+=tank2.speed*tank2.dx;
		tank2.y+=tank2.speed*tank2.dy;
		watch("tank x ->",tank2.x);
		watch("tank y ->",tank2.y);
		//tank2.action=1;
		break;
	case KEY_UP:
		//tank2.action=0;
		break;
	}
	changeTank(tank1,tank2);
}
