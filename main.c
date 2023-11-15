#include "shell.h"

int main()
{
	char *arg, *command, input[MAX_INPUT_LENGTH], *line = NULL;
	size_t len = 0;
	ssize_t read;

	do
	{
		printf("Enter a line: ");
		read = _get_line(&line, &len, stdin);

		if (read != -1)
		{
			printf("You entered: %s\n", line);
		}
	} while (read != -1);

	free_mem(line);

	while (1)
	{
		printf("Shell> ");
		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = '\0';

		parse_input(input, &command, &arg);

		if (command[0] == '\0')
		{
			continue;
		}

		if (strcmp(command, "exit") == 0)
		{
			handle_exit(arg);
		}
		else if (strcmp(command, "env") == 0)
		{
			handle_env();
		}
		else if (strcmp(command, "setenv") == 0)
		{
			if (arg != NULL)
			{
				char *value = strchr(arg, ' ');
				if (value != NULL)
				{
					*value = '\0';
					value++;
					handle_setenv(arg, value);
				}
				else
				{
					fprintf(stderr, "Invalid syntax for setenv\n");
				}
			}
			else
			{
				fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			}
		}
		else if (strcmp(command, "unsetenv") == 0)
		{
			if (arg != NULL)
			{
				*arg = '\0';
				arg++;
				handle_unsetenv(arg);
			}
			else
			{
				fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			}
		}
		else if (strcmp(command, "cd") == 0)
		{
			handle_cd(arg);
		}
		else
		{
			handle_cmd(command, arg);
		}
	}

	return (0);
}

