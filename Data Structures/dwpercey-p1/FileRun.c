/************************
*Name: Darrell W. Percey*
*File: FileRun.c		*
*For: Project 1			*
*						*
*************************/

#include "FileCheck.h"

	/*
	* Function:  main()
	*
	* Description:
	* Executes functions to compare files
	*
	*/
	
int main(){
	int wordCount;
	
	wordCount = getWordCount();
	FileNodeP fileList = getFiles();
	readFilesIn(fileList);
	compareFiles(wordCount, fileList);
	return 0;
	
}
	
