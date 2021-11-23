/* 
 * Dictionary ADT - implementation 
 * Implements a dictionary using an array of key-value pairs
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Dictionary.h"

#define NOT_FOUND (-1)

typedef struct {
    dictKey key;
    dictValue value;
} keyValuePair;

struct dictionary {
    keyValuePair *pairs;
    int length;
    int maxSize;
};

// Create a new Dictionary
Dictionary Dictionary_create(int maxSize) {
    Dictionary newDict;

    // allocate memory for the struct
    newDict = malloc(sizeof(struct dictionary));

    // set the max size
    newDict->maxSize = maxSize;

    // allocate memory for the array of key value pairs
    newDict->pairs = malloc(sizeof(keyValuePair) * maxSize);

    // set dictionary to empty
    newDict->length = 0;

    return newDict;
}

// Remove memory used by Dictionary
void Dictionary_destroy(Dictionary dictionary) {
    // free the array of pairs
    free(dictionary->pairs);

    // free the struct
    free(dictionary);
}

// Loop up a key/value pair by a key
// This scans through the whole array until the key is found
// Returns a pointer to a key/value pair if found, NULL otherwise
keyValuePair *lookupPair(Dictionary dictionary, dictKey key) {
    int index;
    keyValuePair *pair;

    index = 0;
    pair = NULL; // NULL means not found
    while (index < dictionary->length && pair == NULL) {
        if (strncmp(key, dictionary->pairs[index].key, MAX_KEY_LENGTH) == 0) {
            // matching key
            // set pair to point to the keyValuePair struct in the array at the current index
            // N.B. this could also be written as:
            // pair = &(dictionary->pairs[index]);
            pair = dictionary->pairs + index;
        }

        index++;
    }

    return pair;
}

// Set the string key to a particular value
void Dictionary_set(Dictionary dictionary, dictKey key, dictValue value) {
    int index;
    int length;
    keyValuePair *pair;
    
    length = dictionary->length;
    pair = lookupPair(dictionary, key);
    
    if (pair == NULL) {
        // no existing pair found

        // ensure there's room
        assert(length + 1 < dictionary->maxSize);

        // copy over new key
        index = length;
        pair = &(dictionary->pairs[index]);
        strncpy(pair->key, key, MAX_KEY_LENGTH);
        dictionary->length++;
    }

    pair->value = value;
}

// Remove the string key from the dictionary
// This scans through all the keys stored in the dictionary
// to find the right one to remove,
// then it replaces that cell with the next one, from that point onwards.
void Dictionary_delete(Dictionary dictionary, dictKey key) {
    int index;
    int removedIndex;
    bool isKeyFound;
    keyValuePair *pair;

    isKeyFound = false;
    index = 0;
    while (index < dictionary->length && !isKeyFound) {
        // set pair to point to the keyValuePair struct in the array at the current index
        // N.B. this could also be written as:
        // pair = &(dictionary->pairs[index]);
        pair = dictionary->pairs + index;

        if (strncmp(pair->key, key, MAX_KEY_LENGTH) == 0) {
            // matching key
            removedIndex = index;
            isKeyFound = true;
        }

        index++;
    }

    // Must only delete keys that exist
    assert(isKeyFound);

    // shrink the dictionary
    dictionary->length--;

    index = removedIndex;
    while (index < dictionary->length) {
        // override the current index with the one after
        dictionary->pairs[index] = dictionary->pairs[index+1];

        index++;
    }
}

// Returns the value for the given string key
dictValue Dictionary_get(Dictionary dictionary, dictKey key) {
    int length;
    keyValuePair *pair;
    
    length = dictionary->length;
    pair = lookupPair(dictionary, key);
    
    assert(pair != NULL);

    return pair->value;
}

// Returns true if the given string key exists in the dictionary
// otherwise returns false
bool Dictionary_hasKey(Dictionary dictionary, dictKey key) {
    return lookupPair(dictionary, key) != NULL;
}
