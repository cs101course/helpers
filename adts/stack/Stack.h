/* 
 * A stack of integers 
 */

typedef int stackItem;
typedef struct stack *Stack;

// Create a new stack (of size 0)
Stack Stack_create(void);

// Remove memory used by stack
void Stack_destroy(Stack stackToDestroy);

// Returns the top of the stack
stackItem Stack_top(Stack stack);

// Removes the top of the stack
void Stack_pop(Stack stack);

// Pushes a value onto the top of the stack
void Stack_push(Stack stack, stackItem value);

// Returns the number of items currently on the stack
int Stack_size(Stack stack);
