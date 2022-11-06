#include "asm.h"
#include "opcodes.h"

std::vector<std::vector<int8_t>> logicTree{ {0,0,0} }; // array of tokens

int Parser::parse() {
    using namespace std;
    int iterator = 0;
    while (iterator < tokens.size()) {

        if (tokens[iterator] == "add" || tokens[iterator] == "ADD") _asmADD(&iterator);
        //cout << logicTree[0][0] << endl;
        // else {
        //     cout << "Error: Unexpected token " << tokens[iterator] << endl;
        //     return 1;
        // }
        iterator++;
    }
    cout << "Parsed successfully!" << endl;
    return 0;
}

void Parser::_asmADD(int* iterator) {
    using namespace std;
    vector<int8_t> logic;
    logic.push_back(0x01);
    logic.push_back(0x02);
    logic.push_back(0x03);
    logicTree.push_back(logic);
    // for(auto i : operation) {
    //     logicTree[i].push_back(operation[i]);
    // }
}

/*

if (tokens[i] == "NOP") cout << OP_NOP << endl;
        
         else if (tokens[i] == "LOAD") {
            cout << OP_ADD << endl;
        } else if (tokens[i] == "ADD") {
            cout << OP_ADD << endl;
        } else if (tokens[i] == "SUB") {
            cout << OP_SUB << endl;
        } else if (tokens[i] == "STA") {
            cout << OP_STA << endl;
        } else if (tokens[i] == "LDI") {
            cout << OP_LDI << endl;
        } else if (tokens[i] == "JMP") {
            cout << OP_JMP << endl;
        } else if (tokens[i] == "IN") {
            cout << OP_IN << endl;
        } else if (tokens[i] == "OUT") {
            cout << OP_OUT << endl;
        } else if (tokens[i] == "HLT") {
            cout << OP_HLT << endl;
        }// else {
        //     cout << "Error: Unknown opcode " << tokens[i] << endl;
        // }

*/