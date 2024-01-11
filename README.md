# 0x16. C - Simple Shell
a simple UNIX command interpreter.

![Logo](https://github.com/Rachbou/simple_shell/assets/125462640/7960e467-bde7-4441-9220-38c345d8bd1b)

## Overview
This is a UNIX command line interpreter based on the simple shell(sh). It reads user input from the command line, interprets it, and executes commands.

## Getting Started
Compile the shell using GCC with the options :

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Usage
After compiling the program, you may use it in both interactive and non-interactive mode.
### Interactive Mode
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
### Non-Interactive Mode
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Authors
[Rachid BOULMANI](https://github.com/RachBou)
