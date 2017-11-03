make : FileCheck.o FileRun.o
	gcc -o File FileCheck.o FileRun.o -lm
FileCheck.o :  FileCheck.c FileCheck.h 
	gcc -c -Wall FileCheck.c 
FileRun.o : FileRun.c 
	gcc -c -Wall FileRun.c
clean : 
	rm File FileCheck.o FileRun.o

	