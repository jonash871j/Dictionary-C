#include <iostream>
#include <inn_dictionary.h>

int main()
{
	int k = 0;
	int v = 222;
	dictionary_t* dictionary = inn_dictionary_init(sizeof(int), sizeof(int));
	//inn_dictionary_add(dictionary, &k, &v);
	//INN_DICTIONARY_FOR_EACH(i, dictionary)
	//{
	//	std::cout << i.key << i.value << "\n";
	//}
}