#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIBLIOTECA_LINE_BUFFER 1024
#define BIBLIOTECA_ARGS_BUFFER 64
#define BIBLIOTECA_ARGS_DELIMITER "\t:"

char** biblioteca_splitline(char* line)
{
    char* line_copy = strdup(line);
    
    int buffer_size = BIBLIOTECA_ARGS_BUFFER, position = 0;
    char** args = malloc(sizeof(char*) * buffer_size);
    char*  arg;

    if (args == NULL) {
        fprintf(stderr, "Failed to create args buffer\n");
        exit(EXIT_FAILURE);
    }

    arg = strtok(line, BIBLIOTECA_ARGS_DELIMITER);

    while (arg != NULL) {
        args[position] = arg;
        position++;

        if (position >= buffer_size) {
            buffer_size += BIBLIOTECA_ARGS_BUFFER;
            args = realloc(args, buffer_size * sizeof(char*));

            if (args == NULL) {
                fprintf(stderr, "Failed to reallocate args1 buffer\n" );
                exit(EXIT_FAILURE);
            }
        }
        arg = strtok(NULL, BIBLIOTECA_ARGS_DELIMITER);
    }
    args[position] = NULL;
    return args;
}

char* biblioteca_getline()
{
    char one_char;
    int position = 0;

    int buffer_size = BIBLIOTECA_LINE_BUFFER;
    char* line = malloc(sizeof(char*)*buffer_size);

    if (line == NULL) {
        fprintf(stderr, "Failed to create line buffer\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        one_char = getchar();

        if (one_char == EOF || one_char == '\n' || position >= buffer_size) {
            line[position] = '\0';
            return line;
        }

        line[position] = one_char;
        position++;

        if (position >= buffer_size) {
            buffer_size += BIBLIOTECA_LINE_BUFFER;
            line = realloc(line, buffer_size);

            if (line == NULL) {
                fprintf(stderr, "Failed to reallocate line buffer\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return line;

}

int biblioteca_main()
{
    char* line;
    char** args;
    int status = 1;

    while (status) {
        printf("is true\n");
        line = biblioteca_getline();
        args = biblioteca_splitline(line);
    }

    free(line);
    free(args);
    return status;
}

int main()
{
    return biblioteca_main();
}