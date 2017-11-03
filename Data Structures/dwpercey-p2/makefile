make : MathFunc.o Simulation.o RunSim.o
	gcc -o Sim MathFunc.o Simulation.o RunSim.o -lm
MathFunc.o :  MathFunc.c MathFunc.h Simulation.h
	gcc -c -Wall MathFunc.c 
Simulation.o : Simulation.c Simulation.h MathFunc.h 
	gcc -c -Wall Simulation.c
RunSim.o : RunSim.c
	gcc -c -Wall RunSim.c
clean : 
	rm Sim MathFunc.o Simulation.o RunSim.o

	