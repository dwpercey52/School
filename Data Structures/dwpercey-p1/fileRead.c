#include "fileRead.h"
/*************************************************************** 
  Student Name: Darrell Percey
  File Name: fileRead.c
  Assignment number 1
***************************************************************/

//Takes the command string and compares for the required action
//Assigns a number for command and returns it 
int commandRead(char *test, FILE *fp){
	int commandNum = 0;
	
	if(strcmp(test,"ls")==0){
		printf("$ ls \n");
		commandNum = 1;
	}
	else if(strcmp(test,"mkdir")==0){
		fscanf(fp,"%s",Str2);
		printf("$ mkdir %s \n",Str2);
		commandNum = 2;
	}
	else if(strcmp(test,"cd")==0){
		fscanf(fp,"%s",Str2);
		printf("$ cd %s \n",Str2);
		commandNum = 3;
	}
	else if(strcmp(test,"pwd")==0){
		printf("$ pwd \n");
		commandNum = 4;
	}
	else if(strcmp(test,"addf")==0){
		fscanf(fp,"%s",Str2);
		printf("$ addf %s \n",Str2);
		commandNum = 5;
	}
	else if(strcmp(test,"mv")==0){
		fscanf(fp,"%s", Str2);
		fscanf(fp,"%s", Str3);
		printf("$ mv %s %s \n", Str2, Str3);
		commandNum = 6;
	}
	else if(strcmp(test,"cp")==0){
		fscanf(fp,"%s", Str2);
		fscanf(fp,"%s", Str3);
		printf("$ cp %s %s \n", Str2, Str3);
		commandNum = 7;
	}
	else if(strcmp(test,"rm")==0){
		fscanf(fp,"%s", Str2);
		printf("$ rm %s \n", Str2);
		commandNum = 8;
	}
	else if(strcmp(test,"bye")==0){
		printf("$ bye \n");
		commandNum = 9;
	}
	else if(strcmp(test,"whereis")==0){
		fscanf(fp,"%s",Str2);
		printf("$ whereis %s  \n", Str2);
		commandNum = 10;
	}
	else{
		printf("Command not valid \n");
	}	
	
	return commandNum;
	}

