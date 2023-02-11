#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

  printf("[/!\\] Enter a domain name and check if it is already listed as a phising site.\n");
  printf("[/!\\] If you want to quit this programm type 'quit' in the command line.\n");


  // Create an integer variable that will store the number we get from the user
  char myDomain[50];
  char* Bool = "True";

  //Open file
  FILE *f;
  char c;
  f = fopen("phising_site.txt","r");
  if (NULL == f){
    printf("[-] File can't be opened.\n");
  }
  printf("[+] File is loaded !\n");

/* Printing what is writtin in file
  do {
    c = fgetc(f);
    printf("%c", c);
  } while (c != EOF);
*/

  fclose(f);

  while (Bool == "True")
    {
      printf("[+] Enter a domain name : \n"); 
      scanf("%s", myDomain);
      if (strcmp(myDomain,"quit") == 0){
        printf("[/!\\] You leave the programm !");
        Bool = "False";
      }
      else{
        printf("Your domain name is : %s\n", myDomain);
      }
    }
  
  return 0;
}