#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Dictionary.h"

#define NUM_TEST_KEYS 10

int main(int argc, char *argv[]) {
    dictKey testKeys[NUM_TEST_KEYS] = {
        "testKey1",
        "testKey2",
        "testKey3",
        "testKey4",
        "testKey5",
        "testKey6",
        "testKey7",
        "testKey8",
        "testKey9",
        "testKey10",
    };
    int index;

    Dictionary dict;

    dict = Dictionary_create(1024);

    printf("Testing dictionary does not have key \"testKey\"\n");
    assert(!Dictionary_hasKey(dict, "testKey"));

    printf("Testing setting key \"testKey\"\n");
    Dictionary_set(dict, "testKey", 42);
    assert(Dictionary_hasKey(dict, "testKey"));
    assert(Dictionary_get(dict, "testKey") == 42);

    printf("Testing setting key \"testKey\" again\n");
    Dictionary_set(dict, "testKey", 88);
    assert(Dictionary_hasKey(dict, "testKey"));
    assert(Dictionary_get(dict, "testKey") == 88);

    printf("Testing deleting key \"testKey\"\n");
    Dictionary_delete(dict, "testKey");
    assert(!Dictionary_hasKey(dict, "testKey"));

    printf("Testing setting 10 keys\n");
    index = 0;
    while (index < NUM_TEST_KEYS) {
        assert(!Dictionary_hasKey(dict, testKeys[index]));
        Dictionary_set(dict, testKeys[index], index);
        assert(Dictionary_hasKey(dict, testKeys[index]));
        index++;
    }

    printf("Testing getting 10 keys\n");
    index = NUM_TEST_KEYS-1;
    while (index >= 0) {
        assert(Dictionary_hasKey(dict, testKeys[index]));
        assert(Dictionary_get(dict, testKeys[index]) == index);
        index--;
    }


    printf("Testing deleting 10 keys\n");
    index = 0;
    while (index < NUM_TEST_KEYS) {
        assert(Dictionary_hasKey(dict, testKeys[index]));
        Dictionary_delete(dict, testKeys[index]);
        assert(!Dictionary_hasKey(dict, testKeys[index]));
        index++;
    }


    Dictionary_destroy(dict);

    printf("All tests passed\n");

    return EXIT_SUCCESS;
}
