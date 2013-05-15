#include "ai.h"
#include "tank.h"
#include "map.h"
#include "Laser.h"
#include "watch.h"
int ai()
{
	int i;
	tankClass *aitank;
	initTank();
	i=tankCount;
	aitank=&allTank[i];
	watch("i=",i);
	aitank->x=100;
	aitank->y=100;
	insertTank(*aitank);
}
	