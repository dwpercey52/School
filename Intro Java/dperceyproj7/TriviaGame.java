/** This program is used to make a Trivia game object
so that it will ask the player questions when called
and it will evulate the answers based on the answer given.
Also it holds the score of the player

Author: Darrell Percey
Last Edit: 7/31/2016

COP2253    Project 7
File Name: TriviaGame.java
*/


import java.util.Scanner;
import java.io.FileInputStream;

public class TriviaGame{
   
   private Question[] gameQuestions;
   private int score;
   private int numberOfQuestions;
   private int currentQuestion;
  
  
  //Constructor taking in a file input that contains the questions
   public TriviaGame(FileInputStream file){
      Scanner fileIn = new Scanner(file);
      gameQuestions = new Question[10];
      
      int i = 0;
      while(fileIn.hasNextLine()){
         gameQuestions[i] = new Question();
         gameQuestions[i].setQuestion(fileIn.nextLine());
         if(fileIn.hasNextLine() == true){
            gameQuestions[i].setAnswer(fileIn.nextLine());
            if(fileIn.hasNextLine() == true){
               gameQuestions[i].setValue(fileIn.nextInt());
               if(fileIn.hasNextLine() == true){
                  fileIn.nextLine();
               }
            }
         }
         i++;
      }
      currentQuestion = 0; 
   }
   
   //Accessor methods for numberOfQuestions, currentQuestion, and score
   public int getNumberOfQuestions(){
      return numberOfQuestions;
   }
   
   public int getCurrentQuestion(){
      return currentQuestion;
   }
   
   public int getScore(){
      return score;
   }
   
   //Resets the game for a fresh game.
   public void play(int numQuestion){
      score = 0;
      currentQuestion = 0;
      numberOfQuestions = numQuestion;
   }
   
   //Returns the nextQuestion for the player
   public String nextQuestion(){
      return gameQuestions[currentQuestion].getQuestion();
   }
   
   //Test if the answer is correct or incorrect (MUST BE EXACTLY THE SAME) 
   public boolean evaluateAnswer(String answer){
      if( answer.equals(gameQuestions[currentQuestion].getAnswer()) == true){
         score += gameQuestions[currentQuestion].getValue();
         currentQuestion++;
         return true;
      }
      else{
         currentQuestion++;
         return false;
      }
   }
   
   //Formats all the questions the player tried to answer with answers
   public String toString(){
      String s = "";
      for(int i = 0; i < numberOfQuestions; i++){
         s += gameQuestions[i].toString();
      }
      
      return s;
   }    
}
  