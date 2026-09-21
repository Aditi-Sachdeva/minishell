#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"

void run_external(char *args[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);

        fprintf(stderr, "minishell: %s: command not found\n", args[0]);
        _exit(1);
    }

    waitpid(pid, NULL, 0);
}