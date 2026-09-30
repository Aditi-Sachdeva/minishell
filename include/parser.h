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

int has_pipe(char *args[]);
void split_pipe(char *args[], char *left[], char *right[]);

int has_background(char *args[]);

void expand_variables(char *args[]);

#endif