#include "head.h"
#include "extern.h"
void updateLaser()
{
	int i,j;
	laserClass laser2;
	for (i=1;i<=laserCount;i++)
	{
		if (allLaser[i].t>0)		
		{
			laser2=allLaser[i];
			laser2.x0=laser2.fx0+(LASERT-laser2.t)*laser2.xt;
			laser2.y0=laser2.fy0+(LASERT-laser2.t)*laser2.yt;
			changeLaser(allLaser[i],laser2);
			allLaser[i].t--;
		}
		else
		{
			if (allLaser[i].t<=0 && allLaser[i].t>=-1)
			{
				cancelLaser(allLaser[i]);
				allLaser[i].t--;
			}
		}
	}		
}
void initLaser(int x0,int y0,double xt,double yt,int speed)
{
	laserClass	*laser;
	laserCount++;
	laser=&allLaser[laserCount];
	laser->fx0=x0;
	laser->fy0=y0;
	laser->x0=x0;
	laser->y0=y0;
	xt=speed*xt;
	yt=speed*yt;
	laser->xt=xt;
	//laser->xt=0.5;
	laser->yt=yt;
	//laser->yt=0;
	laser->t=LASERT;
	laser->len=LASERLEN/sqrt(xt*xt+yt*yt);
	laser->id=laserCount;
}

void insertLaser(laserClass	laser)
{
	int i,p,q;
	int flag;
	int x,y,fx,fy,tx,ty,x1,x2,y1,y2;
	fx=laser.x0;fy=laser.y0;
	for (i=0;i<=laser.len;i++)
	{
		tx=laser.x0+i*laser.xt;
		ty=laser.y0+i*laser.yt;
		flag=0;
		for (x=fx;x!=tx;)
		{
			for(y=fy;y!=ty;)
			{
				//if(x>=WINX || y>=WINY || x<=0 || y<=0 || map[x][y].obj==WALL)
				if (map[x][y].obj==WALL)
				{
					char s[100];
					//beginPaint();
					laser.t=0;
					flag=1;
					break;
				}
				if (map[x][y].obj!=TANK)
				{
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
	int i,j,k;
	int x,y,tx,fx,ty,fy;
	int flag;
	fx=laser.x0;fy=laser.y0;
	for (i=0;i<=laser.len;i++)
	{
		tx=laser.x0+i*laser.xt;
		ty=laser.y0+i*laser.yt;
		flag=0;
		for (x=fx;x!=tx;)
		{
			for(y=fy;y!=ty;)
			{
				if (map[x][y].obj==WALL)
				{
					flag=1;
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
void changeLaser(laserClass laser1,laserClass laser2)
{
	cancelLaser(laser1);
	insertLaser(laser2);
}