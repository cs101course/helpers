/* Tests for Stack ADT */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Stack.h"

int main(int argc, char *argv[]) {
    int testIndex;
    Stack testStack = Stack_create();

    printf("Testing size of Stack starts at 0\n");
    assert(Stack_size(testStack) == 0);

    printf("Testing pushing 0 to the Stack\n");
    Stack_push(testStack, 0);
    assert(Stack_top(testStack) == 0);
    assert(Stack_size(testStack) == 1);

    printf("Testing pushing 1 to the Stack\n");
    Stack_push(testStack, 1);
    assert(Stack_top(testStack) == 1);
    assert(Stack_size(testStack) == 2);

    printf("Testing pushing 0 to the Stack\n");
    Stack_push(testStack, 0);
    assert(Stack_top(testStack) == 0);
    assert(Stack_size(testStack) == 3);

    printf("Testing popping 0 from the Stack\n");
    Stack_pop(testStack);
    assert(Stack_top(testStack) == 1);
    assert(Stack_size(testStack) == 2);

    printf("Testing pushing -1 to the Stack\n");
    Stack_push(testStack, -1);
    assert(Stack_top(testStack) == -1);
    assert(Stack_size(testStack) == 3);

    printf("Testing popping -1 from the Stack\n");
    Stack_pop(testStack);
    assert(Stack_top(testStack) == 1);
    assert(Stack_size(testStack) == 2);

    printf("Testing popping 1 from the Stack\n");
    Stack_pop(testStack);
    assert(Stack_top(testStack) == 0);
    assert(Stack_size(testStack) == 1);

    printf("Testing popping 0 from the Stack\n");
    Stack_pop(testStack);
    assert(Stack_size(testStack) == 0);

    printf("Testing pushing 999 to the Stack\n");
    Stack_push(testStack, 999);
    assert(Stack_top(testStack) == 999);
    assert(Stack_size(testStack) == 1);

    printf("Testing popping 999 from the Stack\n");
    Stack_pop(testStack);
    assert(Stack_size(testStack) == 0);

    printf("Testing pushing 100 items to the Stack\n");
    testIndex = 0;
    while (testIndex < 100) {
        Stack_push(testStack, 1);
        testIndex++;
    }
    assert(Stack_size(testStack) == 100);

    printf("Testing popping 98 items from the Stack\n");
    testIndex = 0;
    while (testIndex < 98) {
        Stack_pop(testStack);
        testIndex++;
    }
    assert(Stack_size(testStack) == 2);

    Stack_destroy(testStack);

    printf("All tests passed!\n");

    return EXIT_SUCCESS;
}
