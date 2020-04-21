//
//  parse.h
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#ifndef parse_h
#define parse_h

#include <stddef.h>

// Returns the minimum size of a buffer storing the parsed version of the command.
extern unsigned poplang_get_program_size(const char *, size_t);

// Parses a textual representation of a program and converts the numbers to binary.
extern void poplang_parse_program(const char *, size_t, char *, size_t);

#endif /* parse_h */
