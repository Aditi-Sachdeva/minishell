#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "parser.h"

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

        for (int i = 0; args[i] != NULL; i++)
        {
            printf("args[%d] = %s\n", i, args[i]);
        }
    }

    return 0;
}