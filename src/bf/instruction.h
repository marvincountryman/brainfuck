#ifndef _BF_INSTRUCTION_H_
#define _BF_INSTRUCTION_H_

#define _CRT_SECURE_NO_WARNINGS

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

inline int bf_instruction_tostring(Instruction* instruction, char* buffer, int length) {
    char* opcode = "";

    switch (instruction->opcode) {
    case OP_EOF: opcode = "OP_EOF"; break;
    case OP_BOF: opcode = "OP_BOF"; break;
    case OP_MOV: opcode = "OP_MOV"; break;
    case OP_ADD: opcode = "OP_ADD"; break;
    case OP_SUB: opcode = "OP_SUB"; break;
    case OP_PUT: opcode = "OP_PUT"; break;
    case OP_GET: opcode = "OP_GET"; break;
    case OP_JMPZ: opcode = "OP_JMPZ"; break;
    case OP_JMPNZ: opcode = "OP_JMPNZ"; break;
    }

    return sprintf_s(buffer, length, "{\n\topcode: %s,\n\toperand: %d\n}", opcode, instruction->operand);
}

#endif//_BF_INSTRUCTION_H_