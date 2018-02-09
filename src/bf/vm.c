#include "vm.h"

/*
    New instance of Vm
        malloc register buffer to sizeof(short) * register_count
*/
Vm bf_vm_new(size_t register_count) {
    Vm vm = { 0 };

    vm.register_count = register_count;
    vm.registers = malloc(sizeof(short) * register_count);
    vm.pointer = vm.registers;

    memset(vm.registers, 0, sizeof(short) * register_count);

    return vm;
}

/**/
int bf_vm_free(Vm* vm) {
    free(vm->registers);
    free(vm);
}

/*
    Run supplied instructions
*/
int bf_vm_run(Vm* vm, Instruction* instructions) {
    Instruction* instruction = instructions;

    while (instruction->opcode != OP_EOF) {
        switch (instruction->opcode) {
        case OP_MOV:
            vm->pointer += instruction->operand;
            break;
        case OP_ADD:
            (*vm->pointer) += instruction->operand;
            break;
        case OP_SUB:
            (*vm->pointer) -= instruction->operand;
            break;
        case OP_PUT:
            // print n times
            for (short i = 0; i < instruction->operand; i++)
                putchar((int)*vm->pointer);
            break;
        case OP_GET:
            // get n times
            for (short i = 0; i < instruction->operand; i++)
                *vm->pointer = getchar();
            break;
        case OP_JMPZ:
            if ((*vm->pointer) == 0) {
                instruction += instruction->operand;
                goto instruction_loop_end;
            }

            break;
        case OP_JMPNZ:
            if ((*vm->pointer) != 0) {
                instruction -= instruction->operand;
                goto instruction_loop_end;
            }

            break;
        }

        instruction++;
        instruction_loop_end:;
    }

    return 1;
}