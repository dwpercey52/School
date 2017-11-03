/***************************************************************/
/* Darrell Percey				                               */
/* OfflineSet.h                                                */
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

#ifndef OfflineSet_h
#define OfflineSet_h

#include "Builds.h"

/*********************************
* See C file for details on each *
*********************************/
binP offlineFirstFit(infoP info);
binP offlineBestFit(infoP info);
float* sortSetFF(float* arr, infoP info);
float* sortSetBF(float* arr, infoP info);

#endif