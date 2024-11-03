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

  add_student(students, *courses, 0, first_name, last_name);
}

/**
 * student_list - controller to list all students
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_list(student_t **students, course_t **courses, char *argument)
{
  int count = argument == NULL ? 0 : atoi(argument);
  print_students(*students, count);
}

/**
 * student_show - controller to list one student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_show(student_t **students, course_t **courses, char *argument)
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
 * student_remvoe - controller to remove one student
 * @list: pointer to linked list
 * @argument: argument passed to controller
 */
void student_remvoe(student_t **students, course_t **courses, char *argument)
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
  char *direction = argument == NULL ? "desc" : argument;

  if (strcmp(direction, "asc") == 0)
  {
    sort_students_by_avg_score(*students);
  }
  else if (strcmp(direction, "desc") == 0)
  {
    sort_students_by_avg_score(*students);
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
  char *filename = argument == NULL ? "data/students.csv" : argument;
  load_students_from_csv(students, *courses, filename);
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
  char score_input[50];
  float score;

  printf("Course: ");
  fgets((char *restrict)&course_name, sizeof(course_name), stdin);
  course_name[strcspn(course_name, "\n")] = 0;

  if (find_course(*courses, roll_number, course_name) == 1)
  {
    printf("Student with roll number %d is already enrolled to %s\n", roll_number, course_name);
    return;
  }

  printf("Score: ");
  fgets((char *restrict)&score_input, sizeof(score_input), stdin);
  score_input[strcspn(score_input, "\n")] = 0;

  if (is_valid_float(score_input) == 0)
  {
    printf("%s is not a valid score\n", score_input);
    return;
  };

  score = strtof(score_input, NULL);
  if (score < 0 || score > 100)
  {
    printf("%s is not a valid score\n", score_input);
    return;
  };

  add_course(courses, roll_number, course_name, score, 0);
  update_student_avg_score(&student_data, get_average_score(*courses, roll_number));
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
  update_student_avg_score(&student_data, get_average_score(*courses, roll_number));
}
