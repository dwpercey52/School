all: bbserver bbclient

bbserver: bbserver.c
	gcc -o  bbserver -Wall -g bbserver.c

bbclient: bbclient.c
	gcc -pthread -o bbclient -Wall -g bbclient.c bbfile.c

clean : 
	rm bbclient bbserver

	