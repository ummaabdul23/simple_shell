#include "shell.h"

/**
 * handle_cmd - Function to handle other commands
 *  @cmd: --
 *  @arg: --
 */

void handle_cmd(char *cmd, char *arg)
{
	char **environ;
	pid_t pid = fork();
	char *path, *path_copy, *dir;
	char exec_path[MAX_INPUT_LENGTH];

	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char **argv = malloc(3 * sizeof(char *));
		if (argv == NULL)
		{
			perror("Memory Allocation Error");
			exit(EXIT_FAILURE);
		}

		argv[0] = cmd;
		argv[1] = arg;
		argv[2] = NULL;

		path = getenv("PATH");
		if (path == NULL)
		{
			fprintf(stderr, "PATH environment variable not found.\n");
			exit(EXIT_FAILURE);
		}

		path_copy = strdup(path);

		if (path_copy == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		dir = path_copy;

		while (*dir != '\0')
		{
			char *end = strchr(dir, ':');

			if (end == NULL)
			{
				end = dir + strlen(dir);
			}
			snprintf(exec_path, sizeof(exec_path),
					"%.*s/%s", (int)(end - dir), dir, cmd);
			execve(exec_path, argv, environ);

			if (*end == ':')
			{
				dir = end + 1;
			}
			else
				break;
		}
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

/**
 * parse_input - Function to parse user input
 *  @input: ---
 *  @cmd: --
 *  @arg: --
 */

void parse_input(char *input, char **cmd, char **arg)
{
	*cmd = input;
	*arg = strchr(input, ' ');

	if (*arg != NULL)
	{
		*(*arg) = '\0';
		(*arg)++;
	}
}
/**
 * _get_line - Function to read a line from the file
 * @lineptr: line pointer
 * @n: size paramete
 * @stream: streamed file
 * Return: i or -1
 */

ssize_t _get_line(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer = NULL;
	size_t position = 0;
	size_t size = 0;
	size_t i = 0;

	if (buffer == NULL || size == 0)
	{
		*n = 128;
		buffer = (char *)alloc_mem(*n);
	}

	while (1)
	{
		refill_buf(&buffer, &position, &size, stream);

		if (size == 0)
		{
			break;
		}

		if (i >= *n - 1)
		{
			*n *= 2;
			*lineptr = realloc_mem(*lineptr, *n);
		}
		(*lineptr)[i++] = buffer[position];

		if (buffer[position] == '\n')
		{
			break;
		}
		position++;
	}
	(*lineptr)[i] = '\0';

	if (i > 0)
		return (i);
	else
		return (-1);
}
