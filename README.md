#  Pop Language
An esoteric assembly-like language based entirely on stacks.

## Design
Pop relies on two central stacks as the basis for all operations. These two stacks consist of the *data stack* and the *program stack*. Each stack only allows accessing the top value, and most operations modify a stack in some way.

The data stack holds variables that the user pushes in the program. This stack is also the only stack that arithmetic operations can be applied to.

The program stack holds the current state of the program, and the past operations that have been executed. There are few operations that allow manual adjustment of this stack, but they can be very helpful in writing programs.

There is also a single cache variable available if a state must be kept while perusing the stacks.

## Instructions
| Name | Arguments | # Popped | # Pushed | Description |
|---------|-------------|--------------|-----------|--------------|
| `push` | 1 (value) | 0 | 1 | Pushes a value to the data stack. |
| `pop ` | 0 | -1 | 0 | Pops the top value off the data stack. |
| `popn` | 1 (elements to pop) | -n | 0 | Pops a number of elements off the data stack. |
| `pusc` | 0 | 0 | 1 | Pushes the cached value to the data stack and clears the cache. |
| `popc` | 0 | -1 | 0 | Pops the top value off the data stack and stores it in the cache. |
| `pusp` | 1 | 0 | 1 (program) | Pushes a value onto the program stack. |
| `popp` | 0 | -1 (program) | 0 | Pops the top value off the program stack. This essentially replays the previous instruction. |
| `popq` | 1 (elements to pop) | -n (program) | 0 | Pops a number of values off the program stack. |
| `dup ` | 0 | -1 | 2 | Duplicates the top value in the data stack. |
| `add ` | 0 | -2 | 1 | Pops two elements off the data stack, adds them, and pushes the result. |
| `sub ` | 0 | -2 | 1 | Pops two elements off the data stack, subtracts them, and pushes the result. |
| `mul ` | 0 | -2 | 1 | Pops two elements off the data stack, multiplies them, and pushes the result. |
| `div ` | 0 | -2 | 1 | Pops two elements off the data stack, divides them, and pushes the result. |
| `inc ` | 0 | -1 | 1 | Increments the top element in the data stack. |
| `dec ` | 0 | -1 | 1 | Decrements the top element in the data stack. |
| `and ` | 0 | -2 | 1 | Pops two elements off the data stack, bitwise ANDs them, and pushes the result. |
| `or  ` | 0 | -2 | 1 | Pops two elements off the data stack, bitwise ORs them, and pushes the result. |
| `xor ` | 0 | -2 | 1 | Pops two elements off the data stack, bitwise XORs them, and pushes the result. |
| `not ` | 0 | -1 | 1 | Bitwise NOTs the top element in the data stack. |
| `equ ` | 0 | -2 | 1 | Pops two elements off the data stack, and pushes 0 if not equal or non-0 if equal. |
| `gt  ` | 0 | -2 | 1 | Pops two elements off the data stack, and pushes non-0 if the first is greater than the second, or 0 otherwise. |
| `zero` | 1 (# to advance) | -1 | 0 | Pops an element off the data stack, and advances the program stack by the argument unless the value is 0. |
| `nzer` | 1 (# to advance) | -1 | 0 | Pops an element off the data stack, and advances the program stack by the argument unless the value is not 0. |
| `nout` | 0 | -1 | 0 | Pops a number off the data stack and prints the number. |
| `cout` | 0 | -1 | 0 | Pops a character off the data stack and prints the character. |
| `nin ` | 0 | 0 | 1 | Pushes a number inputted to the console. |
| `cin ` | 0 | 0 | 1 | Pushes a character inputted to the console. |
| `nop ` | 0 | 0 | 0 | No-op (does nothing). |
| `exit` | 0 | 0 | 0 | Immediately stops execution of the program. |

## Hello World!
```
push 0 push '\n' push '!' push 'd' push 'l' push 'r' push 'o' push 'W' push ' ' push 'o' push 'l' push 'l' push 'e' push 'H' cout dup zero 1 exit popq 5
```
See poplang/hello.pop for an explanation on how this works. When converted to binary for execution, it becomes this:
```
"push\0\0\0\0push\0\0\0\npush\0\0\0!push\0\0\0dpush\0\0\0lpush\0\0\0rpush\0\0\0opush\0\0\0Wpush\0\0\0 push\0\0\0opush\0\0\0lpush\0\0\0lpush\0\0\0epush\0\0\0Hcoutdup zero\0\0\0\x01exitpopq\0\0\0\x05"
```

## Compiling
`gcc -o pop main.c parse.c instructions.c exec.c stack.c` inside `poplang/` should do it.

## Usage
To compile a text Pop file to binary, use `pop -c <input.pop> <output.popb>`. To run a Pop program, use `pop <file.pop>`.
