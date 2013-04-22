#ifndef WATCH_H
#define WATCH_H

typedef struct _watchClass{
	char info[100];
	int row;
} watchClass;

int watchFind(const char *);
void watchPrint(int,int);
void watch(const char *,int);

#endif