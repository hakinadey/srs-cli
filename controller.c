#include "srs.h"

/**
 * student_add - controller to add a student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_add(student_t **list, char *argument)
{
  char first_name[50];
  char last_name[50];

  printf("First Name: ");
  fgets((char *restrict)&first_name, sizeof(first_name), stdin);

  printf("Last Name: ");
  fgets((char *restrict)&last_name, sizeof(last_name), stdin);

  first_name[strcspn(first_name, "\n")] = 0;
  last_name[strcspn(last_name, "\n")] = 0;

  add_student(list, 0, first_name, last_name);
}

/**
 * student_print_all - controller to list all students
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_print_all(student_t **list, char *argument)
{
  int count = argument == NULL ? 0 : atoi(argument);
  print_students(*list, count);
}

/**
 * student_print_one - controller to list one student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_print_one(student_t **list, char *argument)
{
  int roll_number = argument == NULL ? 0 : atoi(argument);
  if (!argument || (roll_number == 0 && argument[0] != 0))
  {
    printf("Please provide a valid roll number\n");
    return;
  }

  student *student_data = find_student_by_roll_number(*list, roll_number);

  if (student_data == NULL)
  {
    printf("Student with roll number %d does not exist\n", roll_number);
    return;
  }

  printf("**********************************************\n");
  printf("*************** Personal Details *************\n");
  printf("First Name: %s\n", student_data->first_name);
  printf("Last Name: %s\n", student_data->last_name);
  printf("Roll Number: %d\n", student_data->roll_number);

  printf("\n*************** Academic Details *************\n");

  printf("\n**********************************************\n");
}

/**
 * student_remove_one - controller to remove one student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_remove_one(student_t **list, char *argument)
{
  int roll_number = argument == NULL ? 0 : atoi(argument);
  if (!argument || (roll_number == 0 && argument[0] != 0))
  {
    printf("Please provide a valid roll number\n");
    return;
  }

  remove_student_by_roll_number(list, roll_number);
}

/**
 * student_find - controller to find students given a search query
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_find(student_t **list, char *argument)
{
  const char *query = argument == NULL ? "" : argument;
  find_students_by_query(*list, query);
}
