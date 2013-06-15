#include "acllib.h"
#include "laser.h"
#include "tank.h"
#include "winmode.h"
#include <math.h>
#include "map.h"
#include "watch.h"
laserClass allLaser[MAXLASER];
int laserCount;

void updateLaser()
{
	int i;
	laserClass laser2;
	int la=laserCount;
	for (i=1;i<=la;i++)
	{
		if (allLaser[i].life>0)		
		{
			laser2=allLaser[i];
			laser2.x0=(int)(laser2.ox+(laser2.span-laser2.life)*laser2.xt);
			laser2.y0=(int)(laser2.oy+(laser2.span-laser2.life)*laser2.yt);
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

void initLaser(int x0,int y0,double xt,double yt,int speed,int span,int tankid)
{
	laserClass	*laser;
	double sq;
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
	laser->life=span;
	laser->span=span;
	sq=xt*xt+yt*yt;
	sq=sqrt(sq);
	laser->len=(int)(50/sq);
	laser->id=laserCount;
	laser->pflag=0;
	laser->tankID=tankid;
}

void insertLaser(laserClass	laser)
{
	int i;
	double nxt,nyt;
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
				if(x>WINX || y>WINY || x<0 || y<0)
				if (map[x][y].obj==WALL)	
				{
					//beginPaint();
  				    laser.life=0;
					flag=1;
					break;
				}
				if (map[x][y].obj==WALL || ( laser.tankID>=1 && map[x][y].obj==TANKBODY && map[x][y].id>=1))
				{
					flag=1;
					cancelLaser(laser);
					laser.span=laser.life;
					laser.x0=x;laser.y0=y;
					laser.ox=x;laser.oy=y;
					if (map[x][y].obj==WALL && (map[x+1][y].obj==WALL || map[x-1][y].obj==WALL) || map[x][y].obj==TANKBODY && (map[x+1][y].obj==TANKBODY && map[x-1][y].obj==TANKBODY))
					{
						laser.yt=-laser.yt;
					}
					else
					{
						nyt=laser.yt;
					}
					if (map[x][y].obj==WALL && (map[x][y+1].obj==WALL || map[x][y-1].obj==WALL) || map[x][y].obj==TANKBODY && (map[x][y+1].obj==TANKBODY && map[x-1][y-1].obj==TANKBODY))
					{
						laser.xt=-laser.xt;
					}
					else
					{
						nxt=-laser.xt;
					}
					/*laserCount++;
					allLaser[laserCount]=laser;
					allLaser[laserCount].xt=nxt;
					allLaser[laserCount].yt=nyt;
					allLaser[laserCount].x0=x;
					allLaser[laserCount].ox=x;
					allLaser[laserCount].y0=y;
					allLaser[laserCount].oy=y;*/
				    //initLaser(x,y,nxt/LASERSPEED,nyt/LASERSPEED,LASERSPEED,laser.life);
					//insertLaser(allLaser[laserCount]);
					//laser.life=0;
					break;
				}
				if (map[x][y].obj!=TANK)
				{
					if (map[x][y].obj==TANKBODY)
					{
						watch("winning laser from",laser.tankID);
						//wintime();
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