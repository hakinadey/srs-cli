#include "srs.h"

/**
 * add_course - add a new course to the courses linked list
 * @list: pointer to head of courses linked list
 * @first_name: first name of course
 * @last_name: last name of course
 */
int add_course(course_t **list, int roll_number, char *course_name, int score, int silent)
{
  course *new_course = (course *)malloc(sizeof(course));
  if (!new_course)
  {
    printf("Could not allocate enough memory for new course\n");
    return EXIT_FAILURE;
  }

  new_course->roll_number = roll_number;
  new_course->course_name = strdup(course_name);
  new_course->score = score;

  course_t *new_node = (course_t *)malloc(sizeof(course_t));
  if (!new_node)
  {
    free(new_course->course_name);
    free(new_course);
    printf("Could not allocate enough memory for new course\n");
    return EXIT_FAILURE;
  }

  new_node->data = new_course;

  if (*list == NULL)
    *list = new_node;
  else
  {
    course_t *current = *list;
    while (current->next)
      current = current->next;
    current->next = new_node;
    new_node->prev = current;
  }
  if (!silent)
    printf("Course added: (%d). %s %d\n", new_course->roll_number, course_name, score);
  return EXIT_SUCCESS;
}

/**
 * print_courses - print courses in courses linked list
 * @list: point to the head of the linked list
 */
void print_courses(course_t *list)
{
  course_t *current = list;

  printf("%-15s %-25s %-25s\n", "Roll Number", "Course Name", "Score");
  printf("%-15s %-25s %-25s\n", "------------", "----------", "---------");

  while (current)
  {
    printf("%-15d %-25s %-25d\n", current->data->roll_number, current->data->course_name, current->data->score);
    current = current->next;
  }
}

/**
 * save_to_csv - save list of courses to CSV file
 * @list: pointer to linked list head
 * @filename: name of csv file
 */
void save_courses_to_csv(course_t *list, char *filename)
{
  FILE *file = fopen(filename, "w");
  if (!file)
    return perror("Could not open file");

  course_t *current = list;

  fprintf(file, "Roll Number, Course Name, Score\n");
  while (current)
  {
    fprintf(file, "%d, %s, %d\n", current->data->roll_number, current->data->course_name, current->data->score);
    current = current->next;
  }

  fclose(file);
}

/**
 * load_from_csv - load list of courses from CSV file
 * @list: pointer to linked list head
 * @filename: name of csv file
 */
void load_courses_from_csv(course_t **list, char *filename)
{
  FILE *file = fopen(filename, "r");
  if (!file)
    return perror("Could not open file");

  char line[256];
  fgets(line, sizeof(line), file);

  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\n")] = 0;

    int roll_number;
    char course_name[50];
    int score;

    if (sscanf(line, "%d,%49[^,],%d", &roll_number, course_name, &score) != 3)
    {
      fprintf(stderr, "Could not parse line: %s\n", line);
      return;
    }

    add_course(list, roll_number, course_name, score, 1);
  }

  fclose(file);
}
