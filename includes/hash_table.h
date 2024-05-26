#ifndef  HASH_TABLE_H
#define HASH_TABLE_H

#include "../includes/common.h"
#include <stdint.h>
#include <stdio.h>

typedef uint64_t hash_function(const char*, size_t);
typedef struct _hash_table hash_table;

hash_table* hash_table_create(uint32_t size, hash_function *hash_f);
void hash_table_destroy(hash_table* hash_t);

void hash_table_print(hash_table* hash_t);
bool hash_table_insert(hash_table* hash_t, const char* key, void* obj);
void* hash_table_lookup(hash_table* hash_t, const char* key);
void* hash_table_delete(hash_table* hash_t, const char* key);

#endif