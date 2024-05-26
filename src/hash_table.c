#include "../includes/hash_table.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct entry {
    char* key;
    void* obj;
    struct entry* next;
} entry;

struct _hash_table {
    uint32_t size;
    hash_function* hash;
    entry** elements;
};

hash_table* hash_table_create(uint32_t size, hash_function *hash_f)
{
    hash_table* hash_t = malloc(sizeof(*hash_t));
    hash_t->size = size;
    hash_t->hash = hash_f;
    hash_t->elements = calloc(sizeof(entry*), hash_t->size);

    return hash_t;
};
void hash_table_destroy(hash_table* hash_t)
{
    //TODO: free individual elements
    free(hash_t->elements);
    free(hash_t);
};

void hash_table_print(hash_table* hash_t)
{
    printf("Start table\n");
    for (uint32_t i = 0; i < hash_t->size; i++) {
        if (hash_t->elements[i] == NULL){
            // printf("\t%i\t---\n", i);
        } else {
            printf("%i\t ", i);
            entry* temp = hash_t->elements[i];
            while (temp != NULL) {
                printf("\"%s\"(%p) - ", temp->key, temp->obj);
                temp = temp->next;
            }
            printf("\n");
        }
    }
    printf("End table\n");
};

static size_t hash_table_index(hash_table* hash_t, const char* key)
{
    size_t result = (hash_t->hash(key, strlen(key)) % hash_t->size);
    return result;

}
bool hash_table_insert(hash_table* hash_t, const char* key, void* obj)
{
    if (key == NULL || obj == NULL || hash_t == NULL) return false;
    size_t index = hash_table_index(hash_t, key);

    if (hash_table_lookup(hash_t, key) != NULL) return false;

    //create this entry
    entry* element = malloc(sizeof(*element));
    element->obj = obj;
    element->key = malloc(strlen(key)+1);
    strcpy(element->key, key);

    //inserting entry
    element->next = hash_t->elements[index]; // element's next ponter points now to the element that was the head
    hash_t->elements[index] = element; // element's now the head of the list

    return true;


};
void* hash_table_lookup(hash_table* hash_t, const char* key)
{
    if (key == NULL || hash_t == NULL) return false;
    size_t index = hash_table_index(hash_t, key);

    entry* temp = hash_t->elements[index];

    while (temp != NULL && strcmp(temp->key, key) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) return NULL;
    return temp->obj;
};
void* hash_table_delete(hash_table* hash_t, const char* key)
{
    if (key == NULL || hash_t == NULL) return false;
    size_t index = hash_table_index(hash_t, key);

    entry* temp = hash_t->elements[index];
    entry* prev = NULL;
    while (temp != NULL && strcmp(temp->key, key) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return NULL;
    if (prev == NULL) {
        //deleting the head of the list
        hash_t->elements[index] = temp->next;
    } else {
        //deleting from the middle
        prev->next = temp->next;
    }

    void* result = temp->obj;
    free(temp);
    return result;
};