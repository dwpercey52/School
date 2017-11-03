/***************************************************************/
/* Darrell Percey				                               */
/* Builds.h                                                    */
/* Project 4 || Data Structure II							   */
/*               											   */
/*															   */	
/*	This program will simulate bin packing for 5 different     */
/*  types of the problem Online: First, Next and Best fit,     */
/*  and the Offline: First and Best fit. It will simulate them */
/*  all at once and then print the information to the screen   */
/*  first with a table showing the bins used then with a       */
/*  display of the bins and the items in them.				   */
/*                      									   */	
/*	Files Needed: Test.c OfflineSet.c OnlineSet.c Builds.c     */
/*   OnlineSet.h OfflineSet.h Builds.h 	   					   */
/*   Compile by makefile  typing make in unix 				   */
/*                                                             */
/*                                                             */
/***************************************************************/


#ifndef Builds_h
#define Builds_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LISTSIZE 10000

//Type defs of pointers to structures
typedef struct information* infoP;
typedef struct bin* binP;


//Holds link list of all packaging 
struct information{
	
	binP OnFF;
	binP OnNF;
	binP OnBF;
	binP OffFF;
	binP OffBF;
	
	int sizeList;
	int maxSize;
	float totalList[LISTSIZE];
	
} information;


//Bins for each set
struct bin{
	int totalItems;
	float currentSize;
	float itemList[LISTSIZE];
	binP next;
	
} bin;

/*********************************
* See C file for details on each *
*********************************/
infoP createNewInfoNode();
infoP readFileInfo(infoP temp);
binP createNewBinNode();
void addToBin(binP bin,float item);
void printAllInfo(infoP info);
void displayInformation(binP bin);
int calculateBinsUsed(binP bin);
void freeMemory(binP bin);


#endif