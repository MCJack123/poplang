//
//  instructions.c
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#include "instructions.h"
#include <stdio.h>

extern void read_next_instruction(void);

typedef int(*opcode_t)(stack*, stack*, uint32_t*); // takes the data stack, program stack, and cache, returns number of program instructions moved back (0 to continue reading next instruction)

//example
int opcode_(stack* data, stack* program, uint32_t* cache) {
	return 0;
}

// instructions are listed in this format:
// name (# of arguments, # of elements popped, # of elements pushed) [# of instructions popped, # of instructions pushed]

// push (1, 0, 1)
int opcode_push(stack* data, stack* program, uint32_t* cache) {
	read_next_instruction();
	stack_push(data, stack_read(program));
	return 0;
}

// pop (0, -1, 0)
int opcode_pop(stack* data, stack* program, uint32_t* cache) {
	stack_pop(data);
	return 0;
}

// popn (1, -n, 0)
int opcode_popn(stack* data, stack* program, uint32_t* cache) {
	read_next_instruction();
	int n = stack_read(program);
	for (int i = 0; i < n; i++) stack_pop(data);
	return 0;
}

// pusc (0, 0, 1)
int opcode_pusc(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, *cache);
	*cache = 0;
	return 0;
}

// popc (0, -1, 0)
int opcode_popc(stack* data, stack* program, uint32_t* cache) {
	*cache = stack_pop(data);
	return 0;
}

// pusp (1, 0, 0) [0, 1]
int opcode_pusp(stack* data, stack* program, uint32_t* cache) {
	read_next_instruction();
	return -1;
}

// popp (0, 0, 0)  [-1, 0]
int opcode_popp(stack* data, stack* program, uint32_t* cache) {
	stack_pop(program);
	return 1;
}

// popq (1, 0, 0) [-n, 0]
int opcode_popq(stack* data, stack* program, uint32_t* cache) {
	read_next_instruction();
	int n = stack_read(program);
	for (int i = 0; i < n; i++) stack_pop(program);
	return n+1;
}

// add (0, -2, 1)
int opcode_add(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) + stack_pop(data));
	return 0;
}

// sub (0, -2, 1)
int opcode_sub(stack* data, stack* program, uint32_t* cache) {
	uint32_t n = stack_pop(data);
	stack_push(data, stack_pop(data) - n);
	return 0;
}

// mul (0, -2, 1)
int opcode_mul(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) * stack_pop(data));
	return 0;
}

// div (0, -2, 1)
int opcode_div(stack* data, stack* program, uint32_t* cache) {
	uint32_t n = stack_pop(data);
	stack_push(data, stack_pop(data) / n);
	return 0;
}

// inc (0, -1, 1)
int opcode_inc(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) + 1);
	return 0;
}

// dec (0, -1, 1)
int opcode_dec(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) - 1);
	return 0;
}

// and (0, -2, 1)
int opcode_and(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) & stack_pop(data));
	return 0;
}

// or (0, -2, 1)
int opcode_or(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) | stack_pop(data));
	return 0;
}

// xor (0, -2, 1)
int opcode_xor(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) ^ stack_pop(data));
	return 0;
}

// not (0, -1, 1)
int opcode_not(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, ~stack_pop(data));
	return 0;
}

// equ (0, -2, 1)
int opcode_equ(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) == stack_pop(data));
	return 0;
}

// gt (0, -2, 1)
int opcode_gt(stack* data, stack* program, uint32_t* cache) {
	stack_push(data, stack_pop(data) < stack_pop(data));
	return 0;
}

// zero (1, -1, 0)
// argument indicates number of instruction positions to skip (1 for insts with no arg, 2 for insts with one arg)
int opcode_zero(stack* data, stack* program, uint32_t* cache) {
	read_next_instruction();
	uint32_t skip = stack_read(program);
	if (stack_pop(data))
		for (uint32_t i = 0; i < skip; i++)
			read_next_instruction();
	return 0;
}

// nzero (1, -1, 0)
// argument indicates number of instruction positions to skip (1 for insts with no arg, 2 for insts with one arg)
int opcode_nzer(stack* data, stack* program, uint32_t* cache) {
	read_next_instruction();
	uint32_t skip = stack_read(program);
	if (!stack_pop(data))
		for (uint32_t i = 0; i < skip; i++)
			read_next_instruction();
	return 0;
}

// nout (0, -1, 0)
int opcode_nout(stack* data, stack* program, uint32_t* cache) {
	printf("%d\n", stack_pop(data));
	return 0;
}

// cout (0, -1, 0)
int opcode_cout(stack* data, stack* program, uint32_t* cache) {
	printf("%c", (char)stack_pop(data));
	return 0;
}

// nin (0, 0, 1)
int opcode_nin(stack* data, stack* program, uint32_t* cache) {
	uint32_t n = 0;
	scanf("%ul", &n);
	stack_push(data, n);
	return 0;
}

// cin (0, 0, 1)
int opcode_cin(stack* data, stack* program, uint32_t* cache) {
	char c = 0;
	scanf("%c", &c);
	stack_push(data, c);
	return 0;
}

// nop (0, 0, 0)
int opcode_nop(stack* data, stack* program, uint32_t* cache) {
	return 0;
}

// exit (0, 0, 0)
int opcode_exit(stack* data, stack* program, uint32_t* cache) {
	return -4096;
}

// dup (0, -1, 2)
int opcode_dup(stack* data, stack* program, uint32_t* cache) {
	uint32_t n = stack_pop(data);
	stack_push(data, n);
	stack_push(data, n);
	return 0;
}

struct opcode_table_entry {
	uint32_t key;
	opcode_t func;
};

struct opcode_table_entry opcodes[] = {
	{0x70757368, opcode_push},
	{0x706f7020, opcode_pop},
	{0x706f706e, opcode_popn},
	{0x70757363, opcode_pusc},
	{0x706f7063, opcode_popc},
	{0x70757370, opcode_pusp},
	{0x706f7070, opcode_popp},
	{0x706f7071, opcode_popq},
	{0x61646420, opcode_add},
	{0x73756220, opcode_sub},
	{0x6d756c20, opcode_mul},
	{0x64697620, opcode_div},
	{0x696e6320, opcode_inc},
	{0x64656320, opcode_dec},
	{0x616e6420, opcode_and},
	{0x6f722020, opcode_or},
	{0x786f7220, opcode_xor},
	{0x6e6f7420, opcode_not},
	{0x65717520, opcode_equ},
	{0x67742020, opcode_gt},
	{0x7a65726f, opcode_zero},
	{0x6e7a6572, opcode_nzer},
	{0x6e6f7574, opcode_nout},
	{0x636f7574, opcode_cout},
	{0x6e696e20, opcode_nin},
	{0x63696e20, opcode_cin},
	{0x6e6f7020, opcode_nop},
	{0x65786974, opcode_exit},
	{0x64757020, opcode_dup},
};

int opcode_execute(stack* data, stack* program, uint32_t* cache) {
	for (int i = 0; i < (sizeof(opcodes) / sizeof(struct opcode_table_entry)); i++)
		if (opcodes[i].key == stack_read(program))
			return opcodes[i].func(data, program, cache);
	return 0;
}
