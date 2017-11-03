/***************************************************************/
/* Darrell Percey				                               */
/* OfflineSet.c                                                */
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

#include "OfflineSet.h"




/*
* Function:  offlineFirstFit()
* Return: binP
*
* Description:
* Does the first fit bin packing. Similar to
* online but this one sorts the array from small
* to large then places in the bins
*
*/
binP offlineFirstFit(infoP info){
	int i, j, m;
	float arr[info->sizeList];
	
	for(i = 0; i < info->sizeList; i++){
		arr[i] = info->totalList[i];
	}
	
	sortSetFF(arr,info);
	i = 0;
	
	binP head = createNewBinNode();
	binP current = head;
	
	addToBin(current, arr[i]);
	i++;
	
	for(i = 1; i < info->sizeList; i++){
		j = 0;
		m = 0;
		
		if((arr[i] + current->currentSize) < info->maxSize){
			addToBin(current, arr[i]);
			m = 1;
		}
		else{
			while(j == 0){
				if(current->next != NULL){
					current = current->next;
				}
				else{
					j++;
				}
				if(arr[i] + current->currentSize < info->maxSize){
					addToBin(current, arr[i]);
					m++;
					j++;
				}
			}
		}
		
		if(m == 0){
			current->next = createNewBinNode();
			current = current->next;
			addToBin(current,arr[i]);
		}
		current = head;
	}
	
	return head;
}


/*
* Function:  offlineBestFit()
* Return: binP
*
* Description:
* Similar to the online best fit but this one.
* first sorts the array from largest to smallest.
* Once sorted then it tries to calculate the best
* bins that each item will fit in.
*
*/
binP offlineBestFit(infoP info){
	int i, j;
	float arr[info->sizeList];
	binP head = createNewBinNode();
	binP current = head;
	binP best = head;
	
	
	for(i = 0; i < info->sizeList; i++){
		arr[i] = info->totalList[i];
	}
	
	sortSetBF(arr,info);
	
	
	for(i = 0; i < info->sizeList; i++){
		j = 0;
		while(j == 0){
			if(current->next != NULL){
				current = current->next;
				if((arr[i] + current->currentSize) < info->maxSize){
					if(current->currentSize > best->currentSize || best->currentSize + arr[i] > info->maxSize){
						best = current;
					}
				}
			}
			else{
				j++;
			}
		}
		
		if(best->currentSize + arr[i] > info->maxSize){
			current->next = createNewBinNode();
			current = current->next;
			addToBin(current,arr[i]);
		}
		else{
			addToBin(best, arr[i]);
		}
		current = head;
		best = head;
	}
	return head;
}


/*
* Function:  sortSetFF()
* Return: float*
*
* Description:
* Sorts the array from smallest to largest for the
* first fit offline bin packing. This allows it to
* place in the bins more efficiently.
*
*/
float* sortSetFF(float* arr, infoP info){
	int i, j;
	float temp;
	for(i = 0; i < info->sizeList; i++){
		for(j = 0; j < info->sizeList; j++){
			if(arr[i] < arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return arr;
}


/*
* Function:  sortSetBF()
* Return: float*
*
* Description:
* Sorts for the offline best fit bin packing
* It sorts the items in the bin from largest
* to the smallest for processing.
*
*/
float* sortSetBF(float* arr, infoP info){
	int i, j;
	float temp;
	for(i = 0; i < info->sizeList; i++){
		for(j = 0; j < info->sizeList; j++){
			if(arr[i] > arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return arr;
}