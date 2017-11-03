/************************
*Name: Darrell W. Percey*
*File: FileRun.h		*
*For: Project 1			*
*						*
*************************/


#ifndef FileCheck
#define FileCheck
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELENGTH 100
#define HASHLENGTH 5000
#define HASHINFOLENGTH 20100
#define SENTENCESTORAGE 20100
  
	
	typedef struct FileNode* FileNodeP;
	typedef struct HashInfo* HashInfoP;
	
	
	/*
	* Function:  hashCode()
	*
	* Description:
	* Takes in a data string and sums the ASCII values
	* of all the letters and multiples in an i++ fashion.
	*
	*/
	
		
	int hashCode(char* key);
	
	
	/*
	* Function:  getWordCount()
	*
	* Description:
	* Ask for the user to input an amount of words they want to compare
	* range can be from 2 to 10 and it has error checking.
	* It returns the value back to main for phraseSize
	* 
	*/
	
	
	int getWordCount();
	
	
	/*
	* Function:  newFileNode(char*)
	*
	* Description:
	* This allocates memeory needed for a new FileNode
	* Also returns the temp node back to a pointer for FileNode
	*
	*/
	
	
	FileNodeP newFileNode(char* name);
	
	
	/*
	* Function:  addNewFileNode(char*, FileNodeP)
	*
	* Description:
	* This adds a FileNode to the end of he linked listed FileNodes
	* Finds the end then allocates memeory using newFileNode()
	*
	*/
	
	
	void addNewFileNode(char* name, FileNodeP top);
	
	
	/*
	* Function: newHashNode(char*) 
	*
	* Description:
	* Allocates the memeory for a hashNode and stores the data
	* into it for comparsion later. Returns the pointer to a 
	* HashInfoP in the FileNode array
	*
	*/
	
	
	HashInfoP newHashNode(char* data);
	
	
	/*
	* Function:  addNewFileNode(char* HashInfoP)
	*
	* Description:
	* If there is a collision this function is called
	* it will add the new node to the end of the HashInfo
	* linked list.
	*
	*/
	
	
	void addNewHashNode(char* data, HashInfoP top);
	
	
	/*
	* Function:  readFilesIn(FileNodeP)
	*
	* Description:
	* Reads the entire string in the file into an string
	* array for easier access and for easy of change.
	*
	*/
	
	void readFilesIn(FileNodeP top);
	
	
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
	
	
	FileNodeP getFiles();
	
	/*
	* Function:  freeNodes(FileNodeP)
	*
	* Description:
	* Frees all the memeory allocated in the FileNode
	* and all the HashNodes that are connected to that
	* FileNode.
	*
	*/
	
	
	FileNodeP freeNodes(FileNodeP current);
	
	
	/*
	* Function:  hashFileContent(int, FileNodeP)
	*
	* Description:
	* This breaks the file string into phrases of user picked
	* sizes and stores them in the HashTable array inside of
	* the FileNode structure by passing it to placeHash().
	*
	*/
	
	
	void hashFileContent(int phraseSize, FileNodeP file);
	

	/*
	* Function: placeHash(char* FileNodeP) 
	*
	* Description:
	* Places the data and in the corresponding FileNode's
	* hashtable array in the position of the hashKey that
	* is found from hashCode()
	*
	*/

	
	void placeHash(char* data, FileNodeP file);
	
	
	/*
	* Function: compareFiles(int, FileNodeP) 
	*
	* Description:
	* This function takes in the top file and compares all other files
	* to that orignial one. Then it will call to free the memory and move
	* to the next file. In doing so it will then compare that file to the rest.
	* Essentially it is a queue type moving down the list.
	*/
	
	
	void compareFiles(int phraseSize, FileNodeP files);
	
	
	/*
	* Function:  compareWords(int, FileNodeP, FileNodeP)
	*
	* Description:
	* Compares the words of to the two files passed in
	* and then returns a value of the amount of phrases
	* that were the same.
	*
	*/
	
	
	int compareWords(int phraseSize, FileNodeP current, FileNodeP compareFile);
	
  
  
  
#endif
  