#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "asm.h"
#include "opcodes.h"

std::vector<std::string> tokens; // array of tokens

// Tokenize a line of assembly code and add it to the tokens array
void Tokenizer::tokenize(std::string* line) {
    using namespace std;
    stringstream ss(*line); // convert string to stringstream
    string word; // temp string to hold each word

    // tokenize the line
    while (ss >> word) {
        if (word == ";" || word == "#") return; // ignore comments
        tokens.push_back(word); // add token to array
    }
}

// Print the tokens array - FOR DEBUGGING PURPOSES, REMOVE LATER!
void Tokenizer::printTokens() {
    using namespace std;
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << endl;
    }
}
