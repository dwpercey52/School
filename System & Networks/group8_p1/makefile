make : parse.o myshell.o
	gcc -o myshell parse.o myshell.o -lm
parse.o :  parse.c parse.h 
	gcc -c -Wall parse.c 
myshell.o : myshell.c 
	gcc -c -Wall myshell.c
clean : 
	rm *o myshell listOfFileInCWD.txt

	