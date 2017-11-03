/** This program is used to test the many different methods
of the Golfer class to make sure it functions properly
Also the Score class is tested through the Golfer class.

Author: Darrell Percey
Last Edit: 7/27/2016

COP2253    Project 6
File Name: GolfTester.java
*/

import java.util.Random;

public class GolferTester{

   public static void main(String[] args){
   
      Random generator = new Random();
      Golfer player1 = new Golfer();
      Golfer player2 = new Golfer("Billy", "BayView");
      Score temp;
      player1.setName("John");
      player1.setHomeCourse("Parkview Hills");
      player1.setIDNum();
      player2.setIDNum();
      
      player1.addScore("Bell Park", 75, 55.4, 120, "05/15/16");
      player1.addScore("Darth Park", 34, 35.4, 65, "03/20/16");
      player1.addScore("Seaside Hills", 42, 55.4, 75, "12/14/16");
      player1.addScore("TreeDown", 25, 32.2, 23, "05/24/16");
      
      player1.deleteScore("12/14/16");
      player1.deleteScore("05/24/16");
      
      player2.addScore("Bell Park", 55, 62.4, 85, "05/15/16");
      player2.addScore("Darth Park", 48, 85.6, 62, "03/20/16");
      player2.addScore("Horse Ln", 52, 64.5, 165, "12/01/16");
      player2.addScore("TreeDown", 62, 38.8, 75, "05/24/16");
      player2.addScore("Elenwood", 65, 61.3, 85, "03/12/16");
      player2.addScore("Swordfall", 34, 75.2, 125, "08/23/15");
      player2.addScore("DownFalls", 78, 25.1, 113, "11/30/16");
      player2.addScore("TreeDown", 20, 65.2, 148, "05/13/16");
      player2.addScore("Bell Park", 82, 85.2, 180, "02/24/16");
      player2.addScore("Bell Park", 34, 58.3, 35, "02/14/16");
      player2.addScore("Skyleft", 16, 54.2, 27, "12/24/16");
      
      System.out.println("Trying to find the score on 11/30/16 for " + player2.getName());
      temp = player2.getScore("11/30/16");
      System.out.printf("The information for this score is below \n");
      System.out.printf("Score: %d  Course: %s  Rating: %.1f  Slope: %d  Date: %s",
         temp.getScore(), temp.getCourseName(), temp.getCourseRating(), temp.getCourseSlope(), temp.getDate());
         
      System.out.println("");
      
      System.out.println("Trying to find the score on 12/30/16 for " + player2.getName());
      temp = player2.getScore("12/30/16");
      
      System.out.println(player1.toString());
      
      System.out.println("--------------------------------------");
      System.out.println("--------------------------------------");
      System.out.println("");
      
      System.out.println(player2.toString());
   }
}
      