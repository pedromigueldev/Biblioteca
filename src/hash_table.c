#include "../includes/common.h"

#define MAX_NAME 256
#define TABLE_SIZE 10

enum Book_status {
    BORROWED,
    NOT_BORROWED
};

struct Book {
    char livro[MAX_NAME];
    enum Book_status status;
};