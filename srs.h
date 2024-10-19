#ifndef _SRS_H_
#define _SRS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct command_s - command and its function
 * @command: the command
 * @function: function to handle the command
 *
 * Description: command and its function
 */
typedef struct command_s
{
	char *command;
	void (*function)(void);
} command_t;

#define COMMANDS \
  { \
    {"add", add_student}, \
    {"remove", remove_student}, \
    {"save", remove_student}, \
    {NULL, NULL} \
	}

void add_student(void);
void remove_student(void);

#endif /* _SRS_H_ */
