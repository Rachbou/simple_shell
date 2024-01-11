#include "main.h"
/**
 * prompt - writes a prompt
 *
 * Return: 0 on sucess
 */
int prompt(void)
{
	char *prompt = "$hsh$ ";
	ssize_t Count = 0;

	if (isatty(STDIN_FILENO) == 1)
	{
		Count = write(STDOUT_FILENO, prompt, 6);
		if (Count == -1)
			exit(0);
	}
	return (0);
}
/**
 * getCommand - reads stdin and stores it in a buffer
 *
 * Return: a pointer to the buffer
 */
char *getCommand(void)
{
	ssize_t Count = 0;
	size_t n = 0;
	char *Command = NULL;
	int i = 0;

	Count = getline(&Command, &n, stdin);
	if (Count == -1)
	{
		free(Command);
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (Command[Count - 1] == '\n' || Command[Count - 1] == '\t')
		Command[Count - 1] = '\0';
	for (i = 0; Command[i]; i++)
	{
		if (Command[i] == '#' && Command[i - 1] == ' ')
		{
			Command[i] = '\0';
			break;
		}
	}
	return (Command);
}
/**
 * fpCommand - finds the string to call execve on
 * @av: pointer to array of user strings
 * @PATH: pointer to PATH string
 * @tmpCommand: pointer to copy of PATH string
 *
 * Return: a pointer to string to call execve on
 */
char *fpCommand(char **av, char *PATH, char *tmpCommand)
{
	char *token = NULL, *fpCommand = NULL, *tmpstr = NULL;
	static char tmp[256];
	int Count = 0, flag = 0, z = 0, toklen = 0;
	struct stat h;

	tmpCommand = NULL;
	tmpCommand = _strdup(PATH);
	Count = _splitPATH(tmpCommand);
	token = strtok(tmpCommand, ": =");
	while (token != NULL)
	{
		tmpstr = _concat(tmp, av, token);
		if (stat(tmpstr, &h) == 0)
		{
			fpCommand = tmpstr;
			flag = 1;
			break;
		}
		if (z < Count - 2)
		{
			toklen = _strlen(token);
			if (token[toklen + 1] == ':')
			{
				if (stat(av[0], &h) == 0)
				{
					fpCommand = av[0];
					flag = 1;
					break;
				}
			}
		}
		z++;
		token = strtok(NULL, ":");
	}
	if (flag == 0)
		fpCommand = av[0];
	free(tmpCommand);
	return (fpCommand);
}
/**
 * checkbuiltins - check if first user string is a built-in
 * @av: pointer to array of user of strings
 * @Command: pointer to user string
 * @status: exit status of execve
 * Return: 1 if user string is equal to env or 0 otherwise
 */
int checkbuiltins(char **av, char *Command, int status)
{
	int i;

	if (_strcmp(av[0], "env") == 0)
	{
		_env();
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
		free(Command);
		return (1);
	}
	else if (_strcmp(av[0], "exit") == 0)
	{
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
		free(Command);
		exit(status);
	}
	else
		return (0);
}
/**
 * _fork - create child process to execute based on user input
 * @av: pointer to array of user of strings
 * @Command: pointer to user string
 * @fpCommand: pointer to user input
 *
 * Return: 0 on success
 */
int _fork(char **av, char *Command, char *fpCommand)
{
	int i, status, result, exitstatus = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
	{
		result =  execve(fpCommand, av, environ);
		if (result == -1)
		{
			perror(av[0]);
			for (i = 0; av[i]; i++)
				free(av[i]);
			free(av);
			free(Command);
			exit(127);
		}
	}
	wait(&status);
	if (WIFEXITED(status))
	{
		exitstatus = WEXITSTATUS(status);
	}
	for (i = 0; av[i]; i++)
		free(av[i]);
	free(av);
	free(Command);
	return (exitstatus);
}
