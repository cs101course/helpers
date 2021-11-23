/* Dictionary ADT */

#include <stdbool.h>

#define MAX_KEY_LENGTH 1024

// This is a Dictionary of integers
typedef int dictValue;

// The key is a string, maximum MAX_KEY_LENGTH characters
typedef char dictKey[MAX_KEY_LENGTH];

typedef struct dictionary *Dictionary;


// Create a new Dictionary
// which can hold a maximum of maxSize key/value pairs
Dictionary Dictionary_create(int maxSize);

// Remove memory used by Dictionary
void Dictionary_destroy(Dictionary dictionary);

// Set the string key to a particular value
void Dictionary_set(Dictionary dictionary, dictKey key, dictValue value);

// Remove the string key from the dictionary
void Dictionary_delete(Dictionary dictionary, dictKey key);

// Returns the value for the given string key
dictValue Dictionary_get(Dictionary dictionary, dictKey key);

// Returns true if the given string key exists in the dictionary
// otherwise returns false
bool Dictionary_hasKey(Dictionary dictionary, dictKey key);
