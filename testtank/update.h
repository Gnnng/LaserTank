void timeupdate()
{
	updateTube(1,mousex,mousey);
	updateLaser();
}


void updateMouse(int x,int y,int button,int event){
	int x0,y0;
	char s[100];
	double len;
	mousex=x;
	mousey=y;
	if (event==BUTTON_DOWN && button==LEFT_BUTTON)
	{
		x0=allTank[1].x;
		y0=allTank[1].y;
		beginPaint();
		sprintf(s,"x=%d,y=%d",x0,y0);
		paintText(700,300,s);
		endPaint();
		len=sqrt((double)((x-x0)*(x-x0)+(y-y0)*(y-y0)));
		initLaser(x0,y0,(double)(x-x0)/len,(double)(y-y0)/len,LASERSPEED);
		insertLaser(allLaser[laserCount]);
	}

}