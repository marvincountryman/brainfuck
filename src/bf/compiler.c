#include "compiler.h"

/*
    Map JMP instructions
        Iterate instructions, find OP_JMPZ and OP_JMPNZ, set operand to both 
        OP_JMPZ and OP_JMPNZ of abs(offset) to matching JMP.
*/
int bf_compiler_map_jmps(Compiler* compiler) {
    Instruction* instruction = compiler->instructions;

    while (instruction->opcode != OP_EOF) {
        if (instruction->opcode == OP_JMPZ) {
            int depth = 0;
            int offset = 1;

            Instruction* search = instruction;

            while (search->opcode != OP_EOF) {
                // If nested loop, increment depth.
                if (search->opcode == OP_JMPZ) depth++;
                // If loop terminator, decrement depth.
                if (search->opcode == OP_JMPNZ) depth--;
                // If loop terminator at same depth
                if (depth == 0) {
                    // Apply offset to terminator
                    search->operand = offset - 1;
                    // Apply offset to OP_JMPZ
                    instruction->operand = offset;

                    break;
                }

                search++;
                offset++;
            }
        }

        ++instruction;
    }

    return 1;
}

/*
    New instance of Compiler.
        Allocates instructions with length of code.  Due to our method of 
        joining multiple instructions this size will be larger than needed.  
        When we know how many instructions we need (after compilation) we
        reallocate.
*/
Compiler bf_compiler_new(char* code) {
    Compiler compiler = {
        .code = code,
        .count = strlen(code),
        .instructions = malloc(sizeof(Instruction) * strlen(code)),
    };

    return compiler;
}

/*
    Free compiler and maloced instructions buffer
*/
int bf_compiler_free(Compiler* compiler) {
    free(compiler->instructions);
    free(compiler);

    return 1;
}

/*
    Dump instructions to STDOUT
        Iterates through compiled instructions and writes the opcode and
        operand to STDOUT.
*/
int bf_compiler_dump(Compiler* compiler) {
    for (int i = 0; i < compiler->count; i++) {
        printf("Instruction: {\n");
        printf("  opcode: %d\n", compiler->instructions[i].opcode);
        printf("  operand: %d\n", compiler->instructions[i].operand);
        printf("}\n");
    }
}

/*
    Compile!
        Iterates through code, when valid character is found we check the
        last instruction, if matching we increment the operand to reduce 
        instruction count.  Additionally instructions are counted, the 
        instructions buffer is reallocated, and count is saved to Compiler
        pointer.
*/
int bf_compiler_compile(Compiler* compiler) {
    int count = 0;

    char* ch = compiler->code;
    Instruction* instruction = compiler->instructions;

    // Add the OP_BOF instruction to head of buffer
    count++;
    instruction->opcode = OP_BOF;
    instruction->operand = 0;

    while (*ch != '\0') {
        char opcode = OP_EOF;
        short modifier = 1;

        // Get operator and modifier
        switch (*ch) {
        case '<':
        case '>':
            opcode = OP_MOV;
            modifier = *ch == '<' ? -1 : 1;
            break;
        case '+': opcode = OP_ADD; break;
        case '-': opcode = OP_SUB; break;
        case ',': opcode = OP_GET; break;
        case '.': 
            opcode = OP_PUT; 
            break;
        case '[': opcode = OP_JMPZ; break;
        case ']': opcode = OP_JMPNZ; break;
        }

        if (opcode == OP_EOF) {
            // Valid character not found.  Must be a comment..
        } else if (opcode != OP_JMPZ && opcode != OP_JMPNZ) {
            // If stackable instruction, check if last instruction opcode
            // matches.  If so increment operand with modifier.
            if (instruction->opcode != opcode) {
                count++;
                instruction++;
                instruction->opcode = opcode;
                instruction->operand = 0;
            }

            instruction->operand += modifier;
        } else {
            // OP_JMPZ, and OP_JMPNZ are not stackable.

            count++;
            instruction++;
            instruction->opcode = opcode;
            instruction->operand = 0;
        }


        ch++;
    }

    // Add EOF instruction 
    count++;
    instruction++;
    instruction->opcode = OP_EOF;
    instruction->operand = 0;

    // Save instruction count, and realloc instructions buffer
    compiler->count = count;
    realloc(compiler->instructions, sizeof(Instruction) * count);

    // Map our JMPs!
    return bf_compiler_map_jmps(compiler);
}