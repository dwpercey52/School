#ifndef fileRead
#define fileRead
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "commands.h"

	// Hold the Command-Name
	char Str1[100];
	char Str2[100];
	char Str3[100];

	//Case function for cmds
	int commandRead(char *test, FILE *fp);
#endif
