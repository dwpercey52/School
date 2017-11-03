/** This program holds the methods for the a Guessing Game
In the GuessingGameTester.java we call these methods to allow
the user to play a guessing game by giving text clues wheather 
they are closer or further.


Author: Darrell Percey
Last Edit: 7/9/2016

COP2253    Project 4
File Name: GuessingGame.java
*/

import java.util.Random;
import java.util.Scanner;

public class GuessingGame {

   private static final int MAXGUESSESALLOWED = 6;
   
   private int max;              //Declared variables for methods
   private int answer;
   private int differential;
   private int numGuessTaken;
   private boolean gameOver;
   Random generator = new Random(); 
   
   //Constructors
   public GuessingGame(){
      max = 0;
      newGame(0); 
   }
   
   public GuessingGame(int maxNumber){
      max = maxNumber;
      newGame(max);
   }
   
   //^^Constructors
   
   public void newGame(int maxNumber){    //Resets the game.
      answer = generator.nextInt(max);
      gameOver = false;
      differential = max;
      numGuessTaken = 0;  
   }
   
   public void guess(int guessTaken){           //Takes account the new guess 
      guessTaken = errorCheck(guessTaken);
      
      if(answer == guessTaken){
         System.out.println("You have won!");
         System.out.println("The answer was " + guessTaken);
         gameOver = true;
      }
      else{
         testDifference(guessTaken);
         testRange(guessTaken);
      }
      numGuessTaken++;
      isGameOver();
   }
   
   public boolean isGameOver(){           //Checks to see if the game is over
      
      if( gameOver == true ){
         return gameOver;
      }
      else if( numGuessTaken == MAXGUESSESALLOWED ){
         System.out.println("You have ran out of guesses!");
         System.out.println("The answer was " + answer);
         gameOver = true;
         return gameOver;
      }
      else{
         return gameOver;
      }
   } 
   
   public void testDifference(int currentGuess){         //Test for the absolute difference for the differential
      if( Math.abs(currentGuess-answer) > differential ){
         System.out.println("You are getting colder!");
         differential = Math.abs(currentGuess-answer);
      }
      else{
         System.out.println("You are getting warmer!");
         differential = Math.abs(currentGuess-answer);
      } 
   }
   
   public void testRange(int currentGuess){        //Test the range if too high or low
      if(currentGuess > answer){
         System.out.println("Too high!");
      }
      else{
         System.out.println("Too low!");
      }
   } 
   
   public int errorCheck(int guessTaken){       //Checks the guess to see if it is out of range.
      Scanner userError = new Scanner(System.in);
      while( guessTaken < 0 || guessTaken > max ){
         System.out.println("Please enter a number between 0 and " + max);
         guessTaken = userError.nextInt();
      }
      return guessTaken; 
   } 
}
