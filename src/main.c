#include "srs.h"

int main(int argc, char *argv[])
{
  init_program();
  char *students_filename = "data/students.csv";
  char *courses_filename = "data/courses.csv";

  if (argc > 1)
    students_filename = argv[1];
  if (argc > 2)
    courses_filename = argv[2];

  student_t *students = NULL;
  load_students_from_csv(&students, students_filename);

  course_t *courses = NULL;
  load_courses_from_csv(&courses, courses_filename);

  char input[255];
  char *command;
  while (1)
  {
    printf(">>> ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
      perror("Could not read input\n");
      continue;
    }
    input[strcspn(input, "\n")] = 0;

    command = strtok(input, " ");
    if (command == NULL)
      continue;

    if (strcmp(command, "exit") == 0)
    {
      empty_students_list(&students);
      empty_courses_list(&courses);
      break;
    }

    if (strcmp(command, "save") == 0)
    {
      char *first_argument = strtok(NULL, " ");
      char *second_argument = strtok(NULL, " ");
      char *students_filename = first_argument == NULL ? "data/students.csv" : first_argument;
      char *courses_filename = second_argument == NULL ? "data/courses.csv" : second_argument;

      save_students_to_csv(students, students_filename);
      save_courses_to_csv(courses, courses_filename);
      continue;
    }

    if (strcmp(command, "load") == 0)
    {
      char *first_argument = strtok(NULL, " ");
      char *second_argument = strtok(NULL, " ");
      char *students_filename = first_argument == NULL ? "data/students.csv" : first_argument;
      char *courses_filename = second_argument == NULL ? "data/courses.csv" : second_argument;

      load_students_from_csv(&students, students_filename);
      load_courses_from_csv(&courses, courses_filename);
      continue;
    }

    if (strcmp(command, "student") == 0)
    {
      char *subcommand = strtok(NULL, " ");
      char *argument = strtok(NULL, " ");
      controller_t controllers[] = {
          {"add", student_add},
          {"list", student_print_all},
          {"show", student_print_one},
          {"remove", student_remove_one},
          {"find", student_find},
          {"sort", student_sort},
          {"save", student_save},
          {"load", student_load},
          {NULL, NULL},
      };

      int i = 0;
      while (controllers[i].command)
      {
        if (strcmp(subcommand, controllers[i].command) == 0)
        {
          controllers[i].function(&students, &courses, argument);
          break;
        }
        i++;
      }
      if (!controllers[i].command)
        show_student_help();
    }
    else if (strcmp(command, "course") == 0)
    {
      char *subcommand = strtok(NULL, " ");
      char *argument = strtok(NULL, " ");
      controller_t controllers[] = {
          {"add", course_add},
          {"remove", course_remove},
          {NULL, NULL},
      };

      int i = 0;
      while (controllers[i].command)
      {
        if (strcmp(subcommand, controllers[i].command) == 0)
        {
          controllers[i].function(&students, &courses, argument);
          break;
        }
        i++;
      }
      if (!controllers[i].command)
        show_course_help();
    }
    else
      print_usage();
  }
}

void init_program(void)
{
  char name[100];

  if (!fopen("data/students.csv", "r"))
  {
    FILE *students_file = fopen("data/students.csv", "w");
    if (!students_file)
    {
      perror("Could not create students file\n");
      exit(EXIT_FAILURE);
    }
    fclose(students_file);
  }

  if (!fopen("data/courses.csv", "r"))
  {
    FILE *courses_file = fopen("data/courses.csv", "w");
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
  printf("    save [students_filename] [courses_filename]\n");
  printf("    load [students_filename] [courses_filename]\n");
  printf("    student [COMMAND] [OPTIONS]\n");
  printf("    course [COMMAND] [OPTIONS]\n");

  printf("\nDESCRIPTION\n");
  printf("    This program allows you to manage student records and their courses using a shell prompt. ");
  printf("You can add, remove, display, list, sort, and search for students and courses. ");
  printf("The program runs in an infinite loop until 'exit' is entered.\n");

  printf("\nCOMMANDS\n");
  printf("    save [students_filename] [courses_filename]\n");
  printf("        Save data to files.\n");
  printf("    load [students_filename] [courses_filename]\n");
  printf("        Load data from files.\n");
  printf("    student help\n");
  printf("        Displays help page for student commands.\n");
  printf("    course help\n");
  printf("        Displays help page for course commands.\n");
  printf("    exit\n");
  printf("        Exits the program.\n");
}
