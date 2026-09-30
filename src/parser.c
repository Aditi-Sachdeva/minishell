#include <string.h>
#include <stdlib.h>
#include "parser.h"

int parse(char *line, char *args[])
{
    int count = 0;
    int i = 0;

    while (line[i] != '\0' && count < MAX_ARGS - 1)
    {
        while (line[i] == ' ' || line[i] == '\t')
        {
            i++;
        }
        if (line[i] == '\0')
        {
            break;
        }

        if (line[i] == '"')
        {
            i++;
            args[count++] = &line[i];
            while (line[i] != '"' && line[i] != '\0')
            {
                i++;
            }
            if (line[i] == '"')
            {
                line[i] = '\0';
                i++;
            }
        }
        else
        {
            args[count++] = &line[i];
            while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
            {
                i++;
            }
            if (line[i] != '\0')
            {
                line[i] = '\0';
                i++;
            }
        }
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

int has_background(char *args[])
{
    int i = 0;
    while (args[i] != NULL)
    {
        i++;
    }
    if (i > 0 && strcmp(args[i - 1], "&") == 0)
    {
        args[i - 1] = NULL;
        return 1;
    }
    return 0;
}

void expand_variables(char *args[])
{
    static char buf[MAX_ARGS][256];

    for (int i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] == '$')
        {
            char *value = getenv(args[i] + 1);
            if (value != NULL)
            {
                strncpy(buf[i], value, 255);
                buf[i][255] = '\0';
                args[i] = buf[i];
            }
            else
            {
                args[i] = "";
            }
        }
    }
}