#ifndef _BRAINFUCK_H_
#define _BRAINFUCK_H_

// std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// brainfuck
#include "instruction.h"
#include "compiler.h"
#include "vm.h"

int bf_run(char* buffer);

#endif//_BRAINFUCK_H_