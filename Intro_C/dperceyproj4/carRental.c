#include <stdio.h>
#include <string.h>

// Structs for CarT and RentalT to hold information on cars and Rentals 
  struct CarT {
    int    carId;
    char   make[20];
    char   model[20];
    int    numDoors;
    double rate;
    };

  struct RentalT {
    char   renterName[20];
    int    daysRenting;
    int    carId;
    };
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%% This is the section for the newly added code functions %%%%%%%%%%%%%%%%
//%%%%%%   below is the write and read for car and rentals  %%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


//readRentals reads all of the rentals in the text document for rentals
// and inputs them into the system array on start up. 
int readRentals ( char *filename, struct RentalT *allRentals)   {
  char renterName[20];
  int daysRenting, carId, i=0;
  FILE *rentP1;
  
  rentP1 = fopen(filename,"r"); 
  
  while ( fscanf(rentP1,"%s %d %d ", renterName, &daysRenting, &carId) != EOF )  {
    strcpy(allRentals[i].renterName, renterName);
	allRentals[i].daysRenting = daysRenting;
	allRentals[i].carId = carId;
	i++;
  }
  fclose(rentP1);   
  return i;
}

// writeRentals when exiting the program it copies all the rentals from the allRentals
// array, and paste that information into a text document for rentals.
void writeRentals ( char *filename, struct RentalT *allRentals, int totalRentals ) {
  int i=0;
  FILE *rentP1;
  
  rentP1 = fopen(filename, "w+");
  
  while ( i < totalRentals ) {
    fprintf(rentP1,"%s %d %d ", allRentals[i].renterName, allRentals[i].daysRenting, allRentals[i].carId);
	i++;
  }
  fclose(rentP1);

}

//upon the programs start up the readCars function reads in all the cars information
// that was stored inside the text document for the cars values.
int readCars( char *filename, struct CarT *allCars ) {
  int id, door, i=0; 
  double rate;
  char make[20], model[20]; 
  FILE *carP1;
  
  carP1   = fopen(filename, "r");
  
  while ( fscanf(carP1,"%d %s %s %d %lf ", &id, make, model, &door, &rate) != EOF ) {
    allCars[i].carId = id;
    strcpy(allCars[i].make, make);
    strcpy(allCars[i].model, model);
    allCars[i].numDoors = door;
    allCars[i].rate = rate;
    i++;
  }
  fclose(carP1);
  return i;
}

