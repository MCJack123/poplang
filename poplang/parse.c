//
//  parse.c
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#include "parse.h"
#include <stdbool.h>
#include <ctype.h>

unsigned poplang_get_program_size(const char * program, size_t size) {
	unsigned retval = 0;
	int mode = 0;
	bool escape = false;
	for (int i = 0; i < size; i++) {
		if (mode == 0) {
			escape = false;
			if ((program[i] >= 'a' && program[i] <= 'z') || (program[i] >= 'A' && program[i] <= 'Z') || (program[i] >= '0' && program[i] <= '9')) {mode = 1; retval++;}
			else if (program[i] == '\'') {mode = 2; retval++;}
			else if (program[i] == ';') mode = 3;
		} else if (mode == 2 && program[i] == '\\') escape = true;
		else if ((mode == 1 && !((program[i] >= 'a' && program[i] <= 'z') || (program[i] >= 'A' && program[i] <= 'Z') || (program[i] >= '0' && program[i] <= '9'))) || (mode == 2 && !escape && program[i] == '\'') || (mode == 3 && program[i] == '\n')) mode = 0;
		else escape = false;
	}
	return retval*4;
}

int chartohex(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	else if (c >= 'a' && c <= 'f') return c - 'a';
	else if (c >= 'A' && c <= 'F') return c - 'A';
	else return 0;
}

void poplang_parse_program(const char * input, size_t input_size, char * output, size_t output_size) {
	output_size = (output_size / 4) * 4;
	unsigned out_pos = 0;
	for (int i = 0; i < input_size && out_pos < output_size;) {
		if (input[i] == '\'') {
			char ch = input[++i];
			if (ch == '\\') {
				switch (input[++i]) {
					case '\\': ch = '\\'; break;
					case 'n': ch = '\n'; break;
					case 't': ch = '\t'; break;
					case '\'': ch = '\''; break;
					case 'r': ch = '\r'; break;
					case 'x': ch = (chartohex(input[i+1]) << 4) | chartohex(input[i+2]); break;
					case '0': default: ch = 0; break;
				}
			}
			output[out_pos++] = 0;
			output[out_pos++] = 0;
			output[out_pos++] = 0;
			output[out_pos++] = ch;
			while (input[i++] != '\'');
		} else if (input[i] >= '0' && input[i] <= '9') {
			uint32_t num = input[i] - '0';
			while (input[++i] >= '0' && input[i] <= '9') num = (num * 10) + (input[i] - '0');
			output[out_pos++] = num >> 24;
			output[out_pos++] = (num >> 16) & 0xFF;
			output[out_pos++] = (num >> 8) & 0xFF;
			output[out_pos++] = num & 0xFF;
		} else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
			output[out_pos++] = tolower(input[i++]);
			if (input[i] == '\n') output[out_pos++] = ' '; else output[out_pos++] = tolower(input[i++]);
			if (input[i] == '\n') output[out_pos++] = ' '; else output[out_pos++] = tolower(input[i++]);
			if (input[i] == '\n') output[out_pos++] = ' '; else output[out_pos++] = tolower(input[i++]);
			while ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) i++;
		} else if (input[i] == ';') while (input[i++] != '\n');
		else i++;
	}
}
