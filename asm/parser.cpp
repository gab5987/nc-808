#include "asm.h"
#include "opcodes.h"
#include <bitset>

#define INCREMENT_STACK stackPointer++; *iterator += 3; // increment the stack pointer and iterator by 3

unsigned int logicTree[256][3]; // 256 opcodes, 3 operands
                                // 0 = opcode, 1 = operand 1, 2 = operand 2
                                // 256 is also the max number of possible memory locations

unsigned int stackPointer = 0; // stack pointer, stores the current memory location

class Macros { // base class to create a new macro
    public:
        std::string name;
        u_int operation[3];
        Macros(std::string newName, u_int* op) {
            name = "@" + newName;
            for(auto i = 0 ; i < 3 ; i++) operation[i] = op[i];
        }
};

std::vector<Macros> macros; // vector of macros

// register new macros into its vector
int register_or_call_macros(int* iterator) {
    if(tokens[*iterator] == "@macro:") {
        std::string name = tokens[*iterator + 1]; u_int op[3];
        for(auto i = 0 ; i < 3 ; i++) op[i] = std::stoul(tokens[*iterator + 2 + i], nullptr, 0);

        Macros newMacro(name, op);
        macros.push_back(newMacro);
        stackPointer++;
        return 5;
    }
    return 0;
}

class Variable { // base class to create a new variable
    public:
        std::string name;
        int value;
        Variable(std::string newName, u_int8_t newValue) {
            name = '$' + newName;
            value = newValue;
        }
};

std::vector<Variable> variables; // vector of variables
#define CONTINUE iterator ++; continue;

// register new variables into its vector
int register_variables() {
    u_int iterator = 0;

    while(tokens.size()) {
        const char* buffer = tokens[iterator].c_str();

        if(buffer[0] == '$') {
            for(auto i = 0 ; i < variables.size() ; i++) variables[i].name == tokens[iterator] && CONTINUE;
            
            std::string name = tokens[iterator]; 
            int value = std::stoul(tokens[iterator + 1], nullptr, 0);
            Variable newVariable(name, value);
            variables.push_back(newVariable);
            stackPointer++;
            iterator += 2;
        }
        else CONTINUE;
    }
}

int Parser::parse() {
    using namespace std;
    int iterator = 0;

    register_variables();

    while (iterator < tokens.size()) {
        iterator += register_or_call_macros(&iterator);
        // if(search_for_variable(&iterator)) continue;

        // check if the token is a macro, if so, replace it with the macro's operation
        for(auto i = 0 ; i < macros.size() ; i++) {
            if(std::strcmp(tokens[iterator].c_str(), macros[i].name.c_str()) == 0) {
                for(auto j = 0 ; j < 3 ; j++) logicTree[stackPointer][j] = macros[i].operation[j];
                stackPointer++; iterator += 3;
            }
        }
        
        // check if the token is an opcode, if so, add it to the logic tree
        if (tokens[iterator] == "nop" || tokens[iterator] == "NOP") _asmNOP(&iterator);
        else if (tokens[iterator] == "ld" || tokens[iterator] == "LD") _asmLOAD(&iterator);
        else if (tokens[iterator] == "add" || tokens[iterator] == "ADD") _asmADD(&iterator);
        else if (tokens[iterator] == "sub" || tokens[iterator] == "SUB") _asmSUB(&iterator);
        else if (tokens[iterator] == "sta" || tokens[iterator] == "STA") _asmSTA(&iterator);
        else if (tokens[iterator] == "ldi" || tokens[iterator] == "LDI") _asmLDI(&iterator);
        else if (tokens[iterator] == "jmp" || tokens[iterator] == "JMP") _asmJMP(&iterator);
        else {
            // exits the program and trows a syntax error if the token is not an opcode nor a null terminator
            if(tokens[iterator] != "\0") {
                cout << "Error: Unexpected token '" << tokens[iterator] << "' at line " << stackPointer << endl;
                exit(1);
            }
        }
    }
    for(auto i = 0 ; i < variables.size() ; i++) cout << variables[i].name << " " << variables[i].value << endl;
    cout << "Finished!\nHere's the generated bin code:\n" << endl;
    // prints out the finished program
    for(auto j = 0 ; j < stackPointer ; j++) {
        cout << 
            bitset<8>(j) << " " <<               // memory location
            bitset<8>(logicTree[j][0]) << " " << // opcode
            bitset<8>(logicTree[j][1]) << " " << // operand 1
            bitset<8>(logicTree[j][2])           // operand 2
            << endl;
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

    *iterator += 1; // increment the iterator
    stackPointer += 1; // increment the stack pointer
}

void Parser::_asmLOAD(int* iterator) { // load opcode handler
    logicTree[stackPointer][0] = OP_LOAD; // set opcode to LOAD
    set_operands(iterator); // set the operands

    INCREMENT_STACK; // increment the stack pointer and iterator by 2
}

void Parser::_asmADD(int* iterator) { // add opcode handler
    logicTree[stackPointer][0] = OP_ADD; // set the opcode to add
    for(auto i = 1 ; i < 3 ; i++) logicTree[stackPointer][i] = 0x00; // set the operands to 0
    
    *iterator += 1; // increment the iterator
    stackPointer += 1; // increment the stack pointer
}

void Parser::_asmSUB(int* iterator) { // sub opcode handler
    logicTree[stackPointer][0] = OP_SUB; // set the opcode to sub
    for(auto i = 1 ; i < 3 ; i++) logicTree[stackPointer][i] = 0x00; // set the operands to 0
    
    *iterator += 1; // increment the iterator
    stackPointer += 1; // increment the stack pointer
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
