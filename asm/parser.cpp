#include "asm.h"
#include "opcodes.h"
#include <bitset>

#define INCREMENT_STACK stackPointer++; iterator += 2; // increment the stack pointer and iterator by 2

unsigned int logicTree[256][3]; // 256 opcodes, 3 operands
                                // 0 = opcode, 1 = operand 1, 2 = operand 2
                                // 256 is also the max number of possible memory locations

unsigned int stackPointer = 0; // stack pointer, stores the current memory location

int Parser::parse() {
    using namespace std;
    int iterator = 0;

    void search_for_tokens() {
        if (tokens[iterator] == "nop" || tokens[iterator] == "NOP") _asmNOP(&iterator);
        else if (tokens[iterator] == "ld" || tokens[iterator] == "LD") _asmLOAD(&iterator);
        else if (tokens[iterator] == "add" || tokens[iterator] == "ADD") _asmADD(&iterator);
        else if (tokens[iterator] == "sub" || tokens[iterator] == "SUB") _asmSUB(&iterator);
        else if (tokens[iterator] == "sta" || tokens[iterator] == "STA") _asmSTA(&iterator);
        else if (tokens[iterator] == "ldi" || tokens[iterator] == "LDI") _asmLDI(&iterator);
        else if (tokens[iterator] == "jmp" || tokens[iterator] == "JMP") _asmJMP(&iterator);
        else if (tokens[iterator] == "in" || tokens[iterator] == "IN") _asmIN(&iterator);
        else if (tokens[iterator] == "out" || tokens[iterator] == "OUT") _asmOUT(&iterator);
        else if (tokens[iterator] == "hlt" || tokens[iterator] == "HLT") _asmHLT(&iterator);
        else {
            cout << "Error: Invalid instruction at line " << Tokenizer.line << endl;
            exit(1);
        }
    }

    while (iterator < tokens.size()) {

        

        // else {
        //     cout << "Error: Unexpected token " << tokens[iterator] << endl;
        //     return 1;
        // }
        iterator++;
    }
    cout << "Parsed successfully!" << endl;
    for(auto j = 0 ; j < stackPointer ; j++) {
        cout << bitset<8>(logicTree[j][0]) << " " << bitset<8>(logicTree[j][1]) << " " << bitset<8>(logicTree[j][2]) << endl;
    }
    return 0;
}


// Methods for each instruction

void set_operands(int* iterator) { // set the operands for the current instruction
    using namespace std;
    logicTree[stackPointer][1] = stoul(tokens[*iterator + 1], nullptr, 0); // set operand 1 to the value of the next token
    logicTree[stackPointer][2] = stoul(tokens[*iterator + 2], nullptr, 0); // set operand 2 to the value of the token after that
}

void Parser::_asmNOP(int* iterator) { // nop opcode handler
    logicTree[stackPointer][0] = OP_NOP; // set opcode to NOP
    for(auto i = 1 ; i < 3 ; i++) logicTree[stackPointer][i] = 0x00; // set the operands to 0

    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmLOAD(int* iterator) { // load opcode handler
    logicTree[stackPointer][0] = OP_LOAD; // set opcode to LOAD
    set_operands(iterator); // set the operands

    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmADD(int* iterator) { // add opcode handler
    logicTree[stackPointer][0] = OP_ADD; // set the opcode to add
    for(auto i = 1 ; i < 3 ; i++) logicTree[stackPointer][i] = 0x00; // set the operands to 0
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmSUB(int* iterator) { // sub opcode handler
    logicTree[stackPointer][0] = OP_SUB; // set the opcode to sub
    for(auto i = 1 ; i < 3 ; i++) logicTree[stackPointer][i] = 0x00; // set the operands to 0
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmSTA(int* iterator) { // sta opcode handler
    logicTree[stackPointer][0] = OP_STA; // set the opcode to sta
    set_operands(iterator); // set the operands
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmLDI(int* iterator) { // ldi opcode handler
    logicTree[stackPointer][0] = OP_LDI; // set the opcode to ldi
    set_operands(iterator); // set the operands
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmJMP(int* iterator) { // jmp opcode handler
    logicTree[stackPointer][0] = OP_JMP; // set the opcode to jmp
    set_operands(iterator); // set the operands
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}
