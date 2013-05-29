#include "acllib.h"
#include "map.h"
#include "update.h"
#include "ai.h"

int Main()
{
	initWindow("LaserTank",DEFAULT,DEFAULT,WINX+200,WINY);
	//binding the input
	registerTimerEvent(updateTimer);
	registerKeyboardEvent(updateKey);
	registerMouseEvent(updateMouse);
	startTimer(1,10);
	//registerTimerEvent(aiControl);
	//begin game
	initMap();
	ai();
	//welcome();
	return 0;
}

