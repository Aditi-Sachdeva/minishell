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

void extract_redirection(char *args[], redirect_t *r)
{

    r->input_file = NULL;
    r->output_file = NULL;
    r->append = 0;

    char *clean[MAX_ARGS];
    int j = 0;

    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] != NULL)
            {
                r->input_file = args[i + 1];
                i++;
            }
        }
        else if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] != NULL)
            {
                r->output_file = args[i + 1];
                r->append = 0;
                i++;
            }
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1] != NULL)
            {
                r->output_file = args[i + 1];
                r->append = 1;
                i++;
            }
        }
        else
        {
            clean[j++] = args[i];
        }
    }
    clean[j] = NULL;

    for (int k = 0; k <= j; k++)
    {
        args[k] = clean[k];
    }
}

int has_pipe(char *args[])
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            return 1;
        }
    }
    return 0;
}

void split_pipe(char *args[], char *left[], char *right[])
{
    int i = 0;
    while (args[i] != NULL && strcmp(args[i], "|") != 0)
    {
        left[i] = args[i];
        i++;
    }
    left[i] = NULL;

    int j = 0;
    if (args[i] != NULL)
    {
        i++;
        while (args[i] != NULL)
        {
            right[j++] = args[i];
            i++;
        }
    }
    right[j] = NULL;
}
