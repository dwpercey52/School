/** This program calls methods from the GuessingGame.java file
Running a loop to contiune playing the game till the user decides
they want to exit.


Author: Darrell Percey
Last Edit: 7/9/2016

COP2253    Project 4
File Name: GuessingGame.java
*/

import java.util.Scanner;

public class GuessingGameTester{


   public static void main(String[] args){
   
      String contiunePlaying = "Y";                   //1 Variable and Scanner object
      Scanner userInput = new Scanner(System.in);
      
      System.out.println("Welcome to the Guessing Game!");
      
      while( contiunePlaying.equalsIgnoreCase("Y")  ){                  //While for new game. Checks for Yes / No
         System.out.println("Enter a max value for a guessing range.");
         GuessingGame gameOne = new GuessingGame(userInput.nextInt());
         
         while( gameOne.isGameOver() == false ){                     // Checks to see if one game is over
            System.out.println("Enter a guess");
            gameOne.guess(userInput.nextInt());
         }
         
         System.out.println("Would you like to start a new game? (Y/N)");
         contiunePlaying = userInput.next();
      }
   }
   
}
