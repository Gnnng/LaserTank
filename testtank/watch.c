#include "head.h"
#include "extern.h"
#include "watch.h"
#include "string.h"

watchClass watchList[100];
int watchCount=0;
const int watchConsleX=100;
const int watchConsleY=10;
const int lineHeigtht=10;

int watchFind(const char *info)
{
	int i;
	if (watchCount==0) return -1;
	for(i=0;i<watchCount;i++)
		if (strcmp(watchList[i].info,info)==0) return i;
	return -1;
}

void watch(const char *info,int x)
{
	int index;
	index=watchFind(info);
	if (watchCount==0) memset(watchList,0,sizeof(watchList));
	if (index==-1)
	{
		strcpy(watchList[watchCount].info,info);
		watchList[watchCount].row=watchCount*lineHeigtht;
		index=watchCount++;
	}
	watchPrint(index,x);
}

void watchPrint(int index,int x)
{
	char pstr[100],fstr[100];

	memset(pstr,0,sizeof(pstr));
	memset(fstr,0,sizeof(fstr));

	strcpy(pstr,watchList[index].info);
	sprintf(fstr," %d\0",x);
	strcat(pstr,fstr);
	beginPaint();
	setTextSize(10);
	paintText(watchConsleX,watchConsleY+watchList[index].row,pstr);
	endPaint();
}