
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
			if (allLaser[i].t==0)
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
	int i,j,k;
	int x,y;
	for (i=0;i<=laser.len;i++)
	{
		x=laser.x0+i*laser.xt;
		y=laser.y0+i*laser.yt;
		if (0/*碰撞等情况*/)
		{
		}
		else
		{
			if(map[x][y].obj==WALL || x>=WINX || y>=WINY || x<=0 || y<=0)
			{
				laser.t=0;
				break;
			}
			if (map[x][y].obj!=TANK)
			{
				map[x][y].obj=LASER;
				map[x][y].id=laser.id;
			}				
		}
	}
	allLaser[laser.id]=laser;
}
void cancelLaser(laserClass laser)
{
	int i,j,k;
	int x,y;
	for (i=0;i<=laser.len;i++)
	{
		x=laser.x0+i*laser.xt;
		y=laser.y0+i*laser.yt;
		if (0/*碰撞等情况*/)
		{
		}
		else
		{
			if (map[x][y].obj==LASER)
			{
				map[x][y].obj=NOPE;
			}
		}
	}
}
void changeLaser(laserClass laser1,laserClass laser2)
{
	cancelLaser(laser1);
	insertLaser(laser2);
}