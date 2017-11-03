/***************************************************************/
/* Darrell Percey				                               */
/* OnlineSet.c                                                 */
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
#include "OnlineSet.h"

/*
* Function:  onlineFirstFit()
* Return: binP
*
* Description:
* Does the first fit bin packing. Reads from
* the array one at a time finding the first
* avaliable bin to place
* 
*
*/
binP onlineFirstFit(infoP info){
	int i = 0;
	int j, m;
	binP head = createNewBinNode();
	binP current = head;
	
	addToBin(current, info->totalList[i]);
	
	
	for(i = 1; i < info->sizeList; i++){
		j = 0;
		m = 0;
		
		if((info->totalList[i] + current->currentSize) < info->maxSize){
			addToBin(current, info->totalList[i]);
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
				if(info->totalList[i] + current->currentSize < info->maxSize){
					addToBin(current, info->totalList[i]);
					m++;
					j++;
				}
			}
		}
		
		if(m == 0){
			current->next = createNewBinNode();
			current = current->next;
			addToBin(current,info->totalList[i]);
		}
		current = head;
	}
	
	return head;
}


/*
* Function:  onlineNextFit()
* Return: binP
*
* Description:
* Does the next fit bin packing. Reads from
* array and tries to place in current bin.
* If the current bin is full it makes a new bin.
* 
*
*/
binP onlineNextFit(infoP info){
	int i;
	binP head = createNewBinNode();
	binP current = head;
	
	for(i = 0; i < info->sizeList; i++){
		if((info->totalList[i] + current->currentSize) < info->maxSize){
			addToBin(current, info->totalList[i]);
		}
		else{
			current->next = createNewBinNode();
			current = current->next;
			addToBin(current,info->totalList[i]);
		}
	}
	
	return head;
}


/*
* Function:  onlineBestFit()
* Return: binP
*
* Description:
* Does the best fit packing. Reads from the
* array and tries to calcualte which bin is best. 
* It does so by comparing if it can fit and if the
* current size would pack it more.
*
*/
binP onlineBestFit(infoP info){
	int i, j;
	binP head = createNewBinNode();
	binP current = head;
	binP best = head;
	
	for(i = 0; i < info->sizeList; i++){
		j = 0;
		while(j == 0){
			if(current->next != NULL){
				current = current->next;
				if((info->totalList[i] + current->currentSize) < info->maxSize){
					if(current->currentSize > best->currentSize || best->currentSize + info->totalList[i] > info->maxSize){
						best = current;
					}
				}
			}
			else{
				j++;
			}
		}
		
		if(best->currentSize + info->totalList[i] > info->maxSize){
			current->next = createNewBinNode();
			current = current->next;
			addToBin(current,info->totalList[i]);
		}
		else{
			addToBin(best, info->totalList[i]);
		}
		current = head;
		best = head;
	}
	return head;
}

