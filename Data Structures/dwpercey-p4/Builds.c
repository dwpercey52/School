/***************************************************************/
/* Darrell Percey				                               */
/* Builds.c                                                    */
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
#include "Builds.h"


/*
* Function:  createNewInfoNode()
* Return: infoP
*
* Description:
* Creates a new node for the information structure
* which holds all the bins for each of the packing
* algorithms.
*
*/
infoP createNewInfoNode(){
	infoP temp = (infoP) malloc(sizeof(information));
	temp = readFileInfo(temp);
	return temp;
}


/*
* Function:  readFileInfo()
* Return: infoP
*
* Description:
* Reads in the bin sizes from the top of the file
* then all the following will be floats for items.
* These are read into an array for easier handling.
*
*/
infoP readFileInfo(infoP temp){
	int i; 
	FILE *in = fopen("theItems.txt","r");
	if(!in){
		perror("Couldn't find file! \n");
		exit(1);
	}
	
	fscanf(in, "%d",&temp->maxSize);
	
	for(i = 0; i < LISTSIZE; i++){
		temp->totalList[i] = 0;
	}
	i = 0;
	fscanf(in, "%f", &temp->totalList[i]);
	while(temp->totalList[i] != 0){
		i++;
		fscanf(in, "%f", &temp->totalList[i]);
	}
	temp->sizeList = i;
	
	return temp;
}


/*
* Function:  createNewBinNode()
* Return: binP
*
* Description:
* Creates a new bin and works will all the algorithms
* FF, BF, NF both online and offline.
*
*/
binP createNewBinNode(){
	int i;
	binP temp = (binP) malloc(sizeof(bin));
	temp->totalItems = 0;
	temp->currentSize = 0.0;
	temp->next = NULL;
	
	for(i = 0; i < LISTSIZE; i++){
		temp->itemList[i] = 0.0;
	}
	
	return temp;
}


/*
* Function:  addToBin()
* Return: 
*
* Description:
* Adds an item to the bin, works will all bins.
* Increases bin size, the total items in the bin.
* and places the item into the array for look-up.
*
*/
void addToBin(binP bin,float item){
	bin->currentSize += item;
	bin->itemList[bin->totalItems] = item;
	bin->totalItems++;
}

/*
* Function:  printAllInfo()
* Return: 
*
* Description:
* Prints the table with the amount of bins used by
* each of the bin packings and then displays the
* size of each bin and the items in them.
*
*/
void printAllInfo(infoP info){
	printf("---------------------------------- \n");
	printf("| Online           |             | \n");
	printf("---------------------------------- \n");
	printf("| First Fit        |      %3d    | \n",calculateBinsUsed(info->OnFF));
	printf("---------------------------------- \n");
	printf("| Next Fit         |      %3d    | \n",calculateBinsUsed(info->OnNF));
	printf("---------------------------------- \n");
	printf("| Best Fit         |      %3d    | \n",calculateBinsUsed(info->OnBF));
	printf("---------------------------------- \n");
	printf("| Offline          |             | \n");
	printf("---------------------------------- \n");
	printf("| First Fit        |      %3d    | \n",calculateBinsUsed(info->OffFF));
	printf("---------------------------------- \n");
	printf("| Best Fit         |      %3d    | \n",calculateBinsUsed(info->OffBF));
	printf("---------------------------------- \n");
	
	
	printf("--------------------------Online--------------------------\n");
	printf("-----First Fit \n ");
	displayInformation(info->OnFF);
	printf("\n");
	printf("-----Next Fit \n");
	displayInformation(info->OnNF);
	printf("\n");
	printf("-----Best Fit \n");
	displayInformation(info->OnBF);
	printf("\n");
	printf("--------------------------Offline-------------------------- \n");
	printf("-----First Fit \n");
	displayInformation(info->OffFF);
	printf("\n");
	printf("-----Best Fit \n");
	displayInformation(info->OffBF);
	printf("\n");
}


/*
* Function:  displayInformation()
* Return: 
*
* Description:
* Prints the bins size and items in each bin for the 
* passed in bin packing head structure.
*
*/
void displayInformation(binP bin){
	binP hold = bin;
	binP temp = hold;
	int i = 0;
	int j = 0;
	
	i = 0;
	temp = hold;
	while(temp){
		printf("Bin#%d: %.3f  \n",i, temp->currentSize);
		printf("Item List: ");
		j = 0;
		while(temp->itemList[j] != 0){
			printf("[%.2f] ",temp->itemList[j]);
			j++;
		}
		printf("\n");
		if(temp->next != NULL){
			i++;
			temp = temp->next;
		}
		else{
			break;
		}
	}
}


/*
* Function:  calculateBinsUsed()
* Return: int
*
* Description:
* Finds the amount of bins used for the packing then
* returns the valuve to be displayed.
*
*/
int calculateBinsUsed(binP bin){
	binP hold = bin;
	binP temp = hold;
	int i = 1;
	
	while(temp){
		if(temp->next != NULL){
			i++;
			temp = temp->next;
		}
		else{
			break;
		}
	}
	return i;
}


/*
* Function:  freeMemory()
* Return: 
*
* Description:
* Frees the memory of each of the linked list
*
*/
void freeMemory(binP bin){
	binP temp;
	while(bin != NULL){
		temp = bin;
		bin = bin->next;
		free(temp);
	}
}