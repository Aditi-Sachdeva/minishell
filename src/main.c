#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "shell.h"
#include "parser.h"
#include "builtins.h"
#include "executor.h"

int main(void)
{
    char line[1024];
    char *args[MAX_ARGS];

    while (1)
    {

        while (waitpid(-1, NULL, WNOHANG) > 0)
            ;

        printf(PROMPT);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        int count = parse(line, args);
        if (count == 0)
        {
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }

        int bg = has_background(args);

        if (has_pipe(args))
        {
            char *left[MAX_ARGS], *right[MAX_ARGS];
            split_pipe(args, left, right);
            run_pipeline(left, right);
            continue;
        }

        redirect_t r;
        extract_redirection(args, &r);

        if (args[0] == NULL)
        {
            continue;
        }

        if (is_builtin(args[0]))
        {
            int saved_stdout = -1;

            if (r.output_file != NULL)
            {
                int flags = O_WRONLY | O_CREAT | (r.append ? O_APPEND : O_TRUNC);
                int fd = open(r.output_file, flags, 0644);
                if (fd < 0)
                {
                    perror(r.output_file);
                }
                else
                {
                    saved_stdout = dup(1);
                    dup2(fd, 1);
                    close(fd);
                }
            }

            run_builtin(args);

            if (saved_stdout != -1)
            {
                dup2(saved_stdout, 1);
                close(saved_stdout);
            }
        }
        else
        {
            run_external(args, &r, bg);
        }
    }

    return 0;
}