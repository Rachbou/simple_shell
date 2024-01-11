#include "main.h"
/**
 * main - runs the shell program
 * @argv: a NULL terminated array of strings
 * @argc: the number of items in av
 * Return: 0 on success
 */
int main(int argc, char ** argv)
{
	char *fpcommand = NULL, *tmpcommand = NULL, *command = NULL;
	char *PATH = NULL;
	char **av = NULL;
	int status = argc;
	char *err = strcat(argv[0],": No such file or directory\n");

	PATH = getenv("PATH");
	if (PATH == NULL)
		return (-1);
	while (1)
	{
		av = NULL;
		prompt();
		command = getCommand();
		if (*command != '\0')
		{
			av = tokenize(command);
			if (av == NULL)
			{
				free(command);
				continue;
			}
			fpcommand = fpCommand(av, PATH, tmpcommand);
			if (checkbuiltins(av, command, status) != 0)
				continue;
			status = _fork(av, command, fpcommand);
		}
		else
			free(command);
	}
	return (0);
}
