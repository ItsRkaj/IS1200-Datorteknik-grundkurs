
// Assignment 3
// Task 2: heap


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int numbersInRow = 0;

void print_number (int n) {
  printf ("%10d", n);
  numbersInRow++;
  if (numbersInRow % COLUMNS == 0) {
    printf ("\n");
  }
}
void print_sieves(int n){
  char *A = malloc(n*sizeof(char));
  int i;
  for (i = 2; i <= n; i++) {                  
      A[i] = 1;
  }

  for (i = 2; i <= sqrt(n); i++) {      
    if (A[i]) {                          
        for (int j = i; i*j <= n; j++) { 
            A[i*j] = 0;                 
        } 
    }
  }
  for (i = 2; i <= n; i++) {            
      if (A[i]) {
          print_number(i);
      }
  }
  free(A);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
