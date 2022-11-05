#ifndef ASM_HELPER_H
#define ASM_HELPER_H
#include <vector>
#include <iostream>

int openFile(char* filename);

static class Tokenizer {
    private:
        char* source;
        int line;
        int column;
        int length;
        char* text;
        char* filename;
    public:
        void tokenize(std::string* line);
} Tokenizer;

#endif