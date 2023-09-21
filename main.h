#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>

#define MCL 100 /*MAX COMMAND LENGTH*/
#define IBS 64 /*INITIAL BUFFER SIZE*/
#define BGF 2 /*BUFFER GROWING FACTOR*/
#define SIZE 1024
#define BUFFER 128
#define DELIM " \t\r\n\a"
#define END_OF_FILE -2
#define EXIT -3
#define MAX_LINE_LENGTH 1024

/* Global environemnt */
extern char **environ;

/**
 * struct list_s - A new struct tygetlinepe defining a linked list.
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
extern alias_t *aliases;

/* Function prototypes */
void print_prompt(void);
void read_command(char *line);
void execute_command(char *command);
void handle_eof(void);


/* Prompt and input functions */
void print_prompt(void);

/* Built-in commands */
int execute_builtin(char *command);
int my_cd(char **args, char **front);
int my_env(char **args, char **front);
int my_exit(char **args, char **front);

/* Alias functions */
void add_alias(char *name, char *value);
char *get_alias(char *name);
void free_aliases(void);

/* Environment variables functions */
char *get_env(const char *name);
int set_env(const char *name, const char *value);
int unset_env(const char *name);

/* Error handling */
void handle_error(const char *message);
void perror_exit(const char *message);

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

#endif
