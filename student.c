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

  if (roll_number)
    ROLL_NUMBER = roll_number + 1;

  new_student->roll_number = roll_number ? roll_number : ROLL_NUMBER++;
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
 * print_students - print students in students linked list
 * @list: point to the head of the linked list
 */
void print_students(student_t *list)
{
  student_t *current = list;

  printf("%-15s %-25s %-25s\n", "Roll Number", "First Name", "Last Name");
  printf("%-15s %-25s %-25s\n", "------------", "----------", "---------");

  while (current)
  {
    printf("%-15d %-25s %-25s\n", current->data->roll_number, current->data->first_name, current->data->last_name);
    current = current->next;
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
