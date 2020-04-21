//
//  exec.c
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#include "exec.h"
#include "stack.h"
#include "instructions.h"

stack * programStack = NULL;
stack * dataStack = NULL;
const char * programData;
size_t programSize;
size_t programOffset;
uint32_t cache;

void read_next_instruction() {
	if (programOffset >= programSize) return;
	uint32_t n = (programData[programOffset] << 24) | (programData[programOffset+1] << 16) | (programData[programOffset+2] << 8) | programData[programOffset+3];
	programOffset += 4;
	stack_push(programStack, n);
}

void poplang_execute() {
	while (programOffset < programSize) {
		int res = opcode_execute(dataStack, programStack, &cache);
		if (res == 0) read_next_instruction();
		else if (res > 0) programOffset -= res * 4;
		else if (res == -4096) return;
	}
}

void poplang_deinitialize() {
	if (programStack != NULL) stack_deinit(programStack);
	if (dataStack != NULL) stack_deinit(dataStack);
	programStack = NULL;
	dataStack = NULL;
}

void poplang_initialize(const char * data, size_t size) {
	poplang_deinitialize();
	programStack = stack_init();
	dataStack = stack_init();
	programData = data;
	programSize = size;
	programOffset = 0;
	cache = 0;
	read_next_instruction();
}
