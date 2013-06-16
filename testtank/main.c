#include "acllib.h"
#include "map.h"
#include "update.h"
#include "ai.h"
#include "menu.h"

int Main()
{
	initWindow("LaserTank",DEFAULT,DEFAULT,WINX+200,WINY);
	//binding the input
	loadSound("sound\\blow.mp3",&hit);
	loadSound("sound\\firelaser.wav",&laserFire);
	loadSound("sound\\reflect1.wav",&laserReflect);
	loadSound("sound\\tankmove2.wav",&tankMove);
	initMenu();
	registerTimerEvent(updateTimer);
	//registerKeyboardEvent(updateKey);
	registerMouseEvent(updateMouse);
	startTimer(1,10);
	//registerTimerEvent(aiControl);
	//begin game
	//welcome();
	return 0;
}

