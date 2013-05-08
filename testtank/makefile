object=acllib.o laser.o main.o map.o tank.o update.o watch.o
VPATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include
lasertank.exe: $(object)
	gcc -o lasertank.exe $(object)
	
acllib.o: acllib.c acllib.h
	gcc -c acllib.c
drawwithmouse.o: drawwithmouse.c acllib.h
laser.o: laser.c acllib.h laser.h tank.h map.h
main.o: main.c acllib.h map.h update.h
main1.o: main1.c
map.o: map.c acllib.h tank.h laser.h watch.h update.h map.h
tank.o: tank.c tank.h laser.h acllib.h watch.h update.h map.h
update.o: update.c acllib.h watch.h laser.h tank.h update.h map.h
watch.o: watch.c watch.h acllib.h
