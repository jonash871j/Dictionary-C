#pragma once

#ifdef __cplusplus
typedef bool boolean_t;
#else
typedef enum { false, true } boolean_t;
#endif
typedef unsigned int size_t;

struct key_value_pair_t
{
	void* key;
	void* value;
	int index;
}typedef key_value_pair_t;