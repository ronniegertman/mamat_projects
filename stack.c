#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>

struct stack_elem{
	elem_t value;
	struct stack_elem* next;
	clone_t clone;
	destroy_t destroy;
	print_t print;
};

struct stack{
	size_t max;
	size_t current_size;
	struct stack_elem* head;

	clone_t clone;
	destroy_t destroy;
	print_t print;
};

struct stack* stack_create(size_t max, clone_t clone, destroy_t destroy,
		print_t print){
	//creates new empty stack, max-sized.
	struct stack* new_stack = (struct stack*)malloc(sizeof(struct stack));
	if (new_stack == NULL){
		return NULL;
	}
	new_stack->max = max;
	new_stack->clone = clone;
	new_stack->destroy = destroy;
	new_stack->print = print;
	new_stack->current_size = 0;
	new_stack->head = NULL;
	return new_stack;
}

result_t stack_destroy(struct stack* this_stack){
	//destroying the stack
	if (this_stack == NULL) {
	        return FAIL;
	}

	if(this_stack->current_size == 0){
		free(this_stack);
		return SUCCESS;
	}
	//popping elements until empty, freeing the used memory
	while(this_stack->head != NULL){
		struct stack_elem* tmp = this_stack->head;
		this_stack->head = this_stack->head->next;
		tmp->next = NULL;
		if(tmp->destroy == NULL){
			return FAIL;
		}
		tmp->destroy(tmp->value);
		free(tmp);

	}
	//freeing entire struct stack
	free(this_stack);
	return SUCCESS;
}

result_t stack_push(struct stack* this_stack, elem_t to_push){
	//unable to push if stack is full
	if(this_stack == NULL || this_stack->current_size == this_stack->max){
		return FAIL;
	}
	//creating a new stack element, cloning to_push
	struct stack_elem* new_element
	= (struct stack_elem*) malloc(sizeof(struct stack_elem));
	if(new_element == NULL){
		return FAIL;
	}
	new_element->value = this_stack->clone(to_push);
	new_element->clone = this_stack->clone;
	new_element->destroy = this_stack->destroy;
	new_element->print = this_stack->print;
	new_element->next = this_stack->head;
	this_stack->head = new_element;
	this_stack->current_size ++;
	return SUCCESS;
}

void stack_pop(struct stack* this_stack){
	//removing the head of the stack, freeing used memory
	if(this_stack == NULL || this_stack->current_size == 0){
		return;
	}
	struct stack_elem* next = this_stack->head->next;
	this_stack->current_size --;
	this_stack->head->next = NULL;

	 if (this_stack->destroy != NULL) {
	        this_stack->destroy(this_stack->head->value);
	 }

	free(this_stack->head);
	this_stack->head = next;

}

elem_t stack_peek(struct stack* this_stack){
	//returning stack's head value
	if(this_stack == NULL || this_stack->current_size == 0){
		return NULL;
	}
	return this_stack->head->value;
}

size_t stack_size(struct stack* this_stack){
	//returning stack size
	if(this_stack == NULL || this_stack->current_size == 0){
		return 0;
	}
	return this_stack->current_size;
}

bool stack_is_empty(struct stack* this_stack){
	return (this_stack == NULL || this_stack->current_size == 0);
}

size_t stack_capacity(struct stack* this_stack){
	//calculating the amount of free space in the stack
	if(this_stack == NULL){
		return 0;
	}
	return this_stack->max - this_stack->current_size;
}

void stack_print(struct stack* this_stack){
	//printing stack from head to tail
	if(this_stack == NULL){
			return;
	}
	struct stack_elem* tmp = this_stack->head;
	while(tmp != NULL){
			this_stack->print(tmp->value);
			tmp = tmp->next;
	}
}
