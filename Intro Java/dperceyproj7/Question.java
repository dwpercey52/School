/** This program provides the questions, answers, and scores for each of 
the questions that are used in the TriviaGame class.

Author: Darrell Percey
Last Edit: 7/31/2016

COP2253    Project 7
File Name: TriviaGame.java
*/

public class Question{
   
   private static final int INVALIDINPUT = -1;
   private String question;
   private String answer;
   private int value;
   
   //Constructors Default and para
   public Question(){
      question = "";
      answer = "";
      value = 0;
   }
   
   public Question(String question, String answer, int value){
      this.question = question;
      this.answer = answer;
      setValue(value);
   }
   
   
   //Accesor methods for each of the instance variables
   public String getQuestion(){
      return question;
   }
   
   public String getAnswer(){
      return answer;
   }
   
   public int getValue(){
      return value;
   }
   
   //Mutator methods for each of the instance variables
   public void setQuestion(String question){
      this.question = question;
   }
   
   public void setAnswer(String answer){
      this.answer = answer;
   }
   
   public void setValue(int value){
      if(value >= 1 && value <= 5){
         this.value = value;
      }
      else{
         this.value = INVALIDINPUT;
         System.out.println("Error: Value must be between [1,5]");
      }
   }
   
   //Prints a formatted verison for all the variables
   public String toString(){
      String s = "Q: " + getQuestion() + " \nA: " + getAnswer() + " \n" + getValue() + "\n";
      return s;
   }
}