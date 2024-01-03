#include "main.h"

/**
 * prompt - Display a prompt to the user.
 *
 * Return: 0 on sucess
 */
int prompt(void)
{
	ssize_t Count;

	if (isatty(STDIN_FILENO) == 1)
	{
		Count = write(STDOUT_FILENO, "$shell$ ", 8);
		if (Count == -1)
			exit(0);
	}
	return (0);
}

/**
 * getCommand - Reads the users command.
 *
 * Return: the users command.
 */
char *getCommand(void)
{
	ssize_t Count;
	char *command = NULL;
	size_t n = 0;
	
	Count = getline(&command, &n, stdin);
	if (Count <= -1)
	{
		free(command);
		exit(0);
	}
	if (command[Count - 1] == '\n' || command[Count - 1] == '\t')
	{
		command[Count - 1] = '\0';
	}
	
	return (command);
}
