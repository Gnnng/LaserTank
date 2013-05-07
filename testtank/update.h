#ifndef UPDATE_H
#define UPDATE_H

typedef enum {
	LEFT=37,
	UP,
	RIGHT,
	DOWN
};

extern int mousex,mousey;

void updateWithMap();
void controlTube(int i,int x,int y);
void updateMouse(int x,int y,int button,int event);
void updateKey(int key,int event);

#endif