/***************************************************************/
/* Darrell Percey && Andrew Boven                              */
/* lizard.c                                                    */
/* Project 3 || System Network I 							   */
/*               											   */
/*															   */	
/*	The program executes multiple threads simulating lizards   */
/*	and cats. The lizards will try to cross the "driveway"     */
/*	and the cats will try to catch more than 4 lizards 		   */
/*	crossing at a time.										   */
/*															   */
/* To compile, you need all the files listed below             */
/*   lizard.c                                                  */
/*                                                             */
/* Be sure to use the -lpthread option for the compile command */
/*   gcc -g -Wall lizard.c -o lizard -lpthread                 */
/*                                                             */
/* Execute with the -d command-line option to enable debugging */
/* output.  For example,                                       */
/*   ./lizard -d                                               */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#ifdef __APPLE__
#include <mach/semaphore.h>
#include <mach/task.h>
#define sem_init(a,b,c)     semaphore_create(mach_task_self(), (semaphore_t *)a, SYNC_POLICY_FIFO, c)
#define sem_destroy(a)      semaphore_destroy(mach_task_self(), *((semaphore_t *)a))
#define sem_post(a)         semaphore_signal(*((semaphore_t *)a))
#define sem_wait(a)         semaphore_wait(*((semaphore_t *)a))
#define sem_t               semaphore_t
#else
#include <semaphore.h>
#endif

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */

/*
 * Function prototypes go here
 * You may need more functions, but I don't think so
 */
void * lizardThread( void * param );
void * catThread( void * param );


/*
 * Define "constant" values here
 */

/*
 * Make this 1 to check for lizards travelling in both directions
 * Leave it 0 to allow bidirectional travel
 */
#define UNIDIRECTIONAL       0

/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
#define WORLDEND             30

/*
 * Number of lizard threads to create
 */
#define NUM_LIZARDS          20

/*
 * Number of cat threads to create
 */
#define NUM_CATS             2

/*	
 * Maximum lizards crossing at once before alerting cats
 */
#define MAX_LIZARD_CROSSING  4

/*
 * Maximum seconds for a lizard to sleep
 */
#define MAX_LIZARD_SLEEP     3

/*
 * Maximum seconds for a cat to sleep
 */
#define MAX_CAT_SLEEP        3

/*
 * Maximum seconds for a lizard to eat
 */
#define MAX_LIZARD_EAT       5

/*
 * Number of seconds it takes to cross the driveway
 */
#define CROSS_SECONDS        2


/*
 * Declare global variables here
 */

/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
int numCrossingSago2MonkeyGrass;
int numCrossingMonkeyGrass2Sago;
int debug;
int running;
/**************************************************/
sem_t testLock;
sem_t lizLock;
sem_t semFull;





/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv)
{
  /*
   * Declare local variables
   */
	int i;
	int value[2];
	int temp[NUM_LIZARDS];
	int temp2[NUM_CATS];
	pthread_t lizardThreadList[NUM_LIZARDS];
	pthread_t catThreadList[NUM_CATS];

	value[0] = 0;
	value[1] = 1;


  /*
   * Check for the debugging flag (-d)
   */
  debug = 0;
  if (argc > 1)
    if (strncmp(argv[1], "-d", 2) == 0)
      debug = 1;

//dawdwa
  /*
   * Initialize variables
   */
  numCrossingSago2MonkeyGrass = 0;
  numCrossingMonkeyGrass2Sago = 0;
  running = 1;


  /*
   * Initialize random number generator
   */
  srandom( (unsigned int)time(NULL) );


  /*
   * Initialize locks and/or semaphores
   */

	sem_init(&semFull, value[0], value[0]);
	sem_init(&lizLock, value[0], value[1]);
	sem_init(&testLock, value[0], value[1]+3);


  /*
   * Create NUM_LIZARDS lizard threads
   */

   for(i = 0; i < NUM_LIZARDS; i++){
	   temp[i] = i;
	   pthread_create(&lizardThreadList[i],NULL,lizardThread, &temp[i]);
   }

  /*
   * Create NUM_CATS cat threads
   */
	for(i = 0; i < NUM_CATS; i++){
		temp2[i] = i;
		pthread_create(&catThreadList[i],NULL,catThread, &temp2[i]);
	}


  /*
   * Now let the world run for a while
   */
  sleep( WORLDEND );


  /*
   * That's it - the end of the world
   */
  running = 0;


  /*
   * Wait until all threads terminate
   */
	for(i = 0; i < NUM_LIZARDS; i++){
	   pthread_join(lizardThreadList[i],NULL);
    }
	
	for(i = 0; i < NUM_CATS; i++){
		pthread_join(catThreadList[i],NULL);
	}




   /*
    * Delete the locks and semaphores
    */

	sem_destroy(&semFull);
	sem_destroy(&testLock);
	sem_destroy(&lizLock);

  /*
   * Exit happily
   */
  return 0;
}


