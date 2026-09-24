#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64

typedef struct
{
    char *input_file;
    char *output_file;
    int append;
} redirect_t;

int parse(char *line, char *args[]);
void extract_redirection(char *args[], redirect_t *r);

#endif