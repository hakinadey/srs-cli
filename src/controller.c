#include "srs.h"

/**
 * student_add - controller to add a student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_add(student_t **students, course_t **courses, char *argument)
{
  char first_name[50];
  char last_name[50];

  printf("First Name: ");
  fgets((char *restrict)&first_name, sizeof(first_name), stdin);

  printf("Last Name: ");
  fgets((char *restrict)&last_name, sizeof(last_name), stdin);

  first_name[strcspn(first_name, "\n")] = 0;
  last_name[strcspn(last_name, "\n")] = 0;

  add_student(students, 0, first_name, last_name);
}

/**
 * student_print_all - controller to list all students
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_print_all(student_t **students, course_t **courses, char *argument)
{
  int count = argument == NULL ? 0 : atoi(argument);
  print_students(*students, count);
}

/**
 * student_print_one - controller to list one student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_print_one(student_t **students, course_t **courses, char *argument)
{
  int roll_number = argument == NULL ? 0 : atoi(argument);
  if (!argument || (roll_number == 0 && argument[0] != '0'))
  {
    printf("Please provide a valid roll number\n");
    return;
  }

  student *student_data = find_student_by_roll_number(*students, roll_number);

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
  print_courses_by_roll_number(*courses, roll_number);

  printf("\n**********************************************\n");
}

/**
 * student_remove_one - controller to remove one student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_remove_one(student_t **students, course_t **courses, char *argument)
{
  int roll_number = argument == NULL ? 0 : atoi(argument);
  if (!argument || (roll_number == 0 && argument[0] != 0))
  {
    printf("Please provide a valid roll number\n");
    return;
  }

  remove_student_by_roll_number(students, roll_number);
}

/**
 * student_find - controller to find students given a search query
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_find(student_t **students, course_t **courses, char *argument)
{
  const char *query = argument == NULL ? "" : argument;
  find_students_by_query(*students, query);
}

/**
 * student_sort - sort the list of students
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_sort(student_t **students, course_t **courses, char *argument)
{
  char *direction = argument == NULL ? "asc" : argument;

  if (strcmp(direction, "asc") == 0)
  {
    sort_students_by_name(*students);
  }
  else if (strcmp(direction, "desc") == 0)
  {
    sort_students_by_name(*students);
    reverse_students_list(students);
  }
  else
  {
    printf("Sort direction can only be 'asc' or 'desc'\n");
    return;
  }
}

/**
 * student_save - save list of students to file
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_save(student_t **students, course_t **courses, char *argument)
{
  char *filename = argument == NULL ? "data/students.csv" : argument;
  save_students_to_csv(*students, filename);
}

/**
 * student_load - load list of students from file
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_load(student_t **students, course_t **courses, char *argument)
{
  char *filename = argument == NULL ? "students.csv" : argument;
  load_students_from_csv(students, filename);
}

/**
 * course_add - add a course for a student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void course_add(student_t **students, course_t **courses, char *argument)
{
  int roll_number = argument == NULL ? 0 : atoi(argument);
  if (!argument || (roll_number == 0 && argument[0] != '0'))
  {
    printf("Please provide a valid roll number\n");
    return;
  }
  student *student_data = find_student_by_roll_number(*students, roll_number);
  if (student_data == NULL)
  {
    printf("Student with roll number %d does not exist\n", roll_number);
    return;
  }
  char course_name[50];
  int score;

  printf("Course: ");
  fgets((char *restrict)&course_name, sizeof(course_name), stdin);

  printf("Score: ");
  scanf("%d[^\n]", &score);
  getchar();

  if (score < 0 || score > 100)
  {
    printf("Please enter a valid score\n");
    return;
  };

  course_name[strcspn(course_name, "\n")] = 0;

  add_course(courses, roll_number, course_name, score, 0);
}

/**
 * course_remove - remove course for a specified student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void course_remove(student_t **students, course_t **courses, char *argument)
{
  int roll_number = argument == NULL ? 0 : atoi(argument);
  if (!argument || (roll_number == 0 && argument[0] != '0'))
  {
    printf("Please provide a valid roll number\n");
    return;
  }
  student *student_data = find_student_by_roll_number(*students, roll_number);
  if (student_data == NULL)
  {
    printf("Student with roll number %d does not exist\n", roll_number);
    return;
  }

  char course_name[50];
  int courses_count = find_courses_by_roll_number(*courses, roll_number, 0);
  if (courses_count == 0)
  {
    printf("Student with roll number %d is not enrolled in any course.\n", roll_number);
    return;
  }
  find_courses_by_roll_number(*courses, roll_number, 1);
  printf("Course to remove: ");
  fgets((char *restrict)&course_name, sizeof(course_name), stdin);
  course_name[strcspn(course_name, "\n")] = 0;

  remove_course(courses, roll_number, course_name);
}
