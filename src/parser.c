#include <string.h>
#include "parser.h"

int parse(char *line, char *args[])
{
    int count = 0;
    char *word = strtok(line, " \t");

    while (word != NULL && count < MAX_ARGS - 1)
    {
        args[count] = word;
        count++;
        word = strtok(NULL, " \t");
    }

    args[count] = NULL;
    return count;
}