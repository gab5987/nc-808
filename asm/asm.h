#ifndef ASM_HELPER_H
#define ASM_HELPER_H
#include <vector>
#include <iostream>

int openFile(char* filename); // function to open a file and send it to the tokenizer

extern std::vector<std::string> tokens;

extern bool verbose;

static class Tokenizer {
    public:
        int line;           // counts the number of lines in the file
        int size;           // size of the file in bytes
        int currentAddress; // current address in memory
        char* filename;     // name of the file being tokenized
    public:
        void tokenize(std::string* line);
        void printTokens(); // this method prints the tokens array - FOR DEBUGGING PURPOSES, REMOVE LATER!
} Tokenizer;

static class Parser {
    public:
        std::vector<std::string> tokens; // array of tokens
    public:
        int parse();

        // methods to parse each instruction
        void _asmNOP(int* iterator);
        void _asmLOAD(int* iterator);
        void _asmADD(int* iterator);
        void _asmSUB(int* iterator);
        void _asmSTA(int* iterator);
        void _asmLDI(int* iterator);
        void _asmJMP(int* iterator);

        void _asmIN(int* iterator);
        void _asmOUT(int* iterator);
        void _asmHLT(int* iterator);
} Parser;

#endif
