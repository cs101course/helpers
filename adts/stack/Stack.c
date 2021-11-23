/* 
 * Stack ADT - Implementation
 * A stack of integers
 */

#include <stdlib.h>

#include "Stack.h"

#define MIN_STACK_SIZE 8

struct stack {
    int numItems;
    int arraySize;
    stackItem *arrayOfItems;
};

// Create a new stack (of size 0)
Stack Stack_create(void) {
    Stack newStack;

    newStack = malloc(sizeof(struct stack));
    newStack->numItems = 0;
    newStack->arraySize = MIN_STACK_SIZE;
    newStack->arrayOfItems = malloc(sizeof(stackItem) * newStack->arraySize);

    return newStack;
}

// Remove memory used by stack
void Stack_destroy(Stack stackToDestroy) {
    // remove the memory for the array
    free(stackToDestroy->arrayOfItems);

    // remove the memory for the struct
    free(stackToDestroy);
}

// Returns the top of the stack
stackItem Stack_top(Stack stack) {
    int lastIndex = stack->numItems - 1;
    return (stack->arrayOfItems[lastIndex]);
}

// Removes the top of the stack
void Stack_pop(Stack stack) {
    stack->numItems--;
}

// Pushes a value onto the top of the stack
void Stack_push(Stack stack, stackItem value) {
    // increment the number of items
    stack->numItems++;

    if (stack->numItems >= stack->arraySize) {
        // the new number of items doesn't fit in memory
        // so double the size of the array
        stack->arraySize *= 2;
        stack->arrayOfItems = realloc(stack->arrayOfItems, sizeof(stackItem) * stack->arraySize);
    }

    // save the value to the last index of the array
    stack->arrayOfItems[stack->numItems - 1] = value;
}

// Returns the number of items currently on the stack
int Stack_size(Stack stack) {
    return stack->numItems;
}
