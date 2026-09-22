#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

int is_builtin(char *cmd)
{
    return strcmp(cmd, "cd") == 0 || strcmp(cmd, "pwd") == 0 || strcmp(cmd, "echo") == 0 || strcmp(cmd, "help") == 0;
}

static void do_cd(char *args[])
{
    char *dir = args[1];

    if (dir == NULL)
    {
        dir = getenv("HOME"); 
    }

    if (dir == NULL || chdir(dir) != 0)
    {
        perror("cd");
    }
}

static void do_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
    }
}

static void do_echo(char *args[])
{
    for (int i = 1; args[i] != NULL; i++)
    {
        if (i > 1)
        {
            printf(" ");
        }
        printf("%s", args[i]);
    }
    printf("\n");
}

static void do_help(void)
{
    printf("MiniShell built-in commands:\n");
    printf("  cd [dir]   change directory\n");
    printf("  pwd        show current directory\n");
    printf("  echo ...   print text\n");
    printf("  help       list built-in commands\n");
    printf("  exit       quit the shell\n");
    printf("Any other command is run as a program (ls, cat, ...).\n");
}

void run_builtin(char *args[])
{
    if (strcmp(args[0], "cd") == 0)
    {
        do_cd(args);
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        do_pwd();
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        do_echo(args);
    }
    else if (strcmp(args[0], "help") == 0)
    {
        do_help();
    }
}