//
//  stack.h
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdint.h>

typedef struct stack * stack;

// Creates a new stack object with an initial value.
extern stack* stack_init(void);

// Pushes a number onto the stack.
extern void stack_push(stack*, uint32_t);

// Reads the top of the stack.
extern uint32_t stack_read(stack*);

// Pops the top element off the stack.
extern uint32_t stack_pop(stack*);

// Pops all values off a stack and deallocates the memory.
extern void stack_deinit(stack*);

#endif /* stack_h */
