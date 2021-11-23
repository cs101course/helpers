/* 
 * stack (concrete data type)
 * A stack of integers 
 */

// It is a stack of integers
typedef int stackItem;

// This is the data stored for a stack
typedef struct {
    stackItem *items; // an array (allocated at run time) of items
    int arraySize;    // the current size of the array
    int numItems;     // the number of items currently stored in the stack
} stack;

// Initalise an empty stack
// This allocates memory for the items array
void stack_init(stack *stack);

// Remove all memory for this stack
// This frees the items array
void stack_destroy(stack *stack);

// Returns the top of the stack
stackItem stack_top(stack *stack);

// Removes the top of the stack
void stack_pop(stack *stack);

// Pushes a value onto the top of the stack
// This grows the size of the items array if required, and
// increments the numItems in the stack
void stack_push(stack *stack, stackItem value);
