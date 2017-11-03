make : OfflineSet.o OnlineSet.o Test.o Builds.o
	gcc -o Pack OfflineSet.o OnlineSet.o Test.o Builds.o -lm
Builds.o :	Builds.c Builds.h OnlineSet.h OfflineSet.h
	gcc -c -Wall Builds.c
OfflineSet.o :  OfflineSet.c OfflineSet.h Builds.h
	gcc -c -Wall OfflineSet.c 
OnlineSet.o : OnlineSet.c OnlineSet.h Builds.h
	gcc -c -Wall OnlineSet.c
Test.o : Test.c
	gcc -c -Wall Test.c
clean : 
	rm Pack Builds.o OfflineSet.o OnlineSet.o Test.o

	