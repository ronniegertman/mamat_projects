#ifndef STACK_H
#define STACK_H
#include "common.h"

typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);
struct stack;

//creates new empty stack, max-sized.
struct stack* stack_create(size_t max, clone_t clone, destroy_t destoy,
		print_t print);
//destroying the stack
enum result stack_destroy(struct stack* this_stack);
//creating a new stack element, cloning to_push
enum result stack_push(struct stack* this_stack, elem_t to_push);
//removing the head of the stack
void stack_pop(struct stack* this_stack);
//returning stack's head value
elem_t stack_peek(struct stack* this_stack);
//returning stack size
size_t stack_size(struct stack* this_stack);
bool stack_is_empty(struct stack* this_stack);
//calculating the amount of free space in the stack
size_t stack_capacity(struct stack* this_stack);
//printing stack from head to tail
void stack_print(struct stack* this_stack);




#endif //STACK_H





