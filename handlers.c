#include "shell.h"

extern char **environ;

/** handle_exit - Function to handle the exit command
 * @arg: parameter
 */

void handle_exit(char *arg)
{
	printf("Exiting the shell.\n");
	if (arg != NULL)
	{
		int status = atoi(arg);
		exit(status);
	}
	else
	{
		exit(0);
	}
}

/** handle_env - Function to handle the env command
 */

void handle_env()
{
	int i;

	printf("Current environment variables:\n");
	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/** handle_setenv - Function to handle the setenv command
 * @variable: --
 * @value: --
 */

void handle_setenv(char *variable, char *value)
{
	if (setenv(variable, value, 1) != 0)
	{
		fprintf(stderr, "Failed to set environment variable.\n");
	}
}

/** handle_unsetenv - Function to handle the unsetenv command
 * @variable: --
 */

void handle_unsetenv(char *variable)
{
	if (unsetenv(variable) != 0)
	{
		fprintf(stderr, "Failed to unset environment variable.\n");
	}
}

/** handle_cd - Function to handle the cd command
 * @dir: --
 */

void handle_cd(char *dir)
{
	char *target_dir = (dir != NULL) ? dir : getenv("HOME");
	char current_dir[MAX_INPUT_LENGTH];

	if (strcmp(target_dir, "-") == 0)
	{
		if (getenv("OLDPWD") != NULL)
		{
			target_dir = getenv("OLDPWD");
		}
		else
		{
			fprintf(stderr, "OLDPWD not set.\n");
			return;
		}
	}

	if (chdir(target_dir) != 0)
	{
		fprintf(stderr, "Failed to change directory to %s\n", target_dir);
	}
	else
	{
		getcwd(current_dir, sizeof(current_dir));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", current_dir, 1);
	}
}
