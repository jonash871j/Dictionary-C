#pragma once
#include "inn_types.h"

// - Use 
// inn_dictionary_init
// inn_dictionary_init_safe
typedef struct dictionary_t dictionary_t;

// Dictionary functions ****************************************************************************************************

// Used to initialize dictionary unsafely
// Returns dictionary pointer
dictionary_t* inn_dictionary_init(size_t _key_sizeof, size_t _value_sizeof);

// Used to initialize dictionary safely
// Returns dictionary pointer
dictionary_t* inn_dictionary_init_safe(size_t _key_sizeof, size_t _value_sizeof, void* _key_error, void* _value_error);

// Used to destory dictionary
void inn_dictionary_destroy(dictionary_t* _dictionary);

// Used to add element to dictionary
// Returns true if sussessful
boolean_t inn_dictionary_add(dictionary_t* _dictionary, void* _key, void* _value);

// Used to remove value by key
// Returns true if sussessful
boolean_t inn_dictionary_remove(dictionary_t* _dictionary, void* _key);

// Used to clear all elements in dictionary
void inn_dictionary_clear(dictionary_t* _dictionary);

// Used to check if dictionary contains the given key
// Return true if it exists
boolean_t inn_dictionary_contains_key(dictionary_t * _dictionary, void* _key);

// Used to check if dictionary contains the given value
// Return true if it exists
boolean_t inn_dictionary_contains_value(dictionary_t * _dictionary, void* _value);

// Used to get pair from current index and add 1 to index
// Returns pair from current index
key_value_pair_t inn_dictionary_get_pair(dictionary_t * _dictionary);

// Used to reset dictionary index to 0 and get pair from index 0
// Returns key_value_pair_t from index 0
key_value_pair_t inn_dictionary_reset_get_pair(dictionary_t * _dictionary);

// Used to get value of specified key 
// Returns value of specified type
// - NOTICE
// if initialized dictionary_t unsafely and the given key is invalid, program craps out
void* inn_dictionary_get(dictionary_t * _dictionary, void* _key);

// Used to get length of dictionary
// Returns length
int inn_dictionary_get_length(dictionary_t* _dictionary);

// Used to set value of specified key 
// Returns true if sussessful
boolean_t inn_dictionary_set(dictionary_t * _dictionary, void* _key, void* _value);

// Macros ******************************************************************************************************************

// -- Used to get value of specified key
// -- Returns value of specified type
// - ARGUMENT type
// could be: int, float, double
// notice: const char* you have to set a reference(&) before calling the macro
// - NOTICE
// if initialized dictionary_t unsafely and the given key is invalid, program craps out
// - CALLS
// void* inn_dictionary_get(dictionary_t* _dictionary, void* _key)
#define INN_DICTIONARY(type, dictionary, key) (*(##type *)inn_dictionary_get(##dictionary, ##key))

// Used to initialize dictionary unsafely
// Returns dictionary pointer
// - NOTICE
// you dont have to use sizeof() by using this macro
// - CALLS
// dictionary_t* inn_dictionary_init
#define INN_DICTIONARY_INIT(key, value) inn_dictionary_init(sizeof(key), sizeof(value));

// Used to simulate foreach from C#
// - ARGUMENT item
// your key_value_pair_t item you want to use in a scope
// - EXAMPLE
// INN_DICTIONARY_FOR_EACH(day_item, day_dictionary)
//		printf("Day \t%s is of value\t %i\n", (const char*)day_item.key, *(int*)day_item.value);
#define INN_DICTIONARY_FOREACH(item, dictionary) for (key_value_pair_t item = inn_dictionary_reset_get_pair(dictionary); (item.index <= inn_dictionary_get_length(dictionary) - 1) && (item.index >= 0); item = inn_dictionary_get_pair(dictionary))
