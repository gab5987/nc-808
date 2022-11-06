#ifndef ASM_HELPER_H
#define ASM_HELPER_H
#include <vector>
#include <iostream>

int openFile(char* filename); // function to open a file and send it to the tokenizer

static class Tokenizer {
    private:
        int line;       // counts the number of lines in the file
        int size;       // size of the file in bytes
        char* filename; // name of the file being tokenized
    public:
        void tokenize(std::string* line);
        void printTokens(); // this method prints the tokens array - FOR DEBUGGING PURPOSES, REMOVE LATER!
} Tokenizer;

#endif