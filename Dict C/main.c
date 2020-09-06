#include "inn_dictionary.h"
#include <stdio.h> 

struct vector_t
{
	int x, y, z;
}typedef vector_t;

// Loop through dictionary and print all keys and values
void print_dictionary(dictionary_t* _dictionary)
{
	printf("- Dictionary\n");
	printf("Item amount: %i\n", inn_dictionary_get_length(_dictionary));
	INN_DICTIONARY_FOREACH(value, _dictionary)
	{
		vector_t v = *(vector_t*)value.key;
		printf("vector: %i, %i, %i | value: %i\n", v.x, v.y, v.z, *(int*)value.value);
	}
	printf("\n");
}


main()
{
	// Items
	vector_t v_keys[] = { { 1, 2, 3 }, { 435, 123, 42 }, {354, 3245, 76} };
	int i_values[] = {32, 43, 65};
	
	// Test items
	vector_t v_key = { 435, 123, 42 };
	vector_t v_key2 = { 354, 3245, 76 };
	int i_value = 656;

	// Creates dictionary
	dictionary_t* dictionary = INN_DICTIONARY_INIT(vector_t, int);

	// Adds items to dictionary
	for (int i = 0; i < 3; i++)
		inn_dictionary_add(dictionary, &v_keys[i], &i_values[i]);

	print_dictionary(dictionary);

	// Sets a value in dictionary to a new one and then print if successful
	printf("Item set state: %i\n\n", inn_dictionary_set(dictionary, &v_key, &i_value));

	print_dictionary(dictionary);

	// Remove a item in dictionary and then print if successful
	printf("Item removed state: %i\n\n", inn_dictionary_remove(dictionary, &v_key));

	print_dictionary(dictionary);

	// Get specfic value from dictionary, and then print the value
	printf("The value is: %i\n\n", INN_DICTIONARY(int, dictionary, &v_key2));

	// Clears the dictionary
	inn_dictionary_clear(dictionary);

	print_dictionary(dictionary);
	
	// Destorys dictionary
	inn_dictionary_destroy(dictionary);
}