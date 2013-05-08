#include "acllib.h"
#include "watch.h"
#include "laser.h"
#include "tank.h"
#include <math.h>
#include "update.h"
#include "map.h"

int mousex,mousey;

void updateWithMap()
{
	controlTube(1,mousex,mousey);
	updateLaser();
}

void updateMouse(int x,int y,int button,int event){
	int x0,y0;
	double len;
	mousex=x;
	mousey=y;
	watch("Mouse x",x);
	watch("Mouse y",y);
	if (event==BUTTON_DOWN && button==LEFT_BUTTON)
	{
		x0=allTank[1].x;
		y0=allTank[1].y;
		/*beginPaint();
		sprintf(s,"x=%d,y=%d",x0,y0);
		paintText(700,300,s);
		endPaint();*/
		len=sqrt((double)((x-x0)*(x-x0)+(y-y0)*(y-y0)));
		initLaser(x0,y0,(double)(x-x0)/len,(double)(y-y0)/len,LASERSPEED);
		insertLaser(allLaser[laserCount]);
	}
	if (event==BUTTON_DOWN && button==RIGHT_BUTTON)
	{
		watch("laser x ->",allLaser[map[x][y].id].x0);
		watch("laser y ->",allLaser[map[x][y].id].y0);
		/*beginPaint();
		sprintf(s,"x0=%d,y0=%d",allLaser[map[x][y].id].x0,allLaser[map[x][y].id].y0);
		paintText(500,300,s);
		endPaint();*/
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
		tank2.x+=tank2.speed*dx[key-LEFT];
		tank2.y+=tank2.speed*dy[key-LEFT];
		watch("tank x ->",tank2.x);
		watch("tank y ->",tank2.y);
		tank2.action=1;
		break;
	case KEY_UP:
		tank2.action=0;
		break;
	}
	changeTank(tank1,tank2);
}
