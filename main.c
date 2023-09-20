#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64

void print_prompt(void);
char *read_command(void);
void execute_command(char *command);
void handle_eof(void);

/**
 * print_prompt - Display the shell prompt.
 */
void print_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Read a command from the user and return it as a string.
 *
 * Return: The command string.
 */
char *read_command(void)
{
	char *line = malloc(MAX_LINE_LENGTH);
	if (line == NULL)
	{
		perror("malloc");
		exit(1);
	}

	if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
	{
		/* Handle end of file (Ctrl+D) */
		handle_eof();
	}

	/* Remove the newline character from the end of the line */
	line[strlen(line) - 1] = '\0';

	return (line);
}

/**
 * execute_command - Execute a shell command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	/* Fork a child process */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (child_pid == 0)
	{
		char **argv = create_argv(command);

		if (execvp(argv[0], argv) == -1)
		{
			perror("hsh");
			free(argv);
			exit(1);
		}
	}
	else
	{
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(1);
		}

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			printf("Child exited with status %d\n", exit_status);
		}
	}
}

/**
 * handle_eof - Handle the "end of file" condition (Ctrl+D).
 */
void handle_eof(void)
{
	printf("\n");
	exit(0);
}

/**
 * main - The main entry point of the shell.
 *
 * Description: This function serves as the main entry point of the shell. It
 * reads commands from the user, executes them, and displays the shell prompt.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char *line;

	while (1)
	{
		print_prompt();
		line = read_command();
		execute_command(line);
		free(line);
	}

	return (0);
}
