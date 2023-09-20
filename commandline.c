#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64

void print_prompt(void);
void read_command(char *line);
void execute_command(char *command);
void handle_eof(void);
char **create_argv(char *command);

/**
 * print_prompt - Display the shell prompt.
 */
void print_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Read a command from the user.
 * @line: A buffer to store the command line.
 */
void read_command(char *line)
{
	if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL)
	{
		/* Handle end of file (Ctrl+D) */
		handle_eof();
	}

	/* Remove the newline character from the end of the line */
	line[strlen(line) - 1] = '\0';
}

/**
 * execute_child_process - Execute a shell command in the child process.
 * @command: The command to execute.
 */
void execute_child_process(char *command)
{
	char **argv = create_argv(command);

	if (execvp(command, argv) == -1)
	{
		perror("hsh");
		free(argv);
		exit(1);
	}
}

/**
 * wait_for_child - Wait for the child process to finish.
 * @child_pid: The process ID of the child.
 * @status: Pointer to the status variable.
 */
void wait_for_child(pid_t child_pid, int *status)
{
	if (waitpid(child_pid, status, 0) == -1)
	{
		perror("waitpid");
		exit(1);
	}
}

/**
 * report_child_status - Report the status of the child process.
 * @status: The status of the child process.
 */
void report_child_status(int status)
{
	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);

		printf("Child exited with status %d\n", exit_status);
	}
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
		execute_child_process(command);
	}
	else
	{
		wait_for_child(child_pid, &status);
		report_child_status(status);
	}
}

/**
 * create_argv - Create an argument vector from a command string.
 * @command: The command string.
 * Return: An array of strings (arguments).
 */
char **create_argv(char *command)
{
	char **argv = malloc(MAX_ARGS * sizeof(char *));

	if (argv == NULL)
	{
		perror("malloc");
		exit(1);
	}

	{
		char *token;
		int argc = 0;

		token = strtok(command, " ");
		while (token != NULL)
		{
			argv[argc] = strdup(token);
			if (argv[argc] == NULL)
			{
				perror("strdup");
				exit(1);
			}
			argc++;

			if (argc >= MAX_ARGS - 1)
			{
				fprintf(stderr, "Too many arguments\n");
				exit(1);
			}

			token = strtok(NULL, " ");
		}


	argv[argc] = NULL;
	{
free(argv[argc]);
}
}

	return (argv);
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
	char line[MAX_LINE_LENGTH];

	while (1)
	{
		print_prompt();
		read_command(line);
		execute_command(line);
	}

	return (0);
}
