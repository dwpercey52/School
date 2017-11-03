/***************************************************************/
/* Darrell Percey				                               */
/* Test.c                                                      */
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


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Builds.h"
#include "OnlineSet.h"
#include "OfflineSet.h"



int main(){
	//Makes struct that holds all information
	infoP info = createNewInfoNode();
	
	//Does all bin packing
	info->OnFF = onlineFirstFit(info);
	info->OnNF = onlineNextFit(info);
	info->OnBF = onlineBestFit(info);
	info->OffFF = offlineFirstFit(info);
	info->OffBF = offlineBestFit(info);
	
	//Displays table + information
	printAllInfo(info);
	
	//Frees all memory and list
	freeMemory(info->OnFF);
	freeMemory(info->OnNF);
	freeMemory(info->OnBF);
	freeMemory(info->OffFF);
	freeMemory(info->OffBF);
	free(info);
	
	return 0;
}