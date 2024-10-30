#include "srs.h"

/**
 * add_course - add a new course to the courses linked list
 * @list: pointer to head of courses linked list
 * @first_name: first name of course
 * @last_name: last name of course
 */
void add_course(course_t **list, int roll_number, char *course_name, int score, int silent)
{
  course *new_course = (course *)malloc(sizeof(course));
  if (!new_course)
  {
    printf("Could not allocate enough memory for new course\n");
    return;
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
    return;
  }

  new_node->data = new_course;
  new_node->prev = NULL;
  new_node->next = NULL;

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
    printf("%s (Grade %s) added for student with roll number %d\n", course_name, get_score_grade(score), roll_number);
}

/**
 * remove_course - remove a course from the linked list
 * @list: pionter to head of the linked list
 * @roll_number: roll number of student
 * @course_name: name of course
 */
void remove_course(course_t **list, int roll_number, char *course_name)
{
  course_t *node = *list;
  while (node != NULL)
  {
    if (node->data->roll_number == roll_number && strcmp(node->data->course_name, course_name) == 0)
      break;
    node = node->next;
  }

  if (node == NULL)
  {
    printf("Student with roll number %d is not enrolled in %s\n", roll_number, course_name);
    return;
  }

  if (node == *list)
    *list = node->next;

  if (node->prev != NULL)
    node->prev->next = node->next;

  if (node->next != NULL)
    node->next->prev = node->prev;

  free(node->data->course_name);
  free(node->data);
  free(node);
  printf("%s removed for student with roll number %d\n", course_name, roll_number);
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
 * find_courses_by_roll_number - find all courses with given roll number
 * @list: pointer to courses linked list
 * @roll_number: roll number to find
 */
void print_courses_by_roll_number(course_t *list, int roll_number)
{
  int found = 0;
  course_t *current = list;

  if (current != NULL)
  {
    printf("%-15s %-10s %-10s\n", "Course Name", "Score", "Grade");
    printf("%-15s %-10s %-10s\n", "----------", "---------", "---------");
  }

  int total_score = 0;
  int scores_count = 0;
  while (current != NULL)
  {
    if (current->data->roll_number == roll_number)
    {
      printf("%-15s %-10d %-10s\n", current->data->course_name, current->data->score, get_score_grade(current->data->score));
      total_score += current->data->score;
      scores_count++;
      found = 1;
    }
    current = current->next;
  }

  if (found)
  {
    printf("%-15s %-10s %-10s\n", "----------", "---------", "---------");
    printf("%-15s %-10d %-10s\n", "Average", total_score / scores_count, get_score_grade(total_score / scores_count));
    found = 1;
  }
  else
  {
    printf("No courses enrolled.\n");
  }
}

/**
 * find_courses_by_roll_number - find all courses with given roll number
 * @list: pointer to courses linked list
 * @roll_number: roll number to find
 */
int find_courses_by_roll_number(course_t *head, int roll_number, int print)
{
  course_t *current = head;

  if (print && current != NULL)
  {
    printf("%-15s %-10s %-10s\n", "Course Name", "Score", "Grade");
    printf("%-15s %-10s %-10s\n", "----------", "---------", "---------");
  }

  int courses_count = 0;
  while (current != NULL)
  {
    if (current->data->roll_number == roll_number)
    {
      if (print)
        printf("%-15s %-10d %-10s\n", current->data->course_name, current->data->score, get_score_grade(current->data->score));
      courses_count++;
    }
    current = current->next;
  }

  if (print && courses_count == 0)
    printf("No courses enrolled.\n");

  return (courses_count);
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

/**
 * show_course_help - display help page for course command
 */
void show_course_help(void)
{
  printf("\nNAME\n");
  printf("    course - Manage students' courses interactively\n");

  printf("\nSYNOPSIS\n");
  printf("    course [COMMAND] [OPTIONS]\n");

  printf("\nDESCRIPTION\n");
  printf("    This program allows you to manage students' courses. ");
  printf("You can add, remove, display, list, sort, and search for students' courses. ");
  printf("The program runs in an infinite loop until 'exit' is entered.\n");

  printf("\nCOMMANDS\n");
  printf("    course add <roll_number>\n");
  printf("        Add a new course for a student. You will be prompted for the course name and the score.\n\n");

  printf("    course remove <roll_number> <course_name>\n");
  printf("        Remove a course for the specified student by roll number and course name.\n\n");

  printf("    course show <roll_number>\n");
  printf("        Display all the courses and scores for the specified student by roll number.\n\n");

  printf("    course list\n");
  printf("        List all courses.\n\n");

  printf("    course save <filename>\n");
  printf("        Save list of courses to a text/csv file.\n\n");

  printf("    course load <filename>\n");
  printf("        Load list of courses from a text/csv file.\n\n");

  printf("    course help\n");
  printf("        Display this help information for course commands.\n\n");

  printf("\nEXAMPLES\n");
  printf("    course add 1\n");
  printf("        Prompts for a course name and score, then adds the course to the student with roll number 1.\n\n");

  printf("    course show 2\n");
  printf("        Displays all courses and their scores for the student with roll number 2.\n\n");

  printf("    exit\n");
  printf("        Exits the program.\n");
}

/**
 * get_score_grade - compute grade associated with score
 * @score: score value
 */
const char *get_score_grade(int score)
{

  if (score >= 70)
    return "A";
  if (score >= 60)
    return "B";
  if (score >= 50)
    return "C";
  if (score >= 40)
    return "D";
  return "F";
}

/**
 * get_average_score - get the average_score of a student
 * @roll_number: roll number of student
 * @courses: pointer to courses linked list
 */
int get_average_score(course_t *list, int roll_number)
{
  int total_score = 0;
  int courses_count = 0;
  course_t *current = list;

  while (current != NULL)
  {
    if (current->data->roll_number == roll_number)
    {
      total_score += current->data->score;
      courses_count++;
    }
    current = current->next;
  }

  if (courses_count == 0)
    return 0;

  return total_score / courses_count;
}

/**
 * empty_courses_list - empty the courses linked list
 * @list: double pointer to linked list
 */
void empty_courses_list(course_t **list)
{
  course_t *current = *list;
  course_t *next = NULL;

  while (current != NULL)
  {
    next = current->next;

    free(current->data->course_name);
    free(current->data);

    free(current);

    current = next;
  }

  *list = NULL;
}
