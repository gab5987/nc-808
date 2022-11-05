#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

#include "asm.h"
#include "opcodes.h"

std::vector<std::string> tokens; // array of tokens

void Tokenizer::tokenize(std::string* line) {
    using namespace std;
    stringstream ss(*line);
    string word;
    while (ss >> word) {
        if (word == ";" || word == "#") return;
        tokens.push_back(word);
    }
}

void Tokenizer::printTokens() {
    using namespace std;
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << endl;
    }
}
