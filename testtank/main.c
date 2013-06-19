#include "acllib.h"
#include "map.h"
#include "update.h"
#include "ai.h"
#include "menu.h"

int Main()
{
	initWindow("LaserTank",DEFAULT,DEFAULT,WINX,WINY);
	//load the sound
	loadSound("sound\\blow.mp3",&hit);
	loadSound("sound\\firelaser.wav",&laserFire);
	loadSound("sound\\reflect1.wav",&laserReflect);
	loadSound("sound\\tankmove2.wav",&tankMove);
	//load the image
	loadImage("img\\map.jpg",&floorImg);
	loadImage("img\\tank20.gif",&imgTank0);
	loadImage("img\\tank21.gif",&imgTank1);
	loadImage("img\\tank22.gif",&imgTank2);
	loadImage("img\\tank23.gif",&imgTank3);
	loadImage("img\\aitank0.gif",&imgAITank0);
	loadImage("img\\aitank1.gif",&imgAITank1);
	loadImage("img\\aitank2.gif",&imgAITank2);
	loadImage("img\\aitank3.gif",&imgAITank3);
	loadImage("img\\aitankv.gif",&imgAITankV);
	loadImage("img\\aitankh.gif",&imgAITankH);
	initMenu();
	supermode=0;
	registerTimerEvent(updateTimer);
	//registerKeyboardEvent(updateKey);
	registerMouseEvent(updateMouse);
	startTimer(1,10);
	//registerTimerEvent(aiControl);
	//begin game
	//welcome();
	return 0;
}

