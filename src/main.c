#include "../includes/biblioteca.h"
#include "../includes/hash_table.h"
#include <stdio.h>
#define MAX_LINE 4096

uint64_t my_hash_f(const char* name, size_t length)
{
    uint64_t hash_value = 0;
    for (int i=0; i<length; i++) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]);
    }

    return hash_value;
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("usage: %s <filename>\n", "program");
        return EXIT_FAILURE;
    }

    char* filename = argv[1];
    uint32_t num_guesses = atol(argv[2]);

    const int table_size = (1<<20);
    hash_table* table = hash_table_create(table_size, my_hash_f);

    FILE* fp = fopen(filename, "r");
    char buffer[MAX_LINE];
    uint32_t num_words = 0;

    while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL) {
        buffer[strcspn(buffer, "\n\r")] = 0;
        char* newentry = malloc(strlen(buffer)+1);
        strcpy(newentry, buffer);

        hash_table_insert(table, newentry, newentry);
        num_words++;
    }

    fclose(fp);
    printf("Loaded %d words into the table\n", num_words);
    
    hash_table_print(table);
    printf("Key to delete: %s\n", (char*)hash_table_delete(table, "dg"));
    hash_table_print(table);

    return 1;//biblioteca_main();
}