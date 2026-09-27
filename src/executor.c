#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include "executor.h"
#include "parser.h"

static void apply_redirection(redirect_t *r)
{
    if (r->input_file != NULL)
    {
        int fd = open(r->input_file, O_RDONLY);
        if (fd < 0)
        {
            perror(r->input_file);
            _exit(1);
        }
        dup2(fd, 0);
        close(fd);
    }

    if (r->output_file != NULL)
    {
        int flags = O_WRONLY | O_CREAT;
        flags |= r->append ? O_APPEND : O_TRUNC;

        int fd = open(r->output_file, flags, 0644);
        if (fd < 0)
        {
            perror(r->output_file);
            _exit(1);
        }
        dup2(fd, 1);
        close(fd);
    }
}

void run_external(char *args[], redirect_t *r)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        apply_redirection(r);
        execvp(args[0], args);
        fprintf(stderr, "minishell: %s: command not found\n", args[0]);
        _exit(1);
    }

    waitpid(pid, NULL, 0);
}

void run_pipeline(char *left[], char *right[])
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execvp(left[0], left);
        fprintf(stderr, "minishell: %s: command not found\n", left[0]);
        _exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execvp(right[0], right);
        fprintf(stderr, "minishell: %s: command not found\n", right[0]);
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}