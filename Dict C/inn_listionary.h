#pragma once
#include "inn_types.h"
#define INN_LISTIONARY_INIT(key, value) inn_listionary_init(sizeof(key), sizeof(value));

typedef struct listionary_t listionary_t;

listionary_t* inn_listionary_init(size_t _key_sizeof, size_t _value_sizeof);
listionary_t* inn_listionary_init_safe(size_t _key_sizeof, size_t _value_sizeof, void* _key_error, void* _value_error);
listionary_t* inn_listionary_init_clone(listionary_t* _listionary);
void inn_listionary_destroy(listionary_t* _listionary);

void inn_listionary_add(listionary_t* _listionary, void* _key, void* _value);
boolean_t inn_listionary_remove(listionary_t* _listionary, void* _key);
boolean_t inn_listionary_remove_all(listionary_t* _listionary, void* _key);
boolean_t inn_listionary_remove_by_index(listionary_t* _listionary, int _index);
void inn_listionary_clear(listionary_t* _listionary);

boolean_t inn_listionary_contains_key(listionary_t* _listionary, void* _key);
boolean_t inn_listionary_contains_value(listionary_t* _listionary, void* _value);

void* inn_listionary_get_value_by_key(listionary_t* _listionary, void* _key);
void* inn_listionary_get_value_by_index(listionary_t* _listionary, int _index);
key_value_pair_t inn_listionary_get_pair_by_index(listionary_t* _listionary, int _index);
int inn_listionary_get_key_amount(listionary_t* _listionary, void* _key);
int inn_listionary_get_length(listionary_t* _listionary);

boolean_t inn_listionary_set_value_by_key(listionary_t* _listionary, void* _key, void* _value);
