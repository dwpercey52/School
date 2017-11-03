/** This holds the score and course information
This is casted into an array in the Golfer class
to hold all the score/course info.

Author: Darrell Percey
Last Edit: 7/27/2016

COP2253    Project 6
File Name: Score.java
*/

public class Score{

   private String courseName;
   private String date;
   private int score;
   private int courseSlope;
   private double courseRating;
   
   
   //Constructors default and para.
   public Score(){
      courseName = "";
      date = "";
      score = 0;
      courseSlope = 0;
      courseRating = 0;
   }
   
   public Score(String course, String date, int score, int slope, double rating){
      courseName = course;
      this.date = date;
      this.score = score;
      courseSlope = slope;
      courseRating = rating;
   }
   
   
   //Mutators for all the variables
   public void setScore(int score){
      this.score = score;
   }
   
   public void setCourseName(String name){
      courseName = name;
   }
   
   public void setDate(String date){
      this.date = date;
   }
   
   public void setCourseSlope(int slope){
      courseSlope = slope;
   }
   
   public void setCourseRating(double rating){
      courseRating = rating;
   }
   
   
   //Accesors for all the variables
   public int getScore(){
      return score;
   }
   
   public String getDate(){
      return date;
   }
   
   public double getCourseRating(){
      return courseRating;
   }
   
   public int getCourseSlope(){
      return courseSlope;
   }
   
   public String getCourseName(){
      return courseName;
   }
   
   //Prints the string in a neat manner
   public String toString(){
      return String.format("%-3d    %-8s   %-12s %-3.1f   %-3d \n",score,date,courseName,courseRating,courseSlope);
   }

}