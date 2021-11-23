#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define MIN_STACK_SIZE 8

// Initalise an empty stack
void stack_init(stack *stack) {
    stack->arraySize = MIN_STACK_SIZE;
    stack->items = malloc(sizeof(stackItem) * stack->arraySize);
    stack->numItems = 0;
}

// Remove all memory for this stack
void stack_destroy(stack *stack) {
    free(stack->items);
}

// Returns the top of the stack
stackItem stack_top(stack *stack) {
    int lastIndex = stack->numItems - 1;
    return stack->items[lastIndex];
}

// Removes the top of the stack
void stack_pop(stack *stack) {
    stack->numItems--;
}

// Pushes a value onto the top of the stack
void stack_push(stack *stack, stackItem value) {
    int lastIndex;

    // grow the length of the stack
    stack->numItems++;

    // make room if needed
    if (stack->numItems >= stack->arraySize) {
        stack->arraySize *= 2;
        stack->items = realloc(stack->items, sizeof(stackItem) * stack->arraySize);
    }

    // set the last value
    lastIndex = stack->numItems - 1;
    stack->items[lastIndex] = value;
}
