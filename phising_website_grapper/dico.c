#include <stdio.h>
#include <string.h>

int main() {
  // Create an integer variable that will store the number we get from the user
  char myDomain[50];
  char* Bool = "True";

  printf("[/!\\] Enter a domain name and check if it is already listed as a phising site.\n");
  printf("[/!\\] If you want to quit this programm type 'quit' in the command line.\n");
  while (Bool == "True")
    {
      printf("Enter a domain name : \n"); 
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