/*
 * These prototypes are declared here so that main()
 * can't use them directly.  Functions and variables
 * must be declared before they can be used.  Using them
 * below this point is fine.
 */

void lizard_sleep(int num);
void cat_sleep(int num);
void sago_2_monkeyGrass_is_safe(int num);
void cross_sago_2_monkeyGrass(int num);
void made_it_2_monkeyGrass(int num);
void lizard_eat(int num);
void monkeyGrass_2_sago_is_safe(int num);
void cross_monkeyGrass_2_sago(int num);
void made_it_2_sago(int num);


/*
 * lizardThread()
 *
 * Follows the algorithm provided in the assignment
 * description to simulate lizards crossing back and forth
 * between a sago palm and some monkey grass.  
 * input: lizard number
 * output: N/A
 * Status: Incomplete - Make changes as you see are necessary.
 */
void * lizardThread( void * param )
{
  int num = *(int*)param;

	if (debug){
		printf("[%2d] lizard is alive\n", num);
		fflush(stdout);
    }

	while(running){
      /* 
       * Follow the algorithm given in the assignment
       * using calls to the functions declared above.
       * You'll need to complete the implementation of
       * some functions by filling in the code.  Some  
       * are already completed - see the comments.
       */

		lizard_sleep(num);
		/*
		* Once the lizard wakes up it will look to see if it's safe
		* I.E. more than 4 lizards on the driveway.
		* If it's safe it will cross if it's not safe it will wait.
		*/
		
		sago_2_monkeyGrass_is_safe(num); 
		
		/*
		 * Once it waits for it's turn it will cross the driveway
		 * and begin eating.
		 */
		
		cross_sago_2_monkeyGrass(num);
		lizard_eat(num);
		
		/*
		 * It will do the same for on the way back to it's home
		 * Check for lizard amount in bidirectional.
		 * Unidirectional it would have to check path ways.
		 */
		
		monkeyGrass_2_sago_is_safe(num);
		
		/*
		 * Crosses back over the driveway to safety
		 * goes back to sleep and possibly goes again to eat.
		 */
		
		cross_monkeyGrass_2_sago(num);

    }

  pthread_exit(NULL);
}





/*
 * catThread()
 *
 * This simulates a cat that is sleeping and occasionally checking on
 * the driveway on lizards.
 * 
 * input: cat number
 * output: N/A
 * Status: Completed
 */
void * catThread( void * param ){
	int num = *(int*)param;

	if (debug){
		printf("[%2d] cat is alive\n", num);
		fflush(stdout);
	}

	while(running){
		
		cat_sleep(num);
		
	  /*
	   * Check for too many lizards crossing
	   */
		sem_wait(&lizLock);  //DP: added lock for checking the variables
		if (numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago > MAX_LIZARD_CROSSING){
			printf( "\tThe cats are happy - they have toys.\n" );
			exit( -1 );
		}
		sem_post(&lizLock);
	}

  pthread_exit(NULL);
}





/*
 * lizard_sleep()
 *
 * Simulate a lizard sleeping for a random amount of time
 * input: lizard number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void lizard_sleep(int num)
{
  int sleepSeconds;

  sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

  if (debug){
		printf( "[%2d] sleeping for %d seconds\n", num, sleepSeconds );
		fflush( stdout );
    }

  sleep( sleepSeconds );

  if (debug){
		printf( "[%2d] awake\n", num );
		fflush( stdout );
    }
}

/*
 * cat_sleep()
 *
 * Simulate a cat sleeping for a random amount of time
 * input: cat number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void cat_sleep(int num)
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP);

	if (debug){
		printf( "[%2d] cat sleeping for %d seconds\n", num, sleepSeconds );
		fflush( stdout );
    }

	sleep( sleepSeconds );

	if (debug){
		printf( "[%2d] cat awake\n", num );
		fflush( stdout );
    }
}

 
/*
 * sago_2_monkeyGrass_is_safe()
 *
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * input: lizard number
 * output: N/A
 * Status: Completed
 */
void sago_2_monkeyGrass_is_safe(int num)
{
	if (debug){
		printf( "[%2d] checking  sago -> monkey grass\n", num );
		fflush( stdout );
    }
	
	/* DP: Allows one lizard to check if it is safe
	 * If it isn't safe (more than 4 lizards on the driveway)
	 * then it will wait for it's turn to cross over
	 */
	
	
	if((numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass) > MAX_LIZARD_CROSSING-1 ){
		sem_wait(&semFull);	  
	}
	

	if (debug){
		printf( "[%2d] thinks  sago -> monkey grass  is safe\n", num );
		fflush( stdout );
    }
	
	
}


