# brainfuck

### Summary
This project is a fairly simple implementation of brainfuck done to learn more about C.  It's not the most effiecient implimentation, nor is it the most sensible.  But it works.

### How It Works
This implimentation parses the brainfuck instruction into a instruction buffer.  Using this buffer we run it through our VM, and voila brainfuck interpreter complete.


### Instruction Dump
Input
```
+++[-]
```
Dump
```
{
        opcode: OP_BOF,
        operand: 0
}
{
        opcode: OP_ADD,
        operand: 3
}
{
        opcode: OP_JMPZ,
        operand: 3
}
{
        opcode: OP_SUB,
        operand: 1
}
{
        opcode: OP_JMPNZ,
        operand: 2
}
```