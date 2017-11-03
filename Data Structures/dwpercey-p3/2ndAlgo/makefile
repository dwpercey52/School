make : GraphBuild.o Tours.o Test.o 
	gcc -o Tour GraphBuild.o Tours.o Test.o -lm
GraphBuild.o :  GraphBuild.c GraphBuild.h 
	gcc -c -Wall GraphBuild.c 
Tours.o : Tours.c Tours.h 
	gcc -c -Wall Tours.c
Test.o : Test.c
	gcc -c -Wall Test.c
clean : 
	rm Tour GraphBuild.o Tours.o Test.o

	