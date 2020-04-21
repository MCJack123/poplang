//
//  stack.c
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#include "stack.h"
#include <stdlib.h>

struct stack {
	uint32_t val;
	struct stack * previous;
};

stack stack_create_entry(uint32_t num) {
	stack s = (stack)malloc(sizeof(struct stack));
	s->val = num;
	s->previous = NULL;
	return s;
}

stack* stack_init() {
	stack * s = (stack*)malloc(sizeof(stack));
	*s = NULL;
	return s;
}

void stack_push(stack* s, uint32_t num) {
	stack e = stack_create_entry(num);
	e->previous = *s;
	*s = e;
}

uint32_t stack_read(stack* s) {
	if (*s == NULL) return UINT32_MAX;
	return (*s)->val;
}

uint32_t stack_pop(stack* s) {
	stack n = *s;
	if (n == NULL) return UINT32_MAX;
	uint32_t retval = n->val;
	*s = n->previous;
	free(n);
	return retval;
}

void stack_deinit(stack* s) {
	while (*s != NULL) stack_pop(s);
	free(s);
}
