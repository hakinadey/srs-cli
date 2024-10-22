#ifndef _SRS_H_
#define _SRS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
} student;

/**
 * student_t - student doubly linked list data type
 * @data: pointer to student data
 * @next: pointer to next student
 * @prev: pointer to next student
 */
typedef struct student_t
{
  student *data;
  struct student_t *next;
  struct student_t *prev;
} student_t;

/**
 * auto-incrementing roll number (ID) for students
 */
extern int ROLL_NUMBER;

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
  int score;
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

void init_program(void);

int add_student(student_t **list, int roll_number, char *first_name, char *last_name);
void print_students(student_t *list);
void save_students_to_csv(student_t *list, char *filename);
void load_students_from_csv(student_t **list, char *filename);

int add_course(course_t **list, int roll_number, char *course_name, int score, int silent);
void print_courses(course_t *list);
void save_courses_to_csv(course_t *list, char *filename);
void load_courses_from_csv(course_t **list, char *filename);

#endif /* _SRS_H_ */
