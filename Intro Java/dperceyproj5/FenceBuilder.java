/** This program uses the fence class to build fences
as they are given the information by the user.


Author: Darrell Percey
Last Edit: 7/24/2016

COP2253    Project 5
File Name: FenceBuilder.java
*/


import java.util.Scanner;

public class FenceBuilder{
   
   public static void main(String[] args){
   
      //Declaring variables and objects used.
      String userAnswer = "Y";
      boolean testUser;
      Scanner userInput = new Scanner(System.in);
      Fence myFence = new Fence();
      
      
      System.out.println("Welcome, let's draw some fences!");
      
      //Checks to see if the user wants to contiune with a "Y/y"
      while(userAnswer.equalsIgnoreCase("Y")){
         testUser = false;
         
         //Ask for height input and also checks if it is within a valid range
         System.out.print("Enter a value for the height in the range [2,5]: ");
         while(myFence.setHeight(userInput.nextInt()) != true){
            System.out.println("Error: Value entered was not in range");
            System.out.print("Enter a value for the height in the range [2,5]: ");
         }
         
         //Ask for width input and also checks if it is within a valid range
         System.out.print("Enter a value for the width in the range [3,24]: ");
         while(myFence.setWidth(userInput.nextInt()) != true){
            System.out.println("Error: Value entered was not in range");
            System.out.print("Enter a value for the height in the range [3,24]: ");
         }
         
         //Draws the fence as the width and height should be set to true and given ranged values
         myFence.draw();
         
         
         //Ask if the user wants to draw another fence. If so it checks if the input is valid "Y/y || N/n"
         System.out.print("Would you like to draw another fence? (Y/N): ");
         while(testUser != true){
            userAnswer = userInput.next();
            
            if(userAnswer.equalsIgnoreCase("N") || userAnswer.equalsIgnoreCase("Y")){
               testUser = true;
            }
            else{
               System.out.print("Please enter a valid response: ");
               testUser = false;
            }
         }
      }
      //Prints the amount of fences that were printed.
      System.out.println("There were " + myFence.getFenceCount() + " fences drawn");        
   }
}