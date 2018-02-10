#include "brainfuck.h"

int bf_run(char* buffer) {
    Vm vm = bf_vm_new(3000);
    Compiler compiler = bf_compiler_new(buffer);

    if (!bf_compiler_compile(&compiler)) {
        printf("Failed to compile!\n");
        bf_compiler_free(&compiler);

        return 0;
    }
    if (!bf_vm_run(&vm, compiler.instructions)) {
        printf("Encountered runtime error!\n");

        bf_compiler_free(&compiler);
        bf_vm_free(&vm);

        return 0;
    }

    bf_vm_free(&vm);

    return 1;
}