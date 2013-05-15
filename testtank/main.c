#include "acllib.h"
#include "map.h"
#include "update.h"
#include "ai.h"
int Main()
{
	initWindow("LASERLIFEank",DEFAULT,DEFAULT,WINX+200,WINY);
	//binding the input
	registerTimerEvent(printMap);
	startTimer(0,10);
	registerKeyboardEvent(updateKey);
	registerMouseEvent(updateMouse);
	//begin game
	initMap();
	ai();
	//welcome();
	return 0;
}
