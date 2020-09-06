#include "inn_listionary.h"
#include <stdlib.h>
#include <string.h>

struct listionary_t
{
	boolean_t unsafe_mode;
	size_t length;
	void** key;
	void* key_error;
	size_t key_sizeof;
	void** value;
	void* value_error;
	size_t value_sizeof;
}typedef listionary_t;

// Private constructers and destructers *****************************************************************

static listionary_t* init_default()
{
	listionary_t* listionary = malloc(sizeof(listionary_t));
	listionary->unsafe_mode = false;
	listionary->length = 0;
	return listionary;
}

// Private functions ************************************************************************************

static boolean_t check_inbound(listionary_t* _listionary, int _index)
{
	if ((_index >= _listionary->length) || (_index < 0))
		return false;
	return true;
}
static boolean_t check_raw_data_is_same(size_t length, const char* _check_raw_data, const char* _raw_data)
{
	// 
	for (int i = 0; i < length; i++)
	{
		if (_check_raw_data[i] != _raw_data[i])
			return false;
		if (i == length - 1)
			return true;
	}return false;
}
static int check_key_exists_at_index(listionary_t* _listionary, int _index, void* _key)
{
	// Converts the given _key to check from void* to a char array
	char* key_check_raw = (char*)_key;
	char* key_raw = (char*)_listionary->key[_index];

	// Checks if the key argument equals the key in dictionary_t
	if (check_raw_data_is_same(_listionary->key_sizeof, key_check_raw, key_raw))
		return _index;
	return -1;
}
static int check_value_exists_at_index(listionary_t* _listionary, int _index, void* _value)
{
	// Converts the given _key to check from void* to a char array
	char* value_check_raw = (char*)_value;
	char* value_raw = (char*)_listionary->value[_index];

	// Checks if the key argument equals the key in dictionary_t
	if (check_raw_data_is_same(_listionary->value_sizeof, value_check_raw, value_raw))
		return _index;
	return -1;
}

// Public constructers and destructers ******************************************************************

listionary_t* inn_listionary_init(size_t _key_sizeof, size_t _value_sizeof)
{
	listionary_t* dictionary = init_default();
	dictionary->unsafe_mode = true;
	dictionary->key_error = NULL;
	dictionary->key_sizeof = _key_sizeof;
	dictionary->value_error = NULL;
	dictionary->value_sizeof = _value_sizeof;
	return dictionary;
}
listionary_t* inn_listionary_init_safe(size_t _key_sizeof, size_t _value_sizeof, void* _key_error, void* _value_error)
{
	listionary_t* dictionary = init_default();
	dictionary->key_error = _key_error;
	dictionary->key_sizeof = _key_sizeof;
	dictionary->value_error = _value_error;
	dictionary->value_sizeof = _value_sizeof;
	return dictionary;
}
listionary_t* inn_listionary_init_clone(listionary_t* _listionary)
{
	listionary_t* listionary = malloc(sizeof(listionary_t));
	listionary->key = malloc(_listionary->length * _listionary->key_sizeof);
	listionary->value = malloc(_listionary->length * _listionary->value_sizeof);

	listionary->key_error = _listionary->key_error;
	listionary->key_sizeof = _listionary->key_sizeof;
	listionary->length = _listionary->length;
	listionary->unsafe_mode = _listionary->unsafe_mode;
	listionary->value_error = _listionary->value_error;
	listionary->value_sizeof = _listionary->value_sizeof;
	for (int i = 0; i < _listionary->length; i++)
	{
		listionary->key[i] = _listionary->key[i];
		listionary->value[i] = _listionary->value[i];
	}
	return listionary;
}

void inn_listionary_destroy(listionary_t* _listionary)
{
	free(_listionary->key);
	free(_listionary->value);
	free(_listionary);
}

// Public functions *************************************************************************************

