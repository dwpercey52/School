/*This program takes in products and formats them for that the first letter is uppercase
It will also take the price and the quantity then multiples it for a total price.
This is put into the table in the proper format.

Author: Darrell Percey
Last Edit: 6/7/2016

COP2253    Project 2
File Name: Product.java
*/

import java.text.*;
import java.util.Scanner;

public class Product{
	
	public static void main(String[] args){
		
	String productNameOne, productNameTwo;     //Declare all needed variables for project
	int productQuantityOne, productQuantityTwo; //Amout of both products
	double productPriceOne, productPriceTwo, totalProductOne, totalProductTwo;   // price for the two products & totals
	
	Scanner userInput = new Scanner(System.in); //Declares scanner for user input
	
	System.out.println("Enter the information for product #1");  //Gathering information for Product 1
	System.out.print("Name: ");
	productNameOne = userInput.next();
	System.out.print("Qty: ");
	productQuantityOne = userInput.nextInt();
	System.out.print("Price: ");
	productPriceOne = userInput.nextDouble();
   
   System.out.println("Enter the information for product #2"); //Gatering information for Product 2
	System.out.print("Name: ");
	productNameTwo = userInput.next();
	System.out.print("Qty: ");
	productQuantityTwo = userInput.nextInt();
	System.out.print("Price: ");
	productPriceTwo = userInput.nextDouble();
   
   String temp = productNameOne.substring(0,1).toUpperCase();                 // Formats the name of Product 1
   productNameOne = productNameOne.substring(1, productNameOne.length()).toLowerCase();
   productNameOne = temp + productNameOne;
   System.out.println( productNameOne);
   
   temp = productNameTwo.substring(0,1).toUpperCase();                        // Formats the name of Product 2
   productNameTwo = productNameTwo.substring(1, productNameTwo.length()).toLowerCase();
   productNameTwo = temp + productNameTwo;
   System.out.println( productNameTwo);
   
   totalProductOne = productQuantityOne * productPriceOne;     //Calculates the total of each product
   totalProductTwo = productQuantityTwo * productPriceTwo;
   
   System.out.println("--------------------------------------------");
   System.out.println("| Product    |   Qty |    Price |    Total |");
   System.out.println("--------------------------------------------");
   System.out.printf("| %-10s |  %4d |    %6.2f |   %6.2f | %n", productNameOne, productQuantityOne, productPriceOne, totalProductOne);
   System.out.printf("| %-10s |  %4d |    %6.2f |   %6.2f | %n", productNameTwo, productQuantityTwo, productPriceTwo, totalProductTwo);
   System.out.println("--------------------------------------------");
   
	}
}