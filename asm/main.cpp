#include <iostream>
#include <fstream>
#include <string>

#include "asm.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    openFile(argv[1]);
    return 0;
}

int openFile(char* filename) {
    using namespace std;
    ifstream asm_file; asm_file.open(filename);

    !asm_file.is_open() ? 
        cout << "Error: Could not open file " << filename << endl : 
        cout << "Opened file " << filename << "\n" << endl;

    if(asm_file.is_open()) {
        string line;
        while (getline(asm_file, line)) {
            cout << line << endl;
        }
        asm_file.close();
    }
    return 0;
}