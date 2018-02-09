#ifndef _BF_VM_H_
#define _BF_VM_H_

#include "brainfuck.h"

typedef struct Vm {
    short* pointer;
    short* registers;
    size_t register_count;
} Vm;

Vm bf_vm_new(size_t register_count);

int bf_vm_free(Vm* vm);
int bf_vm_run(Vm* vm, Instruction* instructions);

#endif//_BF_VM_H_