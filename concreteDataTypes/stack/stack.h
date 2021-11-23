/* 
 * stack concrete data type
 * A stack of integers 
 */

typedef int stackItem;
typedef struct {
    stackItem *items;
    int arraySize;
    int numItems;
} stack;

// Initalise an empty stack
void stack_init(stack *stack);

// Remove all memory for this stack
void stack_destroy(stack *stack);

// Returns the top of the stack
stackItem stack_top(stack *stack);

// Removes the top of the stack
void stack_pop(stack *stack);

// Pushes a value onto the top of the stack
void stack_push(stack *stack, stackItem value);
