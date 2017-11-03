#include "commands.h"

/*************************************************************** 
  Student Name: Darrell Percey
  File Name: commands.c
  Assignment number 1
***************************************************************/

/*This is the commands.c file which contains most of the commands made into functions
There is also some functions in here that allow for the functions to work in a more modular
way. Such as searchDir or searchFile functions. These can be called in multiple situations */



//starts the program with a root folder
//this is parent to null as it is top level

Node* rootFunc(){
	Node* temp = malloc(sizeof(Node));
	strcpy(temp->NodeName, "root");
	temp->ParentDir = NULL;
	temp->ChildDir = NULL;
	temp->SibDir = NULL;
	return temp;
}

//checks to see if a directory with the same name
// exist current and returns a value

int checkDir(char *name, Node* current){
	int i = 0;
	while(current != NULL){
		if(strcmp(name,current->NodeName) == 0){
			i++;
		}
		current = current->SibDir;
	}
	return i;
}

//finds a node with the same name
Node* findDir(char *name, Node* current){
	Node* temp;
	int y =0;
	
	while(y == 0){
		if(current->SibDir == NULL){
			if(strcmp(name,current->NodeName) == 0){
				temp = current;
				return temp;
			}
			return NULL;
		}
		else if (strcmp(name, current->NodeName) == 0 ){
			temp = current;
			return temp;
		}
		current = current->SibDir;
	}
	return NULL;
}

//similar to the function above, this places the spot right before
// the node we are looking for so we can pass this value to rmFunc
Node* findSibDir(char *name, Node* current){
	Node* temp;
	int y =0;
	
	while(y == 0){
		
		if(current->SibDir == NULL){
			return NULL;
		}
		else if (strcmp(name, current->SibDir->NodeName) == 0){
			temp = current;
			return temp;
		}
		current = current->SibDir;
	}
	return NULL;
}

// searches the files for a name that matches 
// the passed in name.
int searchFile(char* item, Node* current){
	int i = 0;
	int y = 0;
	int t = 0;
	while(y == 0){
		if(strlen(current->Files[i]) != 0){
			if(strcmp(current->Files[i],item) == 0){
				y++;
				t = i;
				return t;
			}
			i++;
		}
		else{
			y++;
		}
	}
	return 100;
}



void rmFunc(char* name, Node* current){
	int i = 0;
	int x = 0;
	char tempC[100];
	Node* tempN;
	
	i = searchFile(name, current);
	if(i != 100){
		if(strlen(current->Files[i+1]) == 0){
			strcpy(current->Files[i], "\0");
		}
		else{
			while(strlen(current->Files[i+1]) != 0 ){
				strcpy(tempC, current->Files[i+1]);
				strcpy(current->Files[i+1], "\0");
				strcpy(current->Files[i], tempC);
				i++;
				
			}
		}
	}
	else{
		if(current->ChildDir != NULL){
			if(strcmp(name,current->ChildDir->NodeName) == 0){
				current->ChildDir = current->ChildDir->SibDir;
			}
			else{
				tempN = findSibDir(name,current->ChildDir);
				if(tempN != NULL){
					tempN->SibDir = tempN->SibDir->SibDir;
				}
				else
					x++;
			} 
		}
		else
			x++;
	}
	if(x == 1){
		printf("%s is not in :",name);
		pwdFunc(current);
		printf("\n");
	}
}
	
//sends to sendFile func first to see if a file is named that
//if not it returns 100 and it looks for a dirc with the name
// if neither have the name it will display nothing


void mvFunc(char *oldName, char *newName, Node* current){
	int i;
	int y = 0;
	int t = 0;
	Node* temp;
	Node* temp2;
	
	i = searchFile(oldName,current);
	if(i == 100){
		if(current->ChildDir != NULL){
			temp = findDir(oldName, current->ChildDir);
			temp2 = findDir(newName, current->ChildDir);
			if(temp != NULL && temp2 == NULL){
				strcpy(temp->NodeName,newName);
			}
			else if(temp2 != NULL){
		//		printf("Already a thingy \n");
			}
			else if(temp == NULL){
			//	printf("there is no thingy \n");
			}	
		}	
	}
	else{
		while(y == 0){
			if(strlen(current->Files[t]) != 0){
				if(strcmp(current->Files[t], newName) == 0){
					y++;
				}
				t++;
			}
			else if(i != 100){
				strcpy(current->Files[i], newName);
				y++;
			}
			else{
				y++;
			}
		}
	sortFiles(current);
	}
}

//sets up a temp node to place holding
//checks for a current child dirc
//places new dirc in child or sib of child

 void mkdirFunc(char *name, Node* current) {
	int i;
	
	Node* temp = malloc(sizeof(Node));
	strcpy(temp->NodeName, name);
	temp->ParentDir = current;
	temp->ChildDir = NULL;
	temp->SibDir = NULL;
	if(current->ChildDir == NULL){
		current->ChildDir = temp;
		printf("%s \n",name);
	}
	else{
		i= checkDir(name,current->ChildDir);
		if(i == 0){
			current = current->ChildDir;
			while(current->SibDir != NULL){
				current = current->SibDir;
			}
			current->SibDir = temp;
			printf("%s \n",name);
		}
		else{
			printf("Already a directory with that name. \n");
		}
	}
} 


// list all the files in the directory
//then it checks to see if children dircs are linked

void lsFunc(Node* current){
	int i = 0;
	while(strlen(current->Files[i]) != 0){
		printf("F %s \n",current->Files[i]);
		i++;
	}
	if(current->ChildDir != NULL){
		current = current->ChildDir;
		while(current != NULL){
			printf("D %s \n", current->NodeName);
			current = current->SibDir;
		}
	}
}

