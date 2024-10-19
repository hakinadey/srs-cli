#include "srs.h"


int main(void) {
  int i = 0;
  int valid_command = 0;
  char name[100];
  char command[100];
  command_t commands[] = COMMANDS;


  printf("*******************************\n");
  printf("Student Record System\n");
  printf("*******************************\n\n");

  printf("Please enter your name: ");
  fgets((char * restrict)&name, sizeof(name), stdin);

  printf("Welcome, %s\n", name);
  printf("Usage: \n\n");
  printf("add: Add a student\n");
  printf("show: Display all students' information\n");
  printf("show <roll_number>: Display a student's information\n");
  printf("remove <roll_number>: Remove a student\n");
  printf("save: Save data to file\n\n");

  while (1) {
    valid_command = 0;
    printf(">>> ");
    fgets((char * restrict)&command, sizeof(command), stdin);
    if (strcmp(command, "exit\n") == 0) {
      exit(0);
    }
    while (commands[i].command) {
      if (strcmp(command, commands[i].command) == 0) {
        valid_command = 1;
        commands[i].function();
      }
      i++;
    }
    if (!valid_command) {
      printf("Please enter a valid command!\n");
    }
  }
}

void add_student(void) {
  printf("Adding student...\n");
}

void remove_student(void) {
  printf("Removing student...\n");
}
