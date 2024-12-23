#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef int size_t;
typedef void* elem_t;
typedef enum {FAIL, SUCCESS} result_t;
typedef elem_t (*clone_t)(elem_t e);
typedef void (*destroy_t)(elem_t e);
typedef void (*print_t)(elem_t e);
struct stack;

struct stack* stack_create(size_t max, clone_t clone, destroy_t destoy,
		print_t print);
result_t stack_destroy(struct stack* this_stack);
result_t stack_push(struct stack* this_stack, elem_t to_push);
void stack_pop(struct stack* this_stack);
elem_t stack_peek(struct stack* this_stack);
size_t stack_size(struct stack* this_stack);
bool stack_is_empty(struct stack* this_stack);
size_t stack_capacity(struct stack* this_stack);
void stack_print(struct stack* this_stack);




#endif //STACK_H





