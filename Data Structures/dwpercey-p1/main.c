#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileRead.h"
#include "commands.h"

/*************************************************************** 
  Student Name: Darrell Percey
  File Name: Main.c
  Assignment number 1
***************************************************************/

int main() {
	Node* currentDir = rootFunc();
	FILE *fp;
	fp = fopen("commands.txt","r");
	int x = 0;
	printf("Programmed by Darrell Percey \n");
	
	while(x != 9){
		fscanf(fp,"%s",Str1);
		x=commandRead(Str1, fp);
		currentDir = execCommand(x, currentDir);
	}
	
	return 0;
}

