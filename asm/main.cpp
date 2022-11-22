#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include "asm.h"
#include "opcodes.h"

// global variables to hold options
bool verbose = false;

int main(int argc, char* argv[]) {

    // check if the user provided a filename, if not, exit
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename> <options>" << std::endl;
        return 1;
    }

    for(auto i = 0 ; i < argc ; i++) {
        if(!std::strcmp(argv[i], "-v") || !std::strcmp(argv[i], "--verbose")) verbose = true;
    }

    std::cout << verbose << std::endl;

    // open the file and send it to the tokenizer
    openFile(argv[1]);

    std::cout << "\n" << std::endl;
    Parser.tokens = tokens; // set the tokens vector in the parser to the tokens vector in the tokenizer
    Parser.parse(); // parse the tokens
    return 0;
}

int openFile(char* filename) {
    using namespace std;
    ifstream asm_file; asm_file.open(filename); // opens the file

    // check if the file was successfully opened, if not, throws a error and exit
    !asm_file.is_open() ? 
        cout << "Error: Could not open file " << filename << endl : 
        cout << "Opened file " << filename << "\n" << endl;

    // read the file line by line and send it to the tokenizer
    if(asm_file.is_open()) {
        string buffer;
        while(getline(asm_file, buffer)){
            Tokenizer.tokenize(&buffer);
        }
        asm_file.close();
    }
    Tokenizer.printTokens(); // print the tokens array - FOR DEBUGGING PURPOSES, REMOVE LATER!
    return 0;
}