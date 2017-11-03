/** This class holds the Golfers attributes
and an array of score objects for the golfer

Author: Darrell Percey
Last Edit: 7/27/2016

COP2253    Project 6
File Name: Golfer.java
*/

public class Golfer{
   
   //instance variables for golfer
   private String name;
   private String homeCourse;
   private int idNum;
   private int numOfScores;
   private Score[] scores;
   private static int nextIDNum = 1000;
   private static final int NOTFOUND = -1;
   
   //Constructors for golfer default and para.
   public Golfer(){
      name = "";
      homeCourse = "";
      idNum = 0;
      numOfScores = 0;
      scores = new Score[10];
   }
   
   public Golfer(String name, String home){
      this.name = name;
      homeCourse = home;
      scores = new Score[10];
   }
   
   
   //Accessor methods for name, course, and ID
   public String getName(){
      return name;
   }
   
   public String getHomeCourse(){
      return homeCourse;
   }
   
   public int getIDNum(){
      return idNum;
   }
   
   
   //Mutator methods for name, course and ID
   public void setName(String name){
      this.name = name;
   }
   
   public void setHomeCourse(String course){
      homeCourse = course;
   }
   
   public void setIDNum(){
      idNum = nextIDNum;
      nextIDNum++;
   }
   
   
   //Adds a score to the array of score objects
   public void addScore(String course, int score, double rating, int slope, String date){
      Score temp = new Score();
      temp.setScore(score);
      temp.setCourseName(course);
      temp.setCourseRating(rating);
      temp.setCourseSlope(slope);
      temp.setDate(date); 
      
      int i = 0;
      if(scores[9] == null){
         while(scores[i] != null){
            i++;
         }
      scores[i] = temp;
      }
      else{
         System.out.println("Can't add more scores, player " + name + "'s list is full");
      }
   }
   
   //Get the score object by finding it with the date given
   public Score getScore(String date){
      int i = findScore(date);
      
      if( i == -1){
         System.out.println("Could not find that score");
         return null;
      }
      else{
         System.out.println("The score sheet for the date " + date + " was found");
         return scores[i];
      }
   }
           
   //finds and deletes the score object with the date given then reoriginizes the array      
   public boolean deleteScore(String date){
      int i = 0;
      
      i = findScore(date);
      if(i == -1){
         System.out.println("Score was not found");
         return false;
      }
      else{
         while(scores[i] != null){
               scores[i] = scores[i+1];
               scores[i+1] = null;
               i++;
         }
         System.out.println("Score on " + date + " was deleted for " + name);
         return true;
      }
   }
   
   
   //Finds the index of the score in the array
   private int findScore(String date){
      int i = 0;
      while(i < 10){
         if(scores[i].getDate() == date){
            return i;
         }
         i++;
      }
      return NOTFOUND;
   }
   
   
   //Displays all the information for the golfer object neatly 
   public String toString(){
      int i = 0;
      String s = "Score  Date       Course       Rating Slope \n";
      
      while(scores[i] != null){
         s = s + scores[i].toString();
         i++;
         if(i == 10){
            break;
         }
      }
      return String.format("%-8s  ID #: %-4d  Home Course: %-10s \n",name, idNum, homeCourse) + s;
   }
   
}