# Student Record System (SRS)

Manage student records and their courses interactively

## Description

This program allows you to manage student records and their courses using a shell prompt.
You can add, remove, display, list, sort, and search for students and courses.
The program runs in an infinite loop until 'exit' is entered.

## Commands

### General commands

#### Save data to files.

```bash
save [students_filename] [courses_filename]
```

#### Load data from files.

```bash
load [students_filename] [courses_filename]
```

#### Displays help page for student commands.

```bash
student help
```

#### Display help page for course commands.

```bash
course help
```

#### Exit the program.

```bash
exit
```

### `student` commands

Allows you to manage students' records.
You can add, remove, display, list, sort, and search for students.
The program runs in an infinite loop until `exit` is entered.

#### Synopsis

```bash
student [COMMAND] [OPTIONS]
```

#### Add a new student

You will be prompted for the student's first name and last name.

```bash
student add
```

#### Remove a student

Remove a student with the specified roll number.

```bash
student remove <roll_number>
```

#### List students

List all or first `n` students in the system.

```bash
student list [n]
```

#### Sort students

Sort the student list in ascending or descending order by roll number.

```bash
student sort [asc|desc]
```

#### Search for students

Find students by their first or last names. The `query` can be any part of the name.

```bash
student find <query>
```

### `course` commands

Allows you to manage students' courses.

#### Synopsis

```bash
course [COMMAND] [OPTIONS]
```

#### Add a new course

Add a new course for student with specified roll number. You will be prompted for the course name and score.

```bash
course add <roll_number>
```

#### Remove a course

Remove a course for student with the specified roll number. You will be prompted for te course name.

```bash
course remove <roll_number>
```
