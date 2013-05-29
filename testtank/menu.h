#ifndef MENU_H
#define MENU_H
#define MAXBUTTON 10
typedef struct buttonType {
	int x,y;//central x and central y
	int height;
	int width;
	char str[80];
	int jump;
	int id;
} buttonClass;

extern buttonClass allButton[MAXBUTTON];
extern int buttonCount;

void addButton(int x,int y,int width,int height,char* name,int jump);
void printMenu(int tid);
void printButton(int tid);
void initMenu();

#endif