// when exiting the program the writeCars function takes all the cars in the
// allCars arrays and inputs them into a text file 
void writeCars ( char *filename, struct CarT *allCars, int totalCars ) {
  int i=0;
  FILE *carP1;
  
  carP1 = fopen(filename, "w+");
  
  while ( i < totalCars ) {
    fprintf(carP1,"%d %s %s %d %lf ", allCars[i].carId, allCars[i].make, 
			allCars[i].model, allCars[i].numDoors, allCars[i].rate);
	i++;
  }
  fclose(carP1);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%% above is all the new code added for Project6 %%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  
// addNewCar function allows a user to a car to the inventory of available rentals 
int addNewCar ( struct CarT *allCars, int totalCars, int size )  {
  if ( size >= 20 )  {
	printf("You have filled up the inventory slots \n");
	totalCars = 20;
	return totalCars;
  } 
  
  // Asking the user for the information of the car that is being added.
  printf("Please enter the Car ID number.(For Example 1111): ");
  scanf("%d", &allCars[totalCars].carId);
  
  printf("Please enter the make of the vehicle: ");
  scanf("%s", &allCars[totalCars].make);
  
  printf("Please enter the model of the vehicle: ");
  scanf("%s", &allCars[totalCars].model);
  
  printf("Please enter the number of doors on the vehicle: ");
  scanf("%d", &allCars[totalCars].numDoors);
  
  printf("Please enter the rate of rental for the vehicle: ");
  scanf("%lf", &allCars[totalCars].rate); 
  
  totalCars++;
  return totalCars;
  
  }

  
  
  // addNewRental function allows the user to add rentals to the list.
  // this takes the information from the customer and calls the function findCarIdByName to search for the ID
int addNewRental ( struct CarT *allCars, int totalCars, struct RentalT *allRentals, int totalRentals, int size )  {
   
  char carName[20];
  int found; 
  int a = 0;
  
  if ( size >= 60 )  {
	printf("You have filled up the Rental slots available \n");
	totalRentals = 60;
	return totalRentals;
  } 
	
	// Asking the user for the reservation information 
	printf("Please enter the name of the renter: ");
	scanf("%s", &allRentals[totalRentals].renterName);
	
	printf("Please enter the amount of days the user is renting: ");
	scanf("%d", &allRentals[totalRentals].daysRenting);
	
	printf("Enter the make of the car that the user would like to rent: ");

	
	while ( a < 1 ) {
	   scanf("%s", &carName);
	   found = findCarIdByName ( allCars, totalCars, carName );
	   
	  if ( found >= 0 )  {
	    allRentals[totalRentals].carId = allCars[found].carId;
	    totalRentals++;
		printf("Your rental has been added successfully \n");
	    return totalRentals;
      }
      else if ( found == -1 )  { 
	    printf("Please enter a valid car in the inventory \n");
      }
	}
}



// findCarIdByName is a function that compares the name to other picked to pull an ID for the rental struct
// this is put into the function addNewRental just above
int findCarIdByName ( struct CarT *allCars, int totalCars, char *carName )  {

  int check, a;
  a = 0;
  totalCars = 0;
  
  // continuous loop for comparison 
  while ( a < 1 )  {
  
    check = strcmp ( carName , allCars[totalCars].make );
   
    if ( check == 0 )  { 
      return totalCars;
	  break; 
    } 
    else if ( totalCars > 20 )  { 
	  return -1;
	  break;
	} 
	totalCars++;
  }
	
}



//findReservation function is used to find a renter and the information of their rental
int findReservation ( struct RentalT *allRentals, int totalRentals, char *renterName )  {
   
   int a = 0; 
   int check, foundCar; 
   totalRentals = 0;
   
   
  // continuous loop for comparison 
  while  ( a < 1 )  { 
	check = strcmp ( renterName, allRentals[totalRentals].renterName);
	if ( check == 0 ) { 
      return totalRentals;
	  break; 
	} 
    else if ( totalRentals > 60 )  { 
	  return -1; 
	  break; 
    }
	totalRentals++;
  }
	
} 
	

 
// findCarById search the inventory list of cars to find a car by it's Id
int findCarById ( struct CarT *allCars, int totalCars, int carId )  {

  int a;
  a = 0;
  totalCars = 0;
  
// continuous loop for comparison 
  while ( a < 1 )  {
    if ( carId == allCars[totalCars].carId )  { 
      return totalCars;
      break;
	}
	else if ( totalCars > 20 ) {
	  return -1;
      break; 		
	}
	totalCars++;
  }
  
} 


void printCarInfo ( struct CarT *allCars, int totalCars, int carId )  {

  
  if ( carId >= 0 ) {
	printf("Make: %s \n", allCars[carId].make);
    printf("Model: %s \n", allCars[carId].model);
	printf("Doors: %d \n", allCars[carId].numDoors);
	printf("Rate: $%.2lf \n", allCars[carId].rate);
  }
  else if ( carId == -1 )  {
    printf("Car not found \n");
  }
}
  

//this function printAllRentals allows the user to print all of the rentals that are currently in the system
void printAllRentals ( struct CarT *allCars, struct RentalT *allRentals, int totalCars, int totalRentals )  {

  int i, carInfo; 
  
  for ( i = 0; i < totalRentals; i++ ) {
	carInfo = findCarById ( allCars, totalCars, allRentals[i].carId);
	printf("Rental %d \n ", i+1);
	printf("Name: %s \n", allRentals[i].renterName);
	printf("Days:  %d \n", allRentals[i].daysRenting);
    printCarInfo ( allCars, totalCars, carInfo );
	printf("\n");
	  
  }
}
  


double getAverageRentalDays ( struct RentalT *allRentals, int totalRentals )  {
  
  int i, sum;
  double totalHold; 
  
 
	if ( totalRentals == 1 )
      { 		  
        totalHold = allRentals[0].daysRenting;
	    return totalHold;
	  } 
 else if ( totalRentals > 1 )
	  {
	    for ( i = 1; i < totalRentals; i++ )
	      {
		    sum = allRentals[i].daysRenting + allRentals[i-1].daysRenting;
		    totalHold += sum;
		  }
		  totalHold = totalHold  / totalRentals;
		  return totalHold;
	  } 
     
  else if ( totalRentals == 0 )
    {
	  return -1;
	}
}



int main (int fileNums, char *carFiles[])
{
  // Arrays for CarT and RentalT 
  int totalCars, totalRentals, sizeCars, sizeRentals, pick, pickId, foundCarId, foundCar, foundInfo, a, totalDays;
  char renterName[20];
  struct CarT allCars[20];
  struct RentalT allRentals[60];
  FILE *carP1;
  
  // assigns values for the starting = 3 for the 3 pre-made cars, and 0 for no rentals in the system yet
  sizeCars = 3;
  sizeRentals = 0;
  totalRentals = 0;
  totalCars = 0;
  a = 0;

  // checks to see if three files were opened, else it exits the program.
    if ( fileNums != 3 ) {
    printf("Failed to do operations, you must open the program and two text files. \n");
	return 1;
  }
  
  totalCars = readCars( carFiles[2], allCars ); 
  totalRentals = readRentals( carFiles[1], allRentals);
  
  printf("Welcome to the car rental services! \n");
  
  while ( a == 0 )  { 
  
    // Displays the menu so the user knows what numbers to press for which options.
    printf("\n Type the number of the action you would like to do. \n");
    printf("1. Add new car to the inventory \n");
    printf("2. Make a reservation \n");
    printf("3. Find a reservation using a name \n");
    printf("4. Print all rental information \n");
    printf("5. Print car information \n");
    printf("6. Calculate the average days rented \n");
    printf("7. Exit our services \n");
	
    // Picks an action in the switch statement 
    scanf("%d", &pick);
  
    // switch statement is the entire menu and uses all the functions to allow the user to do all the actions.
    switch ( pick ) {
      case 1 : 
	    totalCars = addNewCar ( allCars, totalCars, sizeCars );
	    printf("The total cars in the inventory is %d out of 20 \n", totalCars);
	    sizeCars++;
        break;
	  case 2 :
	    totalRentals = addNewRental ( allCars, totalCars, allRentals, totalRentals, sizeRentals );
        sizeRentals++;
	    break;
	  case 3 :
	    printf("Enter the name of the reservation to search for: ");
	    scanf("%s", &renterName);
	    foundInfo = findReservation ( allRentals, totalRentals, renterName );
	  
	    if ( foundInfo >= 0 )
	      {
	        foundCarId = allRentals[findReservation ( allRentals, totalRentals, renterName )].carId;
	        findCarById ( allCars, totalCars, foundCarId );
	        foundCar = findCarById ( allCars, totalCars, foundCarId );
			printf ("Reservation\n");
	        printf ("Car:  %s %s \n", allCars[foundCar].make, allCars[foundCar].model );
			printf ("Name: %s \n", allRentals[foundInfo].renterName );
			printf ("Days: %d \n", allRentals[foundInfo].daysRenting );
			printf ("Rate: $%.2lf \n", allCars[foundCar].rate );
		  }
	    else if ( foundInfo < 0 )
	      {
		    printf("There are no current reservations under that name \n");
		  }
		  break;
      case 4 :
	    if ( totalRentals > 0 ) 
          {		
	        printAllRentals ( allCars, allRentals, totalCars,  totalRentals );
		  }
		else if ( totalRentals == 0 )
		  {
		    printf("There are no rentals at this time");
		  } 
		break;
	  case 5 :
	    printf("Please enter a car ID you would like to search for: ");
        scanf("%d", &pick);
		pickId = findCarById ( allCars, totalCars, pick );
		printf("Car Information \n");
	    printCarInfo ( allCars, totalCars, pickId );
		break;
      case 6 : 
	    totalDays = getAverageRentalDays ( allRentals, totalRentals );
		if ( totalDays >= 0 ) 
		  {
		    printf("The average rental days is %d \n", totalDays);
		  }
		else if ( totalDays == -1 ) 
		  {
		    printf("There are no reservation days currently \n");
		  }
		break;
	  case 7 : 
		writeCars ( carFiles[2], allCars, totalCars );
		writeRentals ( carFiles[1], allRentals, totalRentals );
	    a++;
		break;
 	  default  : 
	    printf("Please enter a valid action \n");
	    break;
	  }
	}
	
  
}












