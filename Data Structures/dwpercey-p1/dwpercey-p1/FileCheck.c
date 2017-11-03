/************************
*Name: Darrell W. Percey*
*File: FileCheck.c		*
*For: Project 1			*
*						*
*************************/

//All functions for FileRun.c


#include "FileCheck.h"

/*************
* Structures *
**************/

	struct FileNode {
		char fileName[NAMELENGTH];
		char fileWords[SENTENCESTORAGE];
		HashInfoP fileHash[HASHLENGTH];
		FileNodeP next;
	} FileNode;

	
	struct HashInfo{
		HashInfoP next;
		char data[HASHINFOLENGTH];
	} HashInfo;
	
	int fileCount = 0;
	
/*************
* Structures *
* End        *
**************/
	
	
	/*
	* Function:  hashCode()
	*
	* Description:
	* Takes in a data string and sums the ASCII values
	* of all the letters and multiples in an i++ fashion.
	*
	*/
	
	int hashCode(char* key){
		long int sum = 0;
		int length = strlen(key);
		int i;
	
		for(i = 0; i < length; i++){
			/* This is where the program will hang or freeze up
			*	it will start the loop for the length and just freeze
			*	as it hits the last loop.
			*/
			sum += (key[i]*(i+1));
		}
	
		return sum% HASHLENGTH;
	}
	
	
	
	
	/*
	* Function:  getWordCount()
	*
	* Description:
	* Ask for the user to input an amount of words they want to compare
	* range can be from 2 to 10 and it has error checking.
	* It returns the value back to main for phraseSize
	* 
	*/
	
	int getWordCount(){
		int i;
	  
		printf("How long of phrases would you like to compare?(2-10): ");
		scanf("%d",&i);
	  
		while(i > 10 || i < 2){
			printf("Please input a correct value from 2-10: ");
			scanf("%d",&i);
		}
		return i;
	}
	
	
    /*
	* Function:  newFileNode(char*)
	*
	* Description:
	* This allocates memeory needed for a new FileNode
	* Also returns the temp node back to a pointer for FileNode
	*
	*/
	
	FileNodeP newFileNode(char* name){
		FileNodeP temp = (FileNodeP) malloc(sizeof(FileNode));
		strcpy(temp->fileName,name);
		memset(temp->fileWords,'\0',sizeof(temp->fileWords));
		temp->next = NULL;
		return temp;
	}
	
	
	/*
	* Function:  addNewFileNode(char*, FileNodeP)
	*
	* Description:
	* This adds a FileNode to the end of he linked listed FileNodes
	* Finds the end then allocates memeory using newFileNode()
	*
	*/
	
	void addNewFileNode(char* name, FileNodeP top){
		FileNodeP newNode = newFileNode(name);
		FileNodeP temp = top;
		
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
	}
		
	
	/*
	* Function: newHashNode(char*) 
	*
	* Description:
	* Allocates the memeory for a hashNode and stores the data
	* into it for comparsion later. Returns the pointer to a 
	* HashInfoP in the FileNode array
	*
	*/
	
	HashInfoP newHashNode(char* data){
		HashInfoP temp = (HashInfoP) malloc(sizeof(HashInfo));
		strcpy(temp->data,data);
		temp->next = NULL;
		return temp;
	}

	
	/*
	* Function:  addNewFileNode(char* HashInfoP)
	*
	* Description:
	* If there is a collision this function is called
	* it will add the new node to the end of the HashInfo
	* linked list.
	*
	*/
	
	void addNewHashNode(char* data, HashInfoP top){
		HashInfoP newNode = newHashNode(data);
		HashInfoP temp = top;
		
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
	}
	
	
	/*
	* Function:  readFilesIn(FileNodeP)
	*
	* Description:
	* Reads the entire string in the file into an string
	* array for easier access and for easy of change.
	*
	*/
	
	void readFilesIn(FileNodeP top){
		int i = 0;
		int j = 0;
		FILE* file;
		char fileName[NAMELENGTH] = {'\0'};
		FileNodeP temp = top;
		
		while(j < fileCount){
			strcat(fileName,"./datafiles/");
			strcat(fileName,temp->fileName);
			//printf("%s \n",fileName);
			file = fopen(fileName,"r");
			if( !file ){
				printf("Couldn't open this file \n");
				exit(1);
			}
			
			while(!feof(file) && i < SENTENCESTORAGE){
				temp->fileWords[i++] = fgetc(file);
			}
			int m;
			for(m = i-1; m < SENTENCESTORAGE; m++){
				temp->fileWords[m] = '\0';
			}
			
			memset(fileName, '\0', sizeof(fileName));
			fclose(file);
			temp = temp->next;
			i = 0;
			j++;
		}
		
	}
	
	
	/*
	* Function:  freeNodes(FileNodeP)
	*
	* Description:
	* Frees all the memeory allocated in the FileNode
	* and all the HashNodes that are connected to that
	* FileNode.
	*
	*/
	
	FileNodeP freeNodes(FileNodeP current){
		FileNodeP temp;
		if(current->next != NULL){
			temp = current->next;
		}
		else{
			temp = NULL;
		}
		int i;
		for(i = 0; i < HASHLENGTH; i ++){
			free(current->fileHash[i]);
		}
		free(current);
		return temp;
		
	}
	
	
	/*
	* Function:   getFiles()
	*
	* Description:
	* Reads all the names of the files in the /datafiles/
	* directory and inputs those names into a file named
	* inputfile. Also stores the names of the files in the 
	* FileNodes to start an link list.
	*
	*/
	
	FileNodeP getFiles(){
		FILE* list;
		char name[NAMELENGTH];
		
		system("ls ./datafiles/ > inputfile.txt");
		list = fopen("inputfile.txt","r");
		
		if(!list){
			printf("File not found \n");
			printf("Closing the program \n");
			exit(1);
		}
		
		fgets(name,NAMELENGTH,list);
		name[strlen(name)-1] = '\0';
		FileNodeP top = newFileNode(name);
		fileCount++;
		
		while(fgets(name,NAMELENGTH,list) != NULL){
			name[strlen(name)-1] = '\0';
			addNewFileNode(name,top);
			fileCount++;
		}
		return top;
	}
	
	
	/*
	* Function:  hashFileContent(int, FileNodeP)
	*
	* Description:
	* This breaks the file string into phrases of user picked
	* sizes and stores them in the HashTable array inside of
	* the FileNode structure by passing it to placeHash().
	*
	*/
	
	
	void hashFileContent( int phraseSize, FileNodeP file){
		int i = 0;
		char* temp;
		char temp2[HASHINFOLENGTH];
		temp2[0] = '\0';
		
		temp = strtok(file->fileWords," ");
		while(temp != NULL){
			if(temp2[0] == '\0'){
				for(i = 0; i < phraseSize ; i++){
					if(temp != NULL){
						strcat(temp2,temp);
						strcat(temp2," ");
						if( i != phraseSize-1){
							temp = strtok(NULL," ");
						}
					}
				}	
			}
			else{
				i = 0;
				while(temp2[i] != ' '){
					i++;
				}
				int j;
				for(j = 0; j < strlen(temp2); j++){
					temp2[j] = temp2[i+1];
					i++;
				}
				strcat(temp2," ");
				strcat(temp2,temp);
				strcat(temp2," ");
				
			} 
			temp2[strlen(temp2) - 1] = '\0';
			temp = strtok(NULL," ");
			
			placeHash(temp2, file);
			//PROGRAM IS GETTING STUCK RIGHT HERE!
		}
	}
	
	
	/*
	* Function: placeHash(char* FileNodeP) 
	*
	* Description:
	* Places the data and in the corresponding FileNode's
	* hashtable array in the position of the hashKey that
	* is found from hashCode()
	*
	*/
	
	void placeHash(char* data, FileNodeP file){
		int hashKey = hashCode(data);
		
		if(file->fileHash[hashKey] == NULL){
			file->fileHash[hashKey] = newHashNode(data);
		}
		else{
			addNewHashNode(data, file->fileHash[hashKey]);
		}
	}
	
	
	/*
	* Function: compareFiles(int, FileNodeP) 
	*
	* Description:
	* This function takes in the top file and compares all other files
	* to that orignial one. Then it will call to free the memory and move
	* to the next file. In doing so it will then compare that file to the rest.
	* Essentially it is a queue type moving down the list.
	*/
	
	void compareFiles(int phraseSize, FileNodeP top){
		int i = 0;
		int j = 0;
		int m = 0;
		int comparedValue = 0;
		
		FileNodeP temp = top->next;
		printf("  ");
		for(j = 0; j < fileCount; j++){
			printf("      f%d",j+1);
		}
		printf("\n");
		int n;
		for(i = 0; i < fileCount; i++){
			hashFileContent(phraseSize, top);
			printf("\n");
			printf("f%d", i+1);
			for(n = 0; n < i+1; n++){
				printf("       -");
			}
			m = i+1;
			while(m < fileCount){
				comparedValue = compareWords(phraseSize, top, temp);
				if(temp->next != NULL){
					temp = temp->next;
				}
				printf("%8d", comparedValue);
				m++;
			}
			//comparedValue = compareWords(phraseSize, top, temp);
			//printf("    %d", comparedValue);
			printf("\n");
			
			if(top->next != NULL){
				top = freeNodes(top);
				if(top->next != NULL){
					temp = top->next;
				}
			}
		}
	}
	
	/*
	* Function:  compareWords(int, FileNodeP, FileNodeP)
	*
	* Description:
	* Compares the words of to the two files passed in
	* and then returns a value of the amount of phrases
	* that were the same.
	*
	*/
	
	int compareWords(int phraseSize, FileNodeP current, FileNodeP compareFile){
		int i = 0;
		int j;
		int comparedKey = 0;
		int samePhraseValue = 0;
		char* temp;
		char temptester[HASHINFOLENGTH];
		char temp2[HASHINFOLENGTH];
		HashInfoP tempNode;
		
		for(j = 0; j < strlen(compareFile->fileWords); j++){
			temptester[j] = compareFile->fileWords[j];
		}
		
		
		temp2[0] = '\0';
		
		temp = strtok(temptester," ");
		while(temp != NULL){
			if(temp2[0] == '\0'){
				for(i = 0; i < phraseSize ; i++){
					if(temp != NULL){
						strcat(temp2,temp);
						strcat(temp2," ");
						if( i != phraseSize-1){
							temp = strtok(NULL," ");
						}
					}

				//	printf("STRING 2: %st\n",temp2);
				}	
			
			}
			else{
				i = 0;
				while(temp2[i] != ' '){
					i++;
				}
				int j;
				for(j = 0; j < strlen(temp2); j++){
					temp2[j] = temp2[i+1];
					i++;
				}
				strcat(temp2," ");
				strcat(temp2,temp);
				strcat(temp2," ");
				//printf("STRING : %st\n",temp2);
				temp = strtok(NULL," ");
			} 
			
			temp2[strlen(temp2) - 1] = '\0';
			
			comparedKey = hashCode(temp2);
			tempNode = current->fileHash[comparedKey];
			
			if(tempNode != NULL){
				if(strcmp(tempNode->data, temp2) == 0){
					samePhraseValue++;
				}
				else if(tempNode->next != NULL){
					while(tempNode != NULL){
						if(strcmp(tempNode->data, temp2) == 0){
						samePhraseValue++;
						tempNode = tempNode->next;
						}
					}
					if(strcmp(tempNode->data, temp2) == 0){
					samePhraseValue++;
					}
				}
			}
		}
		return samePhraseValue;
	}