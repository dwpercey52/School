make : mtCollatz.o
	gcc -o mtCollatz mtCollatz.o -lm -pthread
mtCollatz.o :  mtCollatz.c 
	gcc -c -Wall mtCollatz.c 
clean : 
	rm *o mtCollatz

	