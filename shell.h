#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define SIZE 1024
#define BUFFER 128
#define DELIM " \t\r\n\a"
#define END_OF_FILE -2
#define EXIT -3
#define MAX_LINE_LENGTH 1024

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;
char **environ;

/* Function prototypes */
void print_prompt(void);
void read_command(char *line);
void execute_command(char *command);
void handle_eof(void);
int execute_builtin(char *command);

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);


/* String functions */
int _strlen(const char *s);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);

#endif /* _SHELL_H_ */