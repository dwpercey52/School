/** This program holds the mutator, constructors, and accessor
methods for the Fence class. This can also draw the fence once called on

Author: Darrell Percey
Last Edit: 7/24/2016

COP2253    Project 5
File Name: Fence.java
*/



public class Fence{

   //instance variables for Fence class
   private static int fenceCount;
   private int height;
   private int width;
   
   //Constructors default and parameterized.
   public Fence(){
      height = 0;
      width = 0;
      fenceCount = 0;
   }
   
   public Fence(int height, int width){
      this.height = height;
      this.width = width;
   }
   
   //get methods also known as accessors, returns information of variables
   public int getHeight(){
      return height;
   }
   
   public int getWidth(){
      return width;
   }
   
   public int getFenceCount(){
      return fenceCount;
   }
   
   //mutator functions for height and width of the fence
   public boolean setHeight(int height){
      if(height < 6 && height > 1){
         this.height = height;
         return true;
      }
      else{
         return false;
      }    
   }
   
   public boolean setWidth(int width){
      if(width < 25 && width > 2){
         this.width = width;
         return true;
      }
      else{
         return false;
      }
   }
   
   //draws the fence and increments the fence count
   public void draw(){
      int i, j;
      for(i = 0; i < height; i++){
         if(i == 0 || i == (height-1)){
            for(j = 0; j < width; j++){
               System.out.print("#");
            }
         }
         else{
            for(j = 0; j < width; j++){
               if(j == 0 || j == (width-1)){
                  System.out.print("#");
               }
               else{
                  System.out.print("|");
               }
            }
         }
         System.out.print("\n");
      }
      fenceCount++;
   } 
}