make : TableCompare.o  Test.o LCS.o
	gcc -o LCS TableCompare.o  Test.o LCS.o -lm
LCS.o :	LCS.c LCS.h  
	gcc -c -Wall LCS.c
TableCompare.o :  TableCompare.c TableCompare.h 
	gcc -c -Wall TableCompare.c 
Test.o : Test.c
	gcc -c -Wall Test.c
clean : 
	rm LCS LCS.o TableCompare.o  Test.o

	