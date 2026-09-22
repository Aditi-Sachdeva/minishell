#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "builtins.h"

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

        if (strcmp(line, "exit") == 0)
        {
            break;
        }

        int count = parse(line, args);
        if (count == 0)
        {
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }

        if (is_builtin(args[0]))
        {
            run_builtin(args);
        }
        else
        {
            run_external(args);
        }
    }

    return 0;
}