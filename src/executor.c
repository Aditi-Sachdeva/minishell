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
