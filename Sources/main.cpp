#include <iostream>
#include <fstream>
#include <string>
#include "..\Headers\trietree.h"

int main() {
    std::ifstream reader("Resources/TreeValues.txt");
    if (reader) {
        ttr::TrieTree tt;
        std::string input;
        while (reader >> input) {
            tt.addWord(input);
        }
        reader.close();
        reader.open("Resources/Letters.txt");
        if (reader >> input) {
            std::cout << "Input words";
            tt.printAllWords();
            std::cout << "Letters: " << input << "\n";
            tt.deleteWordsWithLettersFrom(input);
            std::cout << "Words without removed ones";
            tt.printAllWords();
            reader.close();
        }
        else {
            std::cout << "file with letters not found";
        }
    }
    else {
        std::cout << "file with words not found";
    }
    
}