//adds a file to the current dirc

void addfFunc(char* newFile, Node* current){
	int i = 0;
	int y = 0;
	while(y == 0){
		if(strlen(current->Files[i]) != 0){
			if(strcmp(current->Files[i],newFile) == 0){
				printf("Already a file with that name. \n");
				y++;
			}
			i++;
		}
		else{
			strcpy(current->Files[i], newFile);
			y++;
		}
	}
	sortFiles(current);
}


//called when adding files and when editing names
//sorts the files in alphabetical order

void sortFiles(Node* current){
	int i, j = 0;
	char temp[30];
	
	for (i = 1; i < 10; i++) {
		for (j = 1; j < 25; j++) {
			if (strcmp(current->Files[j-1], current->Files[j]) > 0) {
				if(strlen(current->Files[j-1]) != 0 && strlen(current->Files[j]) != 0){
					strcpy(temp, current->Files[j - 1]);
					strcpy(current->Files[j - 1], current->Files[j]);
					strcpy(current->Files[j], temp);
				}
			}
		}
	}
}


//sorts the directories in alphabetical order

void sortDirc(Node* current){
	int i = 0; 
	int j = 0;
	char temp[30];
	Node* tempN;
	
	if(current->ChildDir != NULL){
		tempN = current->ChildDir;
		while(tempN->SibDir != NULL){
			i++;
			tempN = tempN->SibDir;
		}
		tempN = current->ChildDir;
		while(j != i ){
			while(tempN->SibDir != NULL){
				if (strcmp(tempN->NodeName, tempN->SibDir->NodeName) > 0) {
					if(strlen(tempN->NodeName) != 0 && strlen(tempN->SibDir->NodeName) != 0){
						strcpy(temp, tempN->NodeName);
						strcpy(tempN->NodeName, tempN->SibDir->NodeName);
						strcpy(tempN->SibDir->NodeName, temp);
					}
				}
				tempN = tempN->SibDir;
			}
			j++;
			tempN = current->ChildDir;
		}	
	}
}

// this will check if in the root folder first
//if not in root, it will go up a level in dirc

Node* cdupFunc(Node* current){
	if(current->ParentDir == NULL){
		printf("Cannot access above this point. \n");
	}
	else{
		current = current->ParentDir;
		pwdFunc(current);
		printf("\n");
	}
	return current;
}

//this func does the oppisite as the above
//it goes down in the dirc of the name that is 
// picked

Node* cddownFunc(char* name, Node* current){
	Node* temp;
	if(current->ChildDir == NULL){
		printf("%s is not located in %s \n", name, current->NodeName);
		return current;
	}
	temp = findDir(name, current->ChildDir);
	if(temp == NULL){
		printf("%s is not located in %s \n", name, current->NodeName);
		return current;
	}
	else{
		current = temp;
		pwdFunc(current);
		printf("\n");
		return current;
	}
}

void cpFunc(char* oldName, char* newName, Node* current){
	int i;
	Node* temp;
	Node* temp2;
	
	i = searchFile(oldName,current);
	if(i == 100){
		if(current->ChildDir != NULL){
			temp = findDir(oldName, current->ChildDir);
			temp2 = findDir(newName, current->ChildDir);
			if(temp != NULL && temp2 == NULL){
				mkdirFunc(newName, current);
			}
			else if(temp2 != NULL){
				printf("Already an item with that name. \n");
			}
			else if(temp == NULL){
				printf("There is no items with that name. \n");
			}	
		}	
	}
	else{
		i = searchFile(newName, current);
		if(i == 100){
			addfFunc(newName,current);
		}
		else{
			printf("Already an item with that name. \n");
		}
	sortFiles(current);
	} 
}



void whereis(char* name, Node* current){
	Node* temp;
	int i;
	if(current->ChildDir != NULL){
		whereis(name, current->ChildDir);
		temp = findDir(name, current->ChildDir);
		if(temp != NULL){
			temp = temp->ParentDir;
			printf("%s is located in :",name);
			pwdFunc(temp);
			printf("\n");
		}
	}
	if(current->SibDir != NULL){
		whereis(name, current->SibDir);
	}
	i = searchFile(name, current);
	if( i != 100){
		printf("%s is located in :",name);
		pwdFunc(current);
		printf("\n");
	}
}


//used to take the whereis function to the top of
//the directories so it can scan all
Node* rootStart(Node* current){
	while(current->ParentDir != NULL){
		current = current->ParentDir;
	}
	return current;
}


//recursion to show the current directory

void pwdFunc(Node* current){
	if(current->ParentDir != NULL){
		pwdFunc(current->ParentDir);
	}
	printf("%s/",current->NodeName);
}

//Execute the commands given what the fileRead func sends

Node* execCommand(int x, Node* current){
	Node* temp;
	
	if (x == 1){
		lsFunc(current);
	}
	else if(x == 2){
		mkdirFunc(Str2, current);
		sortDirc(current);
	}
	else if(x == 3){
		if(strcmp(Str2,"..")==0){
			current = cdupFunc(current);
		}	
		else{
			current = cddownFunc(Str2, current);
		}
	}
	else if(x == 4){
		pwdFunc(current);
		printf("\n");
	}
	else if(x == 5){
		addfFunc(Str2, current);	
	}
	else if(x == 6){
		mvFunc(Str2, Str3, current);
		sortDirc(current);
		sortFiles(current);
	}
	else if(x == 7){
		cpFunc(Str2, Str3, current);
		sortDirc(current);
		sortFiles(current);
	}
	else if(x == 8){
		rmFunc(Str2,current);
		sortFiles(current);
	}
	else if(x == 10){
		temp = rootStart(current);
		whereis(Str2, temp);
	}
	
	return current;
	
}