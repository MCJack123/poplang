//
//  exec.h
//  poplang
//
//  Created by JackMacWindows on 4/21/20.
//  Copyright © 2020 MCJack123. All rights reserved.
//

#ifndef exec_h
#define exec_h

#include <stddef.h>

// Initializes the environment with a program
void poplang_initialize(const char *, size_t);

// Executes a program to completion
void poplang_execute(void);

// Deinitializes the environment and frees memory
void poplang_deinitialize(void);

#endif /* exec_h */
