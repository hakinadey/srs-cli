#include "srs.h"

/**
 * add_student - add a new student to the students linked list
 * @list: pointer to head of students linked list
 * @first_name: first name of student
 * @last_name: last name of student
 */
int add_student(student_t **list, int roll_number, char *first_name, char *last_name)
{
  student *new_student = (student *)malloc(sizeof(student));
  if (!new_student)
  {
    printf("Could not allocate enough memory for new student\n");
    return EXIT_FAILURE;
  }

  int default_roll_number = find_highest_roll_number(*list) + 1;
  new_student->roll_number = roll_number ? roll_number : default_roll_number;
  new_student->first_name = strdup(first_name);
  new_student->last_name = strdup(last_name);

  student_t *new_node = (student_t *)malloc(sizeof(student_t));
  if (!new_node)
  {
    free(new_student->first_name);
    free(new_student->last_name);
    free(new_student);
    printf("Could not allocate enough memory for new student\n");
    return EXIT_FAILURE;
  }

  new_node->data = new_student;

  if (*list == NULL)
    *list = new_node;
  else
  {
    student_t *current = *list;
    while (current->next)
      current = current->next;
    current->next = new_node;
    new_node->prev = current;
  }
  if (!roll_number)
    printf("Student added: (%d). %s %s\n", new_student->roll_number, first_name, last_name);
  return EXIT_SUCCESS;
}

/**
 * find_student_by_roll_number - find a single student in the linked list
 * @list: pointer to head of the linked list
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
 * print_students - print students in students linked list
 * @list: point to the head of the linked list
 * @count: number of students to print
 */
void print_students(student_t *list, int count)
{
  int printed = 0;
  student_t *current = list;

  printf("%-15s %-25s %-25s\n", "Roll Number", "First Name", "Last Name");
  printf("%-15s %-25s %-25s\n", "------------", "----------", "---------");

  while (current)
  {
    if (count != 0 && printed >= count)
      break;
    printf("%-15d %-25s %-25s\n", current->data->roll_number, current->data->first_name, current->data->last_name);
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
 * @list: pointer to linked list head
 * @filename: name of csv file
 */
void load_students_from_csv(student_t **list, char *filename)
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
    char first_name[50];
    char last_name[50];

    if (sscanf(line, "%d,%49[^,],%49[^,]", &roll_number, first_name, last_name) != 3)
    {
      fprintf(stderr, "Could not parse line: %s\n", line);
      return;
    }

    add_student(list, roll_number, first_name, last_name);
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
