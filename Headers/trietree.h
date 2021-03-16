#ifndef TRIETREE_H
#define TRIETREE_H
#include <iostream>
#include <string>
#include <cstring>

namespace ttr {

    struct Node {
        Node* ptrs[26];
        bool isWord;
    };
    
    class TrieTree {
    private:
        Node* root;

        void addNode(Node*& obj, const std::string word, short i = 0);

        void deleteNode(Node*& obj, const std::string word, short i);

        bool hasNoChildren(Node* obj);

        void clear(Node*& obj);

        void print(Node* obj, std::string word);

        bool subDeleteWords(Node*& obj, char letter, int* letters);

        bool everyLetterMet(int* letters);
    public:
        TrieTree();

        ~TrieTree();

        bool isEmpty();

        void addWord(std::string word);

        void deleteWord(std::string word);

        void deleteWordsWithLettersFrom(const std::string list);

        void printAllWords();
    };

}


#endif