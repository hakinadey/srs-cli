#include "srs.h"

int ROLL_NUMBER = 1;

int main(int argc, char *argv[])
{
  init_program();
  char *students_filename = "students.csv";
  char *courses_filename = "courses.csv";

  if (argc > 1)
    students_filename = argv[1];
  if (argc > 2)
    courses_filename = argv[2];

  student_t *students = NULL;
  load_students_from_csv(&students, students_filename);

  course_t *courses = NULL;
  load_courses_from_csv(&courses, courses_filename);

  save_students_to_csv(students, "students.csv");
  save_courses_to_csv(courses, "courses.csv");
}

void init_program(void)
{
  char name[100];

  if (!fopen("students.csv", "r"))
  {
    FILE *students_file = fopen("students.csv", "w");
    if (!students_file)
    {
      perror("Could not create students file\n");
      exit(EXIT_FAILURE);
    }
    fclose(students_file);
  }

  if (!fopen("courses.csv", "r"))
  {
    FILE *courses_file = fopen("courses.csv", "w");
    if (!courses_file)
    {
      perror("Could not create courses file\n");
      exit(EXIT_FAILURE);
    }
    fclose(courses_file);
  }

  printf("*************************************\n");
  printf("**** Student Record System (SRS) ****\n");
  printf("*************************************\n\n");

  printf("Please enter your name: ");
  fgets((char *restrict)&name, sizeof(name), stdin);

  printf("\nWelcome, %s\n", name);
  print_usage();
}

void print_usage(void)
{
  printf("Student Record System (SRS) - Manage student records and their courses interactively\n");

  printf("\nSYNOPSIS\n");
  printf("    student [COMMAND] [OPTIONS]\n");
  printf("    course [COMMAND] [OPTIONS]\n");

  printf("\nDESCRIPTION\n");
  printf("    This program allows you to manage student records and their courses using a shell prompt. ");
  printf("You can add, remove, display, list, sort, and search for students and courses. ");
  printf("The program runs in an infinite loop until 'exit' is entered.\n");

  printf("\nCOMMANDS\n");
  printf("    student help\n");
  printf("        Displays help page for student commands.\n");
  printf("    course help\n");
  printf("        Displays help page for course commands.\n");
  printf("    exit\n");
  printf("        Exits the program.\n");
}