/*
 * cross_sago_2_monkeyGrass()
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 * input: lizard number
 * output: N/A
 * Status: Completed
 */
void cross_sago_2_monkeyGrass(int num)
{
  if (debug){
		printf( "[%2d] crossing  sago -> monkey grass\n", num );
		fflush( stdout );
    }

	
  /*
   * One more crossing this way
   */
	sem_wait(&testLock);	//DP: This is the crossing lock allows 4 "lizards"
							//to cross the driveway at a time.

	numCrossingSago2MonkeyGrass++;


  /*
   * Check for lizards cross both ways
   */
	if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL){
		printf( "\tCrash!  We have a pile-up on the concrete.\n" );
		printf( "\t%d crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass );
		printf( "\t%d crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago );
		exit( -1 );
    }
	
	

  /*
   * It takes a while to cross, so simulate it
   */
	sleep( CROSS_SECONDS );

  
  /*
   * That one seems to have made it
   */
	
  
	numCrossingSago2MonkeyGrass--;
	sem_post(&testLock);// DP: Signals for the next lizard if waiting to cross over
	sem_post(&semFull);

}





/*
 * made_it_2_monkeyGrass()
 *
 * Tells others they can go now
 * input: lizard number
 * output: N/A
 * Status: Unused
 */
void made_it_2_monkeyGrass(int num)
{
  /*
   * Whew, made it across
   */
	if (debug){
		printf( "[%2d] made the  sago -> monkey grass  crossing\n", num );
		fflush( stdout );
    }

	lizard_eat(num);

	/* This section of code was unused as I didn't need an indicator 
	 *of crossing over. Up to 4 lizards were allows on the driveway
	 *so in the "isSafe" function we tested and waited for the next
	 *time that it was safe. This function could possibly be used in
	 *unidirectional.
	 */
}





/*
 * lizard_eat()
 *
 * Simulate a lizard eating for a random amount of time
 * input: lizard number
 * output: N/A
 * Status: Completed - No need to change any of this code.
 */
void lizard_eat(int num)
{
  int eatSeconds;

  eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

	if (debug){
		printf( "[%2d] eating for %d seconds\n", num, eatSeconds );
		fflush( stdout );
    }

  /*
   * Simulate eating by blocking for a few seconds
   */
	sleep( eatSeconds );

	if (debug){
		printf( "[%2d] finished eating\n", num );
		fflush( stdout );
    }
}




/*
 * monkeyGrass_2_sago_is_safe()
 *
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 * input: lizard number
 * output: N/A
 * Status: Completed
 */
void monkeyGrass_2_sago_is_safe(int num)
{
	if (debug){
      printf( "[%2d] checking  monkey grass -> sago\n", num );
      fflush( stdout );
    }

	
	if((numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass) > MAX_LIZARD_CROSSING-1 ){
		sem_wait(&semFull);				//DP
	}
	
	
	if (debug){
      printf( "[%2d] thinks  monkey grass -> sago  is safe\n", num );
      fflush( stdout );
    }
}



/*
 * cross_monkeyGrass_2_sago()
 *
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 * input: lizard number
 * output: N/A
 * Status: Completed
 */
void cross_monkeyGrass_2_sago(int num)
{
	if (debug){
		printf( "[%2d] crossing  monkey grass -> sago\n", num );
		fflush( stdout );
    }

  /*
   * One more crossing this way
   */

	sem_wait(&testLock);  //DP: Allows up to 4 lizards shared with both crossings
	numCrossingMonkeyGrass2Sago++;

  
  /*
   * Check for lizards cross both ways
   */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL){
		printf( "\tOh No!, the lizards have cats all over them.\n" );
		printf( "\t%d crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass );
		printf( "\t%d crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago );
		exit( -1 );
    }
	

  /*
   * It takes a while to cross, so simulate it
   */
	sleep( CROSS_SECONDS );

  /*
   * That one seems to have made it
   */
	numCrossingMonkeyGrass2Sago--;
	sem_post(&testLock);	//DP: Allows up to 4 total shared with both crossings
	sem_post(&semFull);
}





/*
 * made_it_2_sago()
 *
 * Tells others they can go now
 * input: lizard number
 * output: N/A
 * Status: Unused
 */
void made_it_2_sago(int num)
{
  /*
   * Whew, made it across
   */
  if (debug)
    {
      printf( "[%2d] made the  monkey grass -> sago  crossing\n", num );
      fflush( stdout );
    }

	/* This section of code was unused as I didn't need an indicator 
	 *of crossing over. Up to 4 lizards were allows on the driveway
	 *so in the "isSafe" function we tested and waited for the next
	 *time that it was safe. This function could possibly be used in
	 *unidirectional.
	 */



}


