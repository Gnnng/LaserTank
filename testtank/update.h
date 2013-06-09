#ifndef UPDATE_H
#define UPDATE_H

typedef enum {
	LEFT=37,
	UP,
	RIGHT,
	DOWN
};

extern int stage;
extern int mousex,mousey;
/*============= Timer Controller ====================*/
void updateTimer(int tid);
void mapTimer(int tid);
void menuTimer(int tid);
void keyTimer(int tid);

/*============= Mouse Controller ====================*/
void controlTube(int i,int x,int y);
void updateMouse(int x,int y,int button,int event);
void LeftClickwhenFighting();
void LeftClickinmenu();
/*============= Keyboard Controller ==================*/
void updateKey(int key,int event);

#endif