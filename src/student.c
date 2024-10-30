#include "srs.h"

/**
 * add_student - add a new student to the students linked list
 * @students: double pointer to head of students linked list
 * @courses: pointer to head of courses linked list
 * @first_name: first name of student
 * @last_name: last name of student
 */
void add_student(student_t **students, course_t *courses, int roll_number, char *first_name, char *last_name)
{
  student *new_student = (student *)malloc(sizeof(student));
  if (!new_student)
  {
    printf("Could not allocate enough memory for new student\n");
    return;
  }

  int default_roll_number = find_highest_roll_number(*students) + 1;
  new_student->roll_number = roll_number ? roll_number : default_roll_number;
  new_student->first_name = strdup(first_name);
  new_student->last_name = strdup(last_name);
  new_student->average_score = get_average_score(courses, roll_number);

  student_t *new_node = (student_t *)malloc(sizeof(student_t));
  if (!new_node)
  {
    free(new_student->first_name);
    free(new_student->last_name);
    free(new_student);
    printf("Could not allocate enough memory for new student\n");
    return;
  }

  new_node->data = new_student;
  new_node->prev = NULL;
  new_node->next = NULL;

  if (*students == NULL)
    *students = new_node;
  else
  {
    student_t *current = *students;
    while (current->next)
      current = current->next;
    current->next = new_node;
    new_node->prev = current;
  }
  if (!roll_number)
    printf("Student added: (%d). %s %s\n", new_student->roll_number, first_name, last_name);
}

/**
 * update_student_avg_score - update average score for a student
 * @data: double pointer to student data
 * @avg_score: new average score
 */
void update_student_avg_score(student **data, int average_score)
{
  if (!data)
    return;
  (*data)->average_score = average_score;
}

/**
 * find_student_by_roll_number - find a single student in the linked list
 * @list: pointer to head of the linked list
 * @roll_number: roll number to find
 */
student *find_student_by_roll_number(student_t *list, int roll_number)
{
  student_t *current = list;

  while (current != NULL)
  {
    if (current->data->roll_number == roll_number)
      return current->data;
    current = current->next;
  }

  return NULL;
}

/**
 * find_student_node_by_roll_number - find a single student node in the linked list
 * @list: pointer to head of the linked list
 * @roll_number: roll number to find
 */
student_t *find_student_node_by_roll_number(student_t *head, int roll_number)
{
  student_t *current = head;

  while (current != NULL)
  {
    if (current->data->roll_number == roll_number)
      return current;
    current = current->next;
  }

  return NULL;
}

/**
 * remove_student_by_roll_number - remove a single student with given roll number in the linked list
 * @list: double pointer to the head of list
 * @roll_number: roll number to remove
 */
void remove_student_by_roll_number(student_t **list, int roll_number)
{
  student_t *node = find_student_node_by_roll_number(*list, roll_number);

  if (node == NULL)
  {
    printf("Student with roll number %d does not exist\n", roll_number);
    return;
  }

  if (node == *list)
    *list = node->next;

  if (node->prev != NULL)
    node->prev->next = node->next;

  if (node->next != NULL)
    node->next->prev = node->prev;

  free(node->data->first_name);
  free(node->data->last_name);
  free(node->data);
  free(node);
  printf("Student with roll number %d removed\n", roll_number);
}

/**
 * find_students_by_query - search list for student whose names match query
 * @list: pointer to head of list
 * @query: query string
 */
void find_students_by_query(student_t *list, const char *query)
{
  student_t *current = list;
  int found = 0;

  printf("%-15s %-25s %-25s %-10s\n", "Roll Number", "First Name", "Last Name", "Avg. Score");
  printf("%-15s %-25s %-25s %-10s\n", "------------", "----------", "---------", "---------");

  while (current != NULL)
  {
    if ((strcasestr(current->data->first_name, query) != NULL) ||
        (strcasestr(current->data->last_name, query) != NULL))
    {
      printf("%-15d %-25s %-25s %-10d\n", current->data->roll_number, current->data->first_name, current->data->last_name, current->data->average_score);
      found = 1;
    }
    current = current->next;
  }

  if (!found)
    printf("No students found matching the query '%s'.\n", query);
}

/**
 * sort_students_by_name - sort students list by name on ascending order
 * @list: pointer to students list
 */
void sort_students_by_name(student_t *list)
{
  if (list == NULL)
    return;

  int swapped;
  student_t *current;
  student_t *last = NULL;

  do
  {
    swapped = 0;
    current = list;

    while (current->next != last)
    {
      int cmp_first = strcmp(current->data->first_name, current->next->data->first_name);
      int cmp_last = strcmp(current->data->last_name, current->next->data->last_name);

      if (cmp_first > 0 || (cmp_first == 0 && cmp_last > 0))
      {
        swap_students(current->data, current->next->data);
        swapped = 1;
      }
      current = current->next;
    }
    last = current;

  } while (swapped);
}

/**
 * sort_students_by_avg_score - sort students list by score on ascending order
 * @list: pointer to students list
 */
void sort_students_by_avg_score(student_t *list)
{
  if (list == NULL)
    return;

  int swapped;
  student_t *current;
  student_t *last = NULL;

  do
  {
    swapped = 0;
    current = list;

    while (current->next != last)
    {
      if (current->data->average_score > current->next->data->average_score)
      {
        swap_students(current->data, current->next->data);
        swapped = 1;
      }
      current = current->next;
    }
    last = current;

  } while (swapped);
}

/**
 * reverse_students_list - reverse the students linked list
 * @list: double pointer to linked list
 */
void reverse_students_list(student_t **list)
{
  student_t *current = *list;
  student_t *temp = NULL;

  while (current != NULL)
  {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;

    current = current->prev;
  }

  if (temp != NULL)
    *list = temp->prev;
}

