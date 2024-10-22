#include "srs.h"

int ROLL_NUMBER = 1;

int main(int argc, char *argv[])
{
  init_program();
  char *students_file = "students.csv";
  char *courses_file = "courses.csv";

  if (argc > 1)
    students_file = argv[1];
  if (argc > 2)
    courses_file = argv[2];

  student_t *students = NULL;
  load_students_from_csv(&students, students_file);

  course_t *courses = NULL;
  load_courses_from_csv(&courses, courses_file);
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

  printf("Welcome, %s\n", name);
  printf("Usage: \n\n");
  printf("add: Add a student\n");
  printf("show: Display all students' information\n");
  printf("show <roll_number>: Display a student's information\n");
  printf("remove <roll_number>: Remove a student\n");
  printf("save: Save data to file\n\n");
}
