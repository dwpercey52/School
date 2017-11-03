/** This program takes in user input for three values of a starting balance,
an interest rate, and the amount of quarters to show a compunding interest.
It will then do the calculations and display each quarters starting and ending balance
with the amount of interest earned for that quarter.


Author: Darrell Percey
Last Edit: 6/15/2016

COP2253    Project 3
File Name: InterestCalculator.java
*/

import java.util.Scanner;

public class InterestCalculator {

   public static void main(String[] args) {
   
      int  numberOfQuarters = 0, placeholderQuarter = 0, checkInformation = 0 ;    //Declaring all needed variables
      double  startingBalance = 0,endingBalance = 0, interestRate = 0 , interestEarned = 0;
      String  userAnswer;
   
      Scanner userInput = new Scanner(System.in);  // Setting an object for the user input
   
      System.out.println("Welcome, this program will calcualte the interest earned!");
   
      while ( checkInformation == 0 ){              //This loop gathers information from the user for all values needed
      
         int temp = 0;
         while( temp == 0 ) {             //gathers information for quarters and checks if it's in the proper range
            System.out.println("Enter number of quarters from 1 to 10");
            numberOfQuarters = userInput.nextInt();
            
            if ( 1 <= numberOfQuarters && 10 >= numberOfQuarters ){
               temp ++;
            }
            else {
               System.out.println("Error: Value for quarters should be between 1 to 10 \n");
            }
         }
         
         temp = 0;
         while( temp == 0 ) {       //gathers information for starting balance making sure it is over 0
            System.out.println("Enter your starting balance great than 0");
            startingBalance = userInput.nextDouble();
            
            if ( startingBalance > 0 ){
               temp ++;
            }
            else {
               System.out.println("Error: Value for the starting balance should be greater than 0 \n");
            }
         }
         
         temp = 0;
         while( temp == 0 ) {       //gathers information for the interest rate and makes sure it's in the proper range
            System.out.println("Enter your interest rate percentage greater than 0% up to 20%");
            System.out.println("For Example: If it's 5.23% enter 5.23");
            interestRate = userInput.nextDouble();
            
            if ( 0 < interestRate && interestRate <= 20 ){
               temp ++;
            }
            else {
               System.out.println("Error: Value for the interest rate should be great than 0% up to 20% \n");
            }
         }
   
         System.out.printf("You have entered a starting balance of %.2f for %d quarters at %.2f \n", startingBalance, numberOfQuarters, interestRate);
         System.out.println("Is this correct? (y/n)");                   //Asking user if information entered is correct
         userAnswer = userInput.next();
   
         if( userAnswer.equalsIgnoreCase("y") ){            //If information entered is correct the program will enter a new
            System.out.println("Quarter    Beginning    Interest   Ending    "); // loop and do calcualation for the interest
            System.out.println("Number     Balance      Earned     Balance   ");
            while ( placeholderQuarter < numberOfQuarters ) {
               interestEarned = startingBalance * ((interestRate / 100) *.25);
               endingBalance = interestEarned + startingBalance;
               placeholderQuarter ++;
               System.out.printf("%-2d         $%-9.2f   $%-7.2f   $%-9.2f \n", placeholderQuarter, startingBalance, interestEarned, endingBalance);
               startingBalance = endingBalance;
            }
            checkInformation ++;   //Breaks the org loop (ending the program)
         }
      }
   }
}