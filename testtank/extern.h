#ifndef EXTERN_H
#define EXTERN_H
extern nodeClass map[WINX+1][WINY+1];
extern tankClass allTank[MAXTANK];
extern int tankCount;
extern laserClass allLaser[MAXLASER];
extern int laserCount;
extern int counter;
extern int dx[];
extern int dy[];
extern int mousex,mousey;

#endif