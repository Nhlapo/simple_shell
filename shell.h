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
<<<<<<< HEAD
=======
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

void _prompt(void);

void _tokenize(char *args[], char *cmd);
void _ext(char *cmd);
void _printenv(char *cmd);
/*int _execve(const char *pathname, char *const argv[], char *const envp[]);*/
/*pid_t _waitpid(pid_t pid, int *wstatus, int options);*/
/*char *check_cmd(char *cmd);*/

/* string function */
int _strcmp(const char *s1, const char *s2);
size_t _strlen(const char *str);
size_t _strcspn(const char *str, const char *reject);
char *_strtok(char *str, const char *delim);

/* getline */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

int proc_file_commands(char *file_path, int *exe_ret);
>>>>>>> 6fafdc80e123e015a1412a03c5ee152fac379d26

#endif /* _SHELL_H_ */
