#ifndef _SRS_H_
#define _SRS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * student - student data type
 * @roll_number: roll number (ID) of student
 * @first_name: first name of student
 * @last_name: last name of student
 */
typedef struct
{
  int roll_number;
  char *first_name;
  char *last_name;
  float average_score;
} student;

/**
 * student_t - student doubly linked list data type
 * @data: pointer to student data
 * @next: pointer to next student
 * @prev: pointer to next student
 */
typedef struct student_s
{
  student *data;
  struct student_s *next;
  struct student_s *prev;
} student_t;

/**
 * course - course data type
 * @roll_number: roll number (ID) of student
 * @course_name:name of course
 * @score: mark of student
 */
typedef struct
{
  int roll_number;
  char *course_name;
  float score;
} course;

/**
 * course_t - course doubly linked list data type
 * @data: pointer to course data
 * @next: pointer to next course
 * @prev: pointer to next course
 */
typedef struct course_t
{
  course *data;
  struct course_t *next;
  struct course_t *prev;
} course_t;

/**
 * controller_t - map command to controller function
 * @command: command entered
 * @function: controller function to execute
 */
typedef struct
{
  char *command;
  void (*function)(student_t **students, course_t **courses, char *argument);
} controller_t;

void init_program(void);
void print_usage(void);
void show_student_help(void);
void show_course_help(void);

void add_student(student_t **students, course_t *courses, int roll_number, char *first_name, char *last_name);
void update_student_avg_score(student **data, float average_score);
int find_highest_roll_number(student_t *list);
student *find_student_by_roll_number(student_t *list, int roll_number);
student_t *find_student_node_by_roll_number(student_t *head, int roll_number);
void find_students_by_query(student_t *list, const char *query);
void remove_student_by_roll_number(student_t **list, int roll_number);
void sort_students_by_name(student_t *list);
void sort_students_by_avg_score(student_t *list);
void reverse_students_list(student_t **list);
void print_students(student_t *list, int count);
void save_students_to_csv(student_t *list, char *filename);
void load_students_from_csv(student_t **students, course_t *courses, char *filename);
char *strcasestr(const char *haystack, const char *needle);
void swap_students(student *first_student, student *second_student);
void empty_students_list(student_t **list);
int str_empty(const char *str);

void add_course(course_t **list, int roll_number, char *course_name, float score, int silent);
void remove_course(course_t **list, int roll_number, char *course_name);
void print_courses(course_t *list);
void print_courses_by_roll_number(course_t *list, int roll_number);
int find_courses_by_roll_number(course_t *head, int roll_number, int print);
int find_course(course_t *head, int roll_number, char *course_name);
void save_courses_to_csv(course_t *list, char *filename);
void load_courses_from_csv(course_t **list, char *filename);
const char *get_score_grade(float score);
float get_average_score(course_t *list, int roll_number);
void empty_courses_list(course_t **list);
int is_valid_float(const char *str);

void student_add(student_t **students, course_t **courses, char *argument);
void student_list(student_t **students, course_t **courses, char *argument);
void student_show(student_t **students, course_t **courses, char *argument);
void student_remvoe(student_t **students, course_t **courses, char *argument);
void student_find(student_t **students, course_t **courses, char *argument);
void student_sort(student_t **students, course_t **courses, char *argument);
void student_save(student_t **students, course_t **courses, char *argument);
void student_load(student_t **students, course_t **courses, char *argument);

void course_add(student_t **students, course_t **courses, char *argument);
void course_remove(student_t **students, course_t **courses, char *argument);

#endif /* _SRS_H_ */
