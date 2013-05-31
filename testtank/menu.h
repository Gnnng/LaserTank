#ifndef MENU_H
#define MENU_H
#define MAXBUTTON 10
typedef enum{
	PLAY
} eventType;

typedef struct buttonType {
	int x,y;//central x and central y
	int height;
	int width;
	char str[80];
	int jump;
	int id;
	int up;
	ACL_Image *upimg,*downimg;
	eventType event;
} buttonClass;
extern ACL_Image *menuback;
extern buttonClass allButton[MAXBUTTON];
extern int buttonCount;

void addButton(int x,int y,int width,int height,char* name,int jump,eventType event,char* up,char* down);
void printMenu();
void printButton(int id);
void initMenu();
int findButton(int x,int y);
void printBackground();

#endif