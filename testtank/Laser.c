#include "acllib.h"
#include "laser.h"
#include "tank.h"
#include "winmode.h"
#include <math.h>
#include "map.h"

laserClass allLaser[MAXLASER];
int laserCount;

void updateLaser()
{
	int i;
	laserClass laser2;
	for (i=1;i<=laserCount;i++)
	{
		if (allLaser[i].life>0)		
		{
			laser2=allLaser[i];
			laser2.x0=(int)(laser2.ox+(LASERLIFE-laser2.life)*laser2.xt);
			laser2.y0=(int)(laser2.oy+(LASERLIFE-laser2.life)*laser2.yt);
			changeLaser(allLaser[i],laser2);
			allLaser[i].life--;
		}
		else
		{
			if (allLaser[i].life<=0 && allLaser[i].life>=-1)
			{
				cancelLaser(allLaser[i]);
				allLaser[i].life--;
			}
		}
	}		
}

void initLaser(int x0,int y0,double xt,double yt,int speed)
{
	laserClass	*laser;
	laserCount++;
	laser=&allLaser[laserCount];
	laser->ox=x0;
	laser->oy=y0;
	laser->x0=x0;
	laser->y0=y0;
	xt=speed*xt;
	yt=speed*yt;
	laser->xt=xt;
	//laser->xt=0.5;
	laser->yt=yt;
	//laser->yt=0;
	laser->life=LASERLIFE;
	laser->len=(int)(LASERLEN/sqrt(xt*xt+yt*yt));
	laser->id=laserCount;
	laser->pflag=0;
}

void insertLaser(laserClass	laser)
{
	int i;
	int flag;
	int tankcrash=0;
	int x,y,fx,fy,tx,ty;
	fx=laser.x0;fy=laser.y0;
	laser.pflag=0;
	for (i=0;i<=laser.len;i++)
	{
		tx=laser.x0+i*laser.xt;//bug
		ty=laser.y0+i*laser.yt;//bug
		if (tx>fx) tx++; else tx--;
		if (ty>fy) ty++; else ty--;
		flag=0;
		for (x=fx;x!=tx;)
		{
			for(y=fy;y!=ty;)
			{
				if(x>WINX || y>WINY || x<0 || y<0 || map[x][y].obj==WALL)
				//if (map[x][y].obj==WALL)	
				{
					//beginPaint();
					laser.life=0;
					flag=1;
					break;
				}
				if (map[x][y].obj!=TANK)
				{
					if (map[x][y].obj==TANKBODY)
					{
						wintime();
						flag=1;
						laser.life=0;
						break;
					}
					map[x][y].obj=LASER;
					map[x][y].id=laser.id;
				}
				if (ty>fy) y++; else y--;
			}
			if (flag)
			{
				break;
			}
			if (tx>fx) x++; else x--;
		}
		if (flag)
		{
			break;
		}
		fx=tx;
		fy=ty;
	}
	allLaser[laser.id]=laser;
}
void cancelLaser(laserClass laser)
{
	int i;
	int x,y,tx,fx,ty,fy;
	int flag;
	fx=laser.x0;fy=laser.y0;
	for (i=0;i<=laser.len;i++)
	{
		tx=laser.x0+i*laser.xt;//bug
		ty=laser.y0+i*laser.yt;//bug
		if (tx>fx) tx++; else tx--;
		if (ty>fy) ty++; else ty--;
		flag=0;
		for (x=fx;x!=tx;)
		{
			for(y=fy;y!=ty;)
			{
				if(x>WINX || y>WINY || x<0 || y<0 || map[x][y].obj==WALL)//copy from insertLaser
				//if (map[x][y].obj==WALL)
				{
					flag=1;
					break;
				}
				if (map[x][y].obj==LASER)
				{
					map[x][y].obj=NOPE;
				}	
				if (ty>fy) y++; else y--;
			}
			if (tx>fx) x++; else x--;
		}
		if (flag)
		{
			break; 
		}
		fx=tx;
		fy=ty;
	}
}
//by Gnnng 
//void insertLaser(laserClass laser){
//	int x,y,tx,ty;
//	x=laser.x0;
//	tx=x+laser.len*laser.xt+1;
//	for(;x!=tx;x<tx?x++:x--){
//		y=(x-tx)*laser.yt/laser.xt+ty;
//		if(x>WINX || y>WINY || x<0 || y<0 || map[x][y].obj==WALL)
//			//if (map[x][y].obj==WALL)
//		{
//			//beginPaint();
//			laser.life=0;
//			break;
//		}
//		if (map[x][y].obj!=TANK)
//		{
//			map[x][y].obj=LASER;
//			map[x][y].id=laser.id;
//		}	
//	}
//	allLaser[laser.id]=laser;
//}
//by Gnnng
//void cancelLaser(laserClass laser){
//	int x,y,tx,ty;
//	x=laser.x0;
//	tx=x+laser.len*laser.xt+1;
//	for(;x!=tx;x<tx?x++:x--){
//		y=(x-tx)*laser.yt/laser.xt+ty;
//		if(x>WINX || y>WINY || x<0 || y<0 || map[x][y].obj==WALL)//copy from insertLaser
//			//if (map[x][y].obj==WALL)
//		{
//			break;
//		}
//		if (map[x][y].obj==LASER)
//		{
//			map[x][y].obj=NOPE;
//		}	
//	}
//}
void changeLaser(laserClass laser1,laserClass laser2)
{
	cancelLaser(laser1);
	insertLaser(laser2);
}