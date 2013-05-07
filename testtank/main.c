#include "acllib.h"
#include "map.h"
#include "update.h"

int Main()
{
	initWindow("LaserTank",DEFAULT,DEFAULT,WINX,WINY);
	//binding the input
	registerTimerEvent(printMap);
	startTimer(0,10);
	registerKeyboardEvent(updateKey);
	registerMouseEvent(updateMouse);
	//begin game
	initMap();
	//welcome();
	return 0;
}
