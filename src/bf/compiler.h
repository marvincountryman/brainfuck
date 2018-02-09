#ifndef _BF_COMPILER_H_
#define _BF_COMPILER_H_

#include "brainfuck.h"

typedef struct Compiler {
    char*        code;
    size_t       count;
    Instruction* instructions;
} Compiler;

Compiler bf_compiler_new(char* code);

int bf_compiler_free(Compiler* compiler);
int bf_compiler_dump(Compiler* compiler);
int bf_compiler_compile(Compiler* compiler);

#endif//_BF_COMPILER_H_