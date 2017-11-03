#include <stdio.h>
#include <string.h>


int main (void)  {


char apple[10];
char orange[10];

scanf("%s",&apple);
scanf("%s",&orange);

if (strcmp(apple, orange) > 0 ) {
printf("apple");
}
else {
printf("no");
} 

}