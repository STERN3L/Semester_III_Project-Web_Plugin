#include <stdio.h>

int main() {
  // Create an integer variable that will store the number we get from the user
  int myNum;
  char Bool = "True";

   while (Bool == "True")
    {
        printf("Type a number and press enter: \n"); 
        scanf("%d", &myNum);
        if (myNum = 5){
            Bool = "False";
        }
        printf("Your number is: %d", myNum);
    }

  // Print the number the user typed

  return 0;
}