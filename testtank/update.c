#include "head.h"
#include "extern.h"
#include "watch.h"

void timeupdate()
{
	updateTube(1,mousex,mousey);
	updateLaser();
}


void updateMouse(int x,int y,int button,int event){
	int x0,y0;
	char s[100];
	double len;
	mousex=x;
	mousey=y;
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