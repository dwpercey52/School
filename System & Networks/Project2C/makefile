all: sender receiver network

bbserver: bbserver.c
	gcc -o  bbserver -Wall -g bbserver.c

sender: rdtSender.c
	gcc -o sender -Wall -g rdtSender.c
	
receiver: rdtReceiver.c
	gcc -o receiver -Wall -g rdtReceiver.c
	
network: rdtNetwork.c
	gcc -o network -Wall -g rdtNetwork.c

clean : 
	rm sender receiver network

	