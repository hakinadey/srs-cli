#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char name[100];

  printf("*******************************\n");
  printf("Student Record System\n");
  printf("*******************************\n\n");

  printf("Please enter your name: ");
  fgets((char * restrict)&name, sizeof(name), stdin);

  printf("Welcome, %s\n\n", name);
}
