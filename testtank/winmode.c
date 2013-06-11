#include "winmode.h"
#include "acllib.h"
#include "watch.h"
#include "stdlib.h"
#include "update.h"
#include "map.h"
int over;

int wintime()
{
	ACL_Image *winpic=(ACL_Image*)malloc(sizeof(ACL_Image));
	over=1;
	stage=2;
	cancelTimer(0);
	beginPaint();
	clearDevice();
	loadImage("img\\winpic.jpg",winpic);
	putImageScale(winpic,0,0,WINX,WINY);
	endPaint();
}