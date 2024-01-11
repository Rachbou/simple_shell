#include "main.h"
/**
 * tokenize - creates array of tokens based on user string
 * @buffer: pointer to user string
 *
 * Return: pointer to array of user strings
 */
char **tokenize(char *buffer)
{
	char *token = NULL;
	int i = 0, Count = 0;
	char *delimiter = " \n";
	char **av = NULL;

	Count = _splitstring(buffer);
	if (!Count)
		return (NULL);
	av = malloc((Count + 1) * sizeof(char *));
	if (av == NULL)
		exit(1);
	token = strtok(buffer, delimiter);
	while (token != NULL)
	{
		av[i] = _strdup(token);
		token = strtok(NULL, delimiter);
		i++;
	}
	av[i] = NULL;
	return (av);
}
/**
 * _splitPATH - counts the number of PATH members
 * @str: pointer to string to count
 *
 * Return: number of PATH members
 */
int _splitPATH(char *str)
{
	int i, flag = 1, Count = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] != ':' && flag == 1)
		{
			Count += 1;
			flag = 0;
		}
		if (str[i + 1] == ':')
		{
			flag = 1;
		}
	}
	return (Count);
}
/**
 * _PATHstrcmp - compares PATH with environ to find PATH value
 * @s1: pointer PATH string
 * @s2: pointer to environ string with actual value
 *
 * Return: 0 on success
 */
int _PATHstrcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s2[i] != '='; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}
/**
 * _concat - concats user string with PATH member string and /
 * @tmp: static array to store concatenated string
 * @av: pointer to array of user strings
 * @token: pointer to PATH token
 *
 * Return: 0 on success
 */
char *_concat(char *tmp, char **av, char *token)
{
	int len = 0;

	memset(tmp, 0, 256);
	len = _strlen(token) + _strlen(av[0]) + 2;
	_strcat(tmp, token);
	_strcat(tmp, "/");
	_strcat(tmp, av[0]);
	tmp[len - 1] = '\0';
	return (tmp);
}
