#include <stdio.h>
#include <string.h>
#include "shell.h"

int main(void)
{
    char line[1024];

    while (1) {
        printf(PROMPT);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\0')
            continue;

        if (strcmp(line, "exit") == 0)
            break;

        printf("You typed: %s\n", line);
    }

    return 0;
}