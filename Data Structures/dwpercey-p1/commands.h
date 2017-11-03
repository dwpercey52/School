#ifndef commands
#define commands
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "fileRead.h"

  /*************************************************************** 
  Student Name: Darrell Percey
  File Name: commands.h
  Assignment number 
  this file holds most of the functions for each of the 
  actions that we are suppose to simulate.
  This also holds the struct that I use for all Dircs and Files
***************************************************************/
  
  
  
  //Parent and Child point up and down
  //Sibling for a list in same level
  //Name for the dic name and point for file names
  typedef struct Node {
	  struct Node* ParentDir;
	  struct Node* ChildDir;
	  struct Node* SibDir;
	  char NodeName[100];
	  char Files[25][100];
  } Node; 
  
  Node* rootFunc();
  Node* execCommand(int x, Node* current);
  Node* cdupFunc(Node* current);
  Node* findDir(char *name, Node* current);
  Node* findSibDir(char *name, Node* current);
  Node* cddownFunc(char* name, Node* current);
  Node* rootStart(Node* current);
  int checkDir(char *name, Node* current);
  int searchFile(char* item, Node* current);
  void whereis(char* name, Node* current);
  void cpFunc(char* oldName, char* newName, Node* current);
  void rmFunc(char* name, Node* current);
  void sortDirc(Node* current);
  void sortFiles(Node* current);
  void pwdFunc(Node* current);
  void mkdirFunc(char *name, Node* current);
  void mvFunc(char *oldName, char *newName, Node* current);
  void lsFunc(Node* current);
  void addfFunc(char* newFile, Node* current);
#endif