/**
 * print_students - print students in students linked list
 * @list: point to the head of the linked list
 * @count: number of students to print
 */
void print_students(student_t *list, int count)
{
  int printed = 0;
  student_t *current = list;

  printf("%-15s %-25s %-25s %-25s\n", "Roll Number", "First Name", "Last Name", "Avg. Score");
  printf("%-15s %-25s %-25s %-25s\n", "------------", "----------", "---------", "---------");

  while (current)
  {
    if (count != 0 && printed >= count)
      break;
    printf("%-15d %-25s %-25s %-d (%s)\n", current->data->roll_number, current->data->first_name, current->data->last_name, current->data->average_score, get_score_grade(current->data->average_score));
    current = current->next;
    printed++;
  }
}

/**
 * save_to_csv - save list of students to CSV file
 * @list: pointer to linked list head
 * @filename: name of csv file
 */
void save_students_to_csv(student_t *list, char *filename)
{
  FILE *file = fopen(filename, "w");
  if (!file)
    return perror("Could not open file");

  student_t *current = list;

  fprintf(file, "Roll Number, First Name, Last Name\n");
  while (current)
  {
    fprintf(file, "%d, %s, %s\n", current->data->roll_number, current->data->first_name, current->data->last_name);
    current = current->next;
  }

  fclose(file);
}

/**
 * load_from_csv - load list of students from CSV file
 * @students: double pointer to students linked list head
 * @courses: pointer to courses linked list head
 * @filename: name of csv file
 */
void load_students_from_csv(student_t **students, course_t *courses, char *filename)
{
  FILE *file = fopen(filename, "r");
  if (!file)
    return perror("Could not open file");

  char line[256];
  fgets(line, sizeof(line), file);

  empty_students_list(students);
  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\n")] = 0;

    int roll_number;
    char first_name[50];
    char last_name[50];

    if (sscanf(line, "%d,%49[^,],%49[^,]", &roll_number, first_name, last_name) != 3)
    {
      printf("Could not parse line: %s\n", line);
      return;
    }

    add_student(students, courses, roll_number, first_name, last_name);
  }

  fclose(file);
}

/**
 * show_student_help - display help page for student command
 */
void show_student_help(void)
{
  printf("\nNAME\n");
  printf("    student - Manage students' records interactively\n");

  printf("\nSYNOPSIS\n");
  printf("    student [COMMAND] [OPTIONS]\n");

  printf("\nDESCRIPTION\n");
  printf("    This program allows you to manage students' records. ");
  printf("You can add, remove, display, list, sort, and search for students. ");
  printf("The program runs in an infinite loop until 'exit' is entered.\n");

  printf("\nCOMMANDS\n");

  printf("    student add\n");
  printf("        Add a new student. You will be prompted for the student's first name and last name.\n\n");

  printf("    student remove <roll_number>\n");
  printf("        Remove a student with the specified roll number.\n\n");

  printf("    student show <roll_number>\n");
  printf("        Display the details of a student with the specified roll number.\n\n");

  printf("    student list [n]\n");
  printf("        List all or first n students in the system.\n\n");

  printf("    student sort asc|desc\n");
  printf("        Sort the student list in ascending or descending order by roll number.\n\n");

  printf("    student find <query>\n");
  printf("        Find a student by their first or last name. The <query> can be any part of the name.\n\n");

  printf("    student save <filename>\n");
  printf("        Save list of students to a text/csv file.\n\n");

  printf("    student load <filename>\n");
  printf("        Load list of students from a text/csv file.\n\n");

  printf("    student help\n");
  printf("        Display this help information for student commands.\n\n");

  printf("    exit\n");
  printf("        Exit the program.\n");

  printf("\nEXAMPLES\n");

  printf("    student add\n");
  printf("        Prompts the user for the first and last name and creates a new student record.\n\n");

  printf("    student remove 3\n");
  printf("        Removes the student with roll number 3.\n\n");

  printf("    student show 5\n");
  printf("        Displays the student record for roll number 5.\n\n");
}

/**
 * find_highest_roll_number - find the highest roll number
 * @list: pointer to head of the linked list
 */
int find_highest_roll_number(student_t *list)
{
  if (list == NULL)
    return 0;

  int highest_roll_number = list->data->roll_number;

  student_t *current = list->next;
  while (current != NULL)
  {
    if (current->data->roll_number > highest_roll_number)
      highest_roll_number = current->data->roll_number;
    current = current->next;
  }

  return highest_roll_number;
}

/**
 * strcasestr - search string case-insensitive
 * @haystack: string to search
 * @needle: substring to find
 */
char *strcasestr(const char *haystack, const char *needle)
{
  if (!*needle)
  {
    return (char *)haystack;
  }

  for (; *haystack; ++haystack)
  {
    if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle))
    {
      const char *h, *n;
      for (h = haystack, n = needle; *h && *n; ++h, ++n)
      {
        if (tolower((unsigned char)*h) != tolower((unsigned char)*n))
        {
          break;
        }
      }
      if (!*n)
      {
        return (char *)haystack;
      }
    }
  }
  return NULL;
}

/**
 * swap_students - swap two students
 * @first_student: pointer to first student
 * @second_student: pointer to second student
 */
void swap_students(student *first_student, student *second_student)
{
  student temp = *first_student;
  *first_student = *second_student;
  *second_student = temp;
}

/**
 * empty_students_list - empty the students linked list
 * @list: double pointer to linked list
 */
void empty_students_list(student_t **list)
{
  student_t *current = *list;
  student_t *next = NULL;

  while (current != NULL)
  {
    next = current->next;

    free(current->data->first_name);
    free(current->data->last_name);
    free(current->data);

    free(current);

    current = next;
  }

  *list = NULL;
}
