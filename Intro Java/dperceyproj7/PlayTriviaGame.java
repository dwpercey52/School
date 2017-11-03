/** This program allows the user to start a game and 
it ask at the end of each game if the player would like to 
play another. This runs using teh TriviaGame class and the
Question class.

Author: Darrell Percey
Last Edit: 7/31/2016

COP2253    Project 7
File Name: TriviaGame.java
*/


import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileNotFoundException;


public class PlayTriviaGame{

   //I had to make this method because when I added the line "answer = userInput.nextLine();" in the line
   //where I comment RIGHT HERE LINE ENTER it would skip through the loop once (I beleive this was due to
   //an error/glitch in the Scanner object. So I made this method so it wouldn't skip through
    private static String userInput(){
      Scanner userInput = new Scanner(System.in);
      String temp = "";
      temp = userInput.nextLine();
      return temp;
   }



   public static void main(String[] args){
      
      //All objects and variables needed for the program
      FileInputStream file = null;
      TriviaGame gameOne = null;
      Scanner userAnswer = new Scanner(System.in);
      String answer = "Y";
      boolean testUser = false;
      int numberEntry = 0;
      int startNumber = 0;
      
      //Test for the file that we are using
      try{
        file = new FileInputStream("questions.dat");
        gameOne = new TriviaGame(file);
      }
      catch (FileNotFoundException e){
         System.out.println("File not found.");
         System.exit(0);
      }
      
      
     //Ask the user for the amount of questions they want
      System.out.print("Enter the amount of questions you would like (10 or less): ");
      numberEntry = userAnswer.nextInt();
      // Sees if the amount of questions is less than 10
      while(numberEntry > 10){
         System.out.print("Enter the amount of questions you would like (10 or less): ");
         numberEntry = userAnswer.nextInt();
      }
         
      //Test for "Y" or "y" to continue with a new game
      while( answer.equalsIgnoreCase("Y")){
         testUser = false;
         gameOne.play(numberEntry);
         
         startNumber = 0;
        
         //Goes from the 0 to the amount of questions the player wanted
         while(startNumber < numberEntry){
            System.out.println(gameOne.nextQuestion());
            answer = userInput(); // RIGHT HERE LINE ENTER
            //As I said I tried a direct input but it would error for some odd reason
            if(gameOne.evaluateAnswer(answer) == true){
               System.out.println(answer + " is correct");
            }
            else{
               System.out.println(answer + " is incorrect");
            }
            
            startNumber++;
         } 
         
         System.out.println("Your score this round is: " + gameOne.getScore());
            

      
         
         
         //Ask if the user wants to draw another fence. If so it checks if the input is valid "Y/y || N/n"
         System.out.print("Would you like to play again? (Y/N): ");
         while(testUser != true){
            answer = userAnswer.next();
            
            if(answer.equalsIgnoreCase("N") || answer.equalsIgnoreCase("Y")){
               testUser = true;
            }
            else{
               System.out.print("Please enter a valid response: ");
               testUser = false;
            }
         }
      } 
      System.out.println("---------------------------------------------"); 
      System.out.println("--Thanks for playing, the answers are below--");
      System.out.println("---------------------------------------------"); 
      System.out.println(gameOne);    
   } 
}
      
      
      
 