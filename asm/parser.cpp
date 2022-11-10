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
    while (iterator < tokens.size()) {

        if (tokens[iterator] == "add" || tokens[iterator] == "ADD") _asmADD(&iterator);
        if (tokens[iterator] == "nop" || tokens[iterator] == "NOP") _asmNOP(&iterator);
        if (tokens[iterator] == "ld"  || tokens[iterator] == "LD")  _asmLOAD(&iterator);
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

void Parser::_asmNOP(int* iterator) { // nop opcode handler
    logicTree[stackPointer][0] = OP_NOP; // set opcode to NOP
    for(auto i = 1 ; i < 3 ; i++) logicTree[stackPointer][i] = 0x00; // set the operands to 0

    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmLOAD(int* iterator) { // load opcode handler
    using namespace std;
    logicTree[stackPointer][0] = OP_LOAD; // set opcode to LOAD
    logicTree[stackPointer][1] = stoul(tokens[*iterator + 1], nullptr, 0); // set operand 1 to the value of the next token
    logicTree[stackPointer][2] = stoul(tokens[*iterator + 2], nullptr, 0); // set operand 2 to the value of the token after that

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
    using namespace std;
    logicTree[stackPointer][0] = OP_STA; // set the opcode to sta
    logicTree[stackPointer][1] = stoul(tokens[*iterator + 1], nullptr, 0); // set operand 1 to the value of the next token
    logicTree[stackPointer][2] = stoul(tokens[*iterator + 2], nullptr, 0); // set operand 2 to the value of the token after that
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmLDI(int* iterator) { // ldi opcode handler
    using namespace std;
    logicTree[stackPointer][0] = OP_LDI; // set the opcode to ldi
    logicTree[stackPointer][1] = stoul(tokens[*iterator + 1], nullptr, 0); // set operand 1 to the value of the next token
    logicTree[stackPointer][2] = stoul(tokens[*iterator + 2], nullptr, 0); // set operand 2 to the value of the token after that
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmJMP(int* iterator) { // jmp opcode handler
    using namespace std;
    logicTree[stackPointer][0] = OP_JMP; // set the opcode to jmp
    logicTree[stackPointer][1] = stoul(tokens[*iterator + 1], nullptr, 0); // set operand 1 to the value of the next token
    logicTree[stackPointer][2] = stoul(tokens[*iterator + 2], nullptr, 0); // set operand 2 to the value of the token after that
    
    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}
