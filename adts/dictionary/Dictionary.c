/* 
 * Dictionary ADT - implementation 
 * Implements a dictionary using a hash table
 * with linear probing
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Dictionary.h"

#define NOT_FOUND (-1)

typedef struct {
    dictKey key;
    dictValue value;
    bool isEmpty;
} hashTableCell;

struct dictionary {
    hashTableCell *hashTable;
    int maxSize;
};

unsigned int hash(dictKey key, int maxValue) {
    // Hash function chosen from:
    // http://www.cse.yorku.ca/~oz/hash.html
    // It has likely been developed through experimentation

    // A starting prime number for the hash calculation
    unsigned long startingPrime = 5381;

    unsigned long hashValue = startingPrime;
    char *str = key;
    unsigned int character;

    while (*str) {
        character = *str;
        str++;

        // according to the source, the magic of number 33 
        // (why it works better than many other constants, prime or not) 
        // has never been adequately explained.
        // Some say 31 (which is prime) works well too.
        hashValue = (hashValue * 33) + character;
    }

    return hashValue % maxValue;
}

// Returns the index of the key in the hash table, if found
// NOT_FOUND otherwise
int indexForKey(Dictionary dictionary, dictKey key) {
    int currentIndex;
    int foundIndex;
    int numSteps;
    bool isProbingFinished;
    hashTableCell *cell;

    foundIndex = NOT_FOUND;
    isProbingFinished = false;
    numSteps = 0; // how many cells have been probed
    currentIndex = hash(key, dictionary->maxSize); // the starting index
    while (!isProbingFinished && numSteps < dictionary->maxSize) {
        cell = &(dictionary->hashTable[currentIndex]);

        if (cell->isEmpty) {
            // Hit an empty cell, value is not found
            isProbingFinished = true;
        } else if (strncmp(key, cell->key, MAX_KEY_LENGTH) == 0) {
            // Found a matching key, value is found
            isProbingFinished = true;
            foundIndex = currentIndex;
        }

        // move to the next cell, looping around to the front if necessary
        currentIndex = (currentIndex + 1) % dictionary->maxSize;

        // keep track of the number of steps
        numSteps++;
    }

    return foundIndex;
}

// Returns the index of next empty cell, if one exists
// NOT_FOUND otherwise
int nextEmptyIndex(Dictionary dictionary, dictKey key) {
    int currentIndex;
    int numSteps;
    int indexFound;
    bool isProbingFinished;
    hashTableCell *cell;

    indexFound = NOT_FOUND;
    isProbingFinished = false;
    numSteps = 0; // how many cells have been probed
    currentIndex = hash(key, dictionary->maxSize); // the starting index
    while (!isProbingFinished && numSteps < dictionary->maxSize) {
        cell = &(dictionary->hashTable[currentIndex]);

        if (cell->isEmpty) {
            // Hit an empty cell
            isProbingFinished = true;
            indexFound = currentIndex;
        }

        // move to the next cell, looping around to the front if necessary
        currentIndex = (currentIndex + 1) % dictionary->maxSize;

        // keep track of the number of steps
        numSteps++;
    }

    return indexFound;
}

// Starting at the index of a removed hash table cell (removedIndex)
// moves along the array ensuring all cells afterwards, up until an empty cell is found
// (or a perfectly hashing key is found)
// are shifted to close the gap.
void removeGaps(Dictionary dictionary, int removedIndex) {
    int index;
    int prevIndex;
    int hashValue;
    int numSteps;
    bool isProbingFinished = false;
    hashTableCell *cell;

    prevIndex = removedIndex;
    index = (removedIndex + 1) % dictionary->maxSize;
    numSteps = 0; // how many cells have been probed
    while (!isProbingFinished && numSteps < dictionary->maxSize) {
        cell = &(dictionary->hashTable[index]);

        if (cell->isEmpty) {
            // if the next cell is empty,
            // nothing more needs to be done
            isProbingFinished = true;
        } else {
            hashValue = hash(cell->key, dictionary->maxSize);
            if (hashValue == index) {
                // this key hashes perfectly,
                // nothing more needs to be done
                isProbingFinished = true;
            } else {
                // gap needs to be closed for probing to work properly
                // move the next cell back one cell
                dictionary->hashTable[prevIndex] = dictionary->hashTable[index];
                // propagate the gap along one cell
                dictionary->hashTable[index].isEmpty = true;
            }
        }

        prevIndex = index;
        index = (index + 1) % dictionary->maxSize;

        numSteps++;
    }
}

// Create a new Dictionary
Dictionary Dictionary_create(int maxSize) {
    int index;
    Dictionary newDict;

    // allocate memory for the struct
    newDict = malloc(sizeof(struct dictionary));

    // set the max size
    newDict->maxSize = maxSize;

    // allocate memory for the hash table
    newDict->hashTable = malloc(sizeof(hashTableCell) * maxSize);

    // set dictionary to empty
    index = 0;
    while (index < newDict->maxSize) {
        newDict->hashTable[index].isEmpty = true;

        index++;
    }

    return newDict;
}

// Remove memory used by Dictionary
void Dictionary_destroy(Dictionary dictionary) {
    // free the hash table
    free(dictionary->hashTable);

    // free the struct
    free(dictionary);
}

// Set the string key to a particular value
void Dictionary_set(Dictionary dictionary, dictKey key, dictValue value) {
    hashTableCell *cell;
    int index;
    
    // look up existing value
    index = indexForKey(dictionary, key);

    if (index == NOT_FOUND) {
        // find the next empty index
        index = nextEmptyIndex(dictionary, key);
    }

    // Check if Dictionary has filled up
    assert(index != NOT_FOUND);

    cell = &(dictionary->hashTable[index]);

    // copy the key into this cell
    strncpy(cell->key, key, MAX_KEY_LENGTH);

    // copy the value into this cell
    cell->value = value;

    // set the cell to filled (not empty)
    cell->isEmpty = false;
}

// Remove the string key from the dictionary
void Dictionary_delete(Dictionary dictionary, dictKey key) {
    hashTableCell *cell;
    int index;
    
    index = indexForKey(dictionary, key);

    // Not allowed to delete an empty cell
    assert(index != NOT_FOUND);

    // set the cell to empty
    cell = &(dictionary->hashTable[index]);
    cell->isEmpty = true;

    // remove any gaps (linear probing)
    removeGaps(dictionary, index);
}

// Returns the value for the given string key
dictValue Dictionary_get(Dictionary dictionary, dictKey key) {
    int index;
    
    index = indexForKey(dictionary, key);

    // Not allowed to get an empty cell
    assert(index != NOT_FOUND);

    return dictionary->hashTable[index].value;
}

// Returns true if the given string key exists in the dictionary
// otherwise returns false
bool Dictionary_hasKey(Dictionary dictionary, dictKey key) {
    int index = indexForKey(dictionary, key);

    return index != NOT_FOUND;
}
