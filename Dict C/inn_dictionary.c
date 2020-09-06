#include "inn_dictionary.h"
#include "inn_listionary.h"
#include <stdlib.h>

struct dictionary_t
{
	int index;
	listionary_t* listionary;
}typedef dictionary_t;

// Private constructers and destructers *****************************************************************

// Used to initialize dictionary_t
static dictionary_t* init_default()
{
	dictionary_t* dictionary = malloc(sizeof(dictionary_t));
	dictionary->index = 0;
	return dictionary;
}

// Public constructers and destructers ******************************************************************

dictionary_t* inn_dictionary_init(size_t _key_sizeof, size_t _value_sizeof)
{
	dictionary_t* dictionary = init_default();
	dictionary->listionary = inn_listionary_init(_key_sizeof, _value_sizeof);
	return dictionary;
}
dictionary_t* inn_dictionary_init_safe(size_t _key_sizeof, size_t _value_sizeof, void* _key_error, void* _value_error)
{
	dictionary_t* dictionary = init_default();
	dictionary->listionary = inn_listionary_init_safe(_key_sizeof, _value_sizeof, _key_error, _value_error);
	return dictionary;
}

void inn_dictionary_destroy(dictionary_t* _dictionary)
{
	inn_listionary_destroy(_dictionary->listionary);
	free(_dictionary);
}

// Public functions *************************************************************************************

boolean_t inn_dictionary_add(dictionary_t* _dictionary, void* _key, void* _value)
{
	if (inn_listionary_get_key_amount(_dictionary->listionary, _key) == 0)
	{
		inn_listionary_add(_dictionary->listionary, _key, _value);
		return true;
	}
	return false;
}
boolean_t inn_dictionary_remove(dictionary_t* _dictionary, void* _key)
{
	return inn_listionary_remove(_dictionary->listionary, _key);
}
void inn_dictionary_clear(dictionary_t* _dictionary)
{
	_dictionary->index = 0;
	inn_listionary_clear(_dictionary->listionary);
}

boolean_t inn_dictionary_contains_key(dictionary_t* _dictionary, void* _key)
{
	return inn_listionary_contains_key(_dictionary->listionary, _key);
}
boolean_t inn_dictionary_contains_value(dictionary_t* _dictionary, void* _value)
{
	return inn_listionary_contains_value(_dictionary->listionary, _value);
}

// Get functions ****************************************************************************************

key_value_pair_t inn_dictionary_get_pair(dictionary_t* _dictionary)
{
	// Checks if index is is out of bounds, then sets index to 0
	if (_dictionary->index >= inn_listionary_get_length(_dictionary->listionary))
		_dictionary->index = 0;

	// Adds 1 to index
	_dictionary->index++;

	return inn_listionary_get_pair_by_index(_dictionary->listionary, _dictionary->index);
}
key_value_pair_t inn_dictionary_reset_get_pair(dictionary_t* _dictionary)
{
	// Sets index to 0
	_dictionary->index = 0;

	return inn_listionary_get_pair_by_index(_dictionary->listionary, _dictionary->index);
}

void* inn_dictionary_get(dictionary_t* _dictionary, void* _key)
{
	return inn_listionary_get_value_by_key(_dictionary->listionary, _key);
}

int inn_dictionary_get_length(dictionary_t* _dictionary)
{
	return inn_listionary_get_length(_dictionary->listionary);
}

// Set functions ****************************************************************************************

boolean_t inn_dictionary_set(dictionary_t* _dictionary, void* _key, void* _value)
{
	return inn_listionary_set_value_by_key(_dictionary->listionary, _key, _value);
}
