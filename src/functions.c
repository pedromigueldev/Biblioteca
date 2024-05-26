#include "../includes/common.h"

int biblioteca_add (char** args)
{
    printf("Add function\n");
    return 1;
}

int biblioteca_display (char** args)
{
    printf("Display functions\n");
    return 1;
}

int (*biblioteca_builtins_functions[]) (char**) ={
    &biblioteca_add,
    &biblioteca_display
};

char* biblioteca_builtins_names[] = {
    "add",
    "display"
};

int biblioteca_builtins_len()
{
    return sizeof(biblioteca_builtins_names) / sizeof(char *);
}