void inn_listionary_add(listionary_t* _listionary, void* _key, void* _value)
{
	//
	listionary_t* listionary_clone = inn_listionary_init_clone(_listionary);

	//
	if (_listionary->length != 0)
	{
		free(_listionary->key);
		free(_listionary->value);
	}

	//
	_listionary->length++;
	_listionary->key = malloc(_listionary->length * _listionary->key_sizeof);
	_listionary->value = malloc(_listionary->length * _listionary->value_sizeof);
	
	//
	for (int i = 0; i < _listionary->length; i++)
	{
		_listionary->key[i] = listionary_clone->key[i];
		_listionary->value[i] = listionary_clone->value[i];
	}

	//
	_listionary->key[_listionary->length - 1] = _key;
	_listionary->value[_listionary->length - 1] = _value;

	//
	inn_listionary_destroy(listionary_clone);
}
boolean_t inn_listionary_remove(listionary_t* _listionary, void* _key)
{ 
	int index = -1;

	for (int i = 0; i < _listionary->length; i++)
	{
		index = check_key_exists_at_index(_listionary, i, _key);

		if (index != -1)
			break;
	}
	//
	if (index == -1)
		return false;

	return inn_listionary_remove_by_index(_listionary, index);
}
boolean_t inn_listionary_remove_all(listionary_t* _listionary, void* _key)
{
	boolean_t successful = false;

	for (int i = 0; i < _listionary->length; i++)
	{
		if (check_key_exists_at_index(_listionary, i, _key) != -1)
		{
			successful = true;
			inn_listionary_remove_by_index(_listionary, i);
			i--;
		}
	}
	return successful;
}
boolean_t inn_listionary_remove_by_index(listionary_t* _listionary, int _index)
{
	//
	if ((_listionary->length == 0) || (!check_inbound(_listionary, _index)))
		return false;

	//
	listionary_t* listionary_clone = inn_listionary_init_clone(_listionary);

	//
	free(_listionary->key);
	free(_listionary->value);

	//
	_listionary->length--;
	_listionary->key = malloc(_listionary->length * _listionary->key_sizeof);
	_listionary->value = malloc(_listionary->length * _listionary->value_sizeof);

	//
	boolean_t add = false;
	for (int i = 0; i < _listionary->length; i++)
	{
		if (i == _index)
			add = true;

		_listionary->key[i] = listionary_clone->key[i + add];
		_listionary->value[i] = listionary_clone->value[i + add];
	}

	//
	inn_listionary_destroy(listionary_clone);

	return true;
}
void inn_listionary_clear(listionary_t* _listionary)
{
	free(_listionary->key);
	free(_listionary->value);
	_listionary->key = malloc(0);
	_listionary->value = malloc(0);
	_listionary->length = 0;
}

boolean_t inn_listionary_contains_key(listionary_t* _listionary, void* _key)
{
	for (int i = 0; i < _listionary->length; i++)
		if (check_key_exists_at_index(_listionary, i, _key) != -1)
			return true;
	return false;
}
boolean_t inn_listionary_contains_value(listionary_t* _listionary, void* _value)
{
	for (int i = 0; i < _listionary->length; i++)
		if (check_value_exists_at_index(_listionary, i, _value) != -1)
			return true;
	return false;
}

// Get functions ****************************************************************************************

void* inn_listionary_get_value_by_key(listionary_t* _listionary, void* _key)
{
	//
	if (_listionary->length == 0)
		return _listionary->value_error;

	int index = -1;

	for (int i = 0; i < _listionary->length; i++)
	{
		index = check_key_exists_at_index(_listionary, i, _key);
		
		//
		if (index != -1)
			break;
		//
		if (i == _listionary->length - 1)
		{
			//
			if (_listionary->unsafe_mode)
				abort();

			return _listionary->value_error;
		}
	}

	// If they equals the same, return dictionary_t value
	return _listionary->value[index];
}
void* inn_listionary_get_value_by_index(listionary_t* _listionary, int _index)
{
	if (check_inbound(_listionary, _index))
	{
		//
		if (_listionary->unsafe_mode)
			abort();

		return _listionary->value_error;
	}
	return _listionary->value[_index];
}
key_value_pair_t inn_listionary_get_pair_by_index(listionary_t* _listionary, int _index)
{
	key_value_pair_t pair;
	
	//
	if (check_inbound(_listionary, _index))
	{
		pair.key = _listionary->key[_index];
		pair.value = _listionary->value[_index];
		pair.index = _index;
	}
	else
	{
		pair.key = _listionary->key_error;
		pair.value = _listionary->value_error;
		pair.index = -1;
	}
	return pair;
}
int inn_listionary_get_key_amount(listionary_t* _listionary, void* _key)
{
	int amount = 0;

	//
	for (int i = 0; i < _listionary->length; i++)
		if (check_key_exists_at_index(_listionary, i, _key) != -1)
			amount++;
	return amount;
}
int inn_listionary_get_length(listionary_t* _listionary)
{
	return _listionary->length;
}

boolean_t inn_listionary_set_value_by_key(listionary_t* _listionary, void* _key, void* _value)
{
	//
	if (_listionary->length == 0)
		return false;

	int index = -1;

	for (int i = 0; i < _listionary->length; i++)
	{
		index = check_key_exists_at_index(_listionary, i, _key);

		//
		if (index != -1)
			break;
		//
		if (i == _listionary->length - 1)
		{
			return false;
		}
	}
	_listionary->value[index] = _value;
	return true;
}