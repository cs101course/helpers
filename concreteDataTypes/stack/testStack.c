/* Tests for Stack ADT */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

int main(int argc, char *argv[]) {
    int testIndex;
    stack testStack;

    stack_init(&testStack);

    printf("Testing size of Stack starts at 0\n");
    assert(testStack.numItems == 0);

    printf("Testing pushing 0 to the Stack\n");
    stack_push(&testStack, 0);
    assert(stack_top(&testStack) == 0);
    assert(testStack.numItems == 1);

    printf("Testing pushing 1 to the Stack\n");
    stack_push(&testStack, 1);
    assert(stack_top(&testStack) == 1);
    assert(testStack.numItems == 2);

    printf("Testing pushing 0 to the Stack\n");
    stack_push(&testStack, 0);
    assert(stack_top(&testStack) == 0);
    assert(testStack.numItems == 3);

    printf("Testing popping 0 from the Stack\n");
    stack_pop(&testStack);
    assert(stack_top(&testStack) == 1);
    assert(testStack.numItems == 2);

    printf("Testing pushing -1 to the Stack\n");
    stack_push(&testStack, -1);
    assert(stack_top(&testStack) == -1);
    assert(testStack.numItems == 3);

    printf("Testing popping -1 from the Stack\n");
    stack_pop(&testStack);
    assert(stack_top(&testStack) == 1);
    assert(testStack.numItems == 2);

    printf("Testing popping 1 from the Stack\n");
    stack_pop(&testStack);
    assert(stack_top(&testStack) == 0);
    assert(testStack.numItems == 1);

    printf("Testing popping 0 from the Stack\n");
    stack_pop(&testStack);
    assert(testStack.numItems == 0);

    printf("Testing pushing 999 to the Stack\n");
    stack_push(&testStack, 999);
    assert(stack_top(&testStack) == 999);
    assert(testStack.numItems == 1);

    printf("Testing popping 999 from the Stack\n");
    stack_pop(&testStack);
    assert(testStack.numItems == 0);

    printf("Testing pushing 100 items to the Stack\n");
    testIndex = 0;
    while (testIndex < 100) {
        stack_push(&testStack, 1);
        testIndex++;
    }
    assert(testStack.numItems == 100);

    printf("Testing popping 98 items from the Stack\n");
    testIndex = 0;
    while (testIndex < 98) {
        stack_pop(&testStack);
        testIndex++;
    }
    assert(testStack.numItems == 2);

    stack_destroy(&testStack);

    printf("All tests passed!\n");

    return EXIT_SUCCESS;
}
