#ifndef _BF_INSTRUCTION_H_
#define _BF_INSTRUCTION_H_

#define OP_EOF   0x00   // End of file
#define OP_BOF   0x01   // Beginning of file
#define OP_MOV   0x02   // Move pointer 
#define OP_ADD   0x03   // Add operand to pointer
#define OP_SUB   0x04   // Sub operand to pointer
#define OP_PUT   0x05   // Print pointer to console
#define OP_GET   0x06   // Read console to pointer
#define OP_JMPZ  0x07   // Jump forward if pointer is zero
#define OP_JMPNZ 0x08   // Jump back if pointer non-zero

typedef struct Instruction {
    char  opcode;
    short operand;
} Instruction;

#endif//_BF_INSTRUCTION_H_