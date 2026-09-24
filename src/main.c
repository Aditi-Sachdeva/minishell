#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        redirect_t r;
        extract_redirection(args, &r);

        if (args[0] == NULL) /* line was only an operator */
            continue;

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
            run_external(args, &r);
        }
    }

    return 0;
}