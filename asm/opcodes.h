#ifndef _OPCODES_H_
#define _OPCODES_H_

#define OP_NOP 0b0000  // 0x00 -> No operation
#define OP_LOAD 0b0001 // 0x01 -> Copy value to register 
#define OP_ADD 0b0010  // 0x02 -> Add value to register
#define OP_SUB 0b0011  // 0x03 -> Subtract value from register
#define OP_STA 0b0100  // 0x04 -> Store value from register to memory
#define OP_LDI 0b0101  // 0x05 -> Load value from memory to register
#define OP_JMP 0b0110  // 0x06 -> Jump to address

// other opcodes here

#define OP_IN 0b1101  // 0x0d -> Input value to register
#define OP_OUT 0b1110 // 0x0e -> Output value from register
#define OP_HLT 0b1111 // 0x0f -> Halt

#endif