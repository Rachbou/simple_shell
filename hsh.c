#include "main.h"

/**
 * main - runs the Simple Shell
 * @argv: a NULL terminated array of strings
 * @argc: the number of items in av
 * Return: 0 on success
 */

int main(int argc, char ** argv) {
	int status = argc;
	char *err = strcat(argv[0],": No such file or directory\n");
	char **av = malloc(2 * sizeof(char *));
	
    while (1) {
		char *command = NULL;
		pid_t pid;
		
		prompt();
		command = getCommand();
		av[0] = command;
		av[1] = NULL;
		pid = fork();
        if (pid == 0) {
            if (execve(command, av, environ) == -1) {
                write(STDERR_FILENO, err, strlen(err));
                exit(1);
            }
        } else {
            waitpid(pid, &status, 0);
        }
    }
    
    return 0;
}
