#include "../Headers/trietree.h"

ttr::TrieTree::TrieTree() {
    root = new Node;
    for (int i = 0; i < 26; i++) {
        root->ptrs[i] = nullptr;
    }
}

ttr::TrieTree::~TrieTree() {
    clear(root);
}

bool ttr::TrieTree::isEmpty() {
    return hasNoChildren(root);
}

void ttr::TrieTree::addWord(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = std::towlower(word[i]);
    }
    addNode(root, word, 0);
}

void ttr::TrieTree::deleteWord(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = std::towlower(word[i]);
    }
    deleteNode(root, word, 0);
}

// void ttr::TrieTree::deleteWordsWithLettersFrom(const std::string list) {
//     int letters[26] = { -1 };
//     for (int i = 0; i < list.length(); i++) {
//         if (std::isalpha(list[i])) {
//             letters[list[i] - 'a'] = 0;
//         }
//      }
//     subDeleteWords(root, ' ', letters);
// }

void ttr::TrieTree::deleteWordsWithLettersFrom(const std::string list) {
    int letters[26];
    for (int i = 0; i < 26; i++) {
        letters[i] = -1;
    }
    for (int i = 0; i < list.length(); i++) {
        if (std::isalpha(list[i])) {
            letters[list[i] - 'a'] = 0;
        }
     }
    subDeleteWords(root, ' ', letters);
}

void ttr::TrieTree::addNode(Node*& obj, const std::string word, short i) {
    if (obj == nullptr) {
        obj = new Node;
        obj->isWord = false;
        for (short j = 0; j < 26; j++) {
            obj->ptrs[j] = nullptr;
        }
    }
    if (short(word.length()) - 1 < i) {
        obj->isWord = true;
    }
    else {
        addNode(obj->ptrs[word[i] - 'a'], word, i + 1);
    }
}

void ttr::TrieTree::deleteNode(Node*& obj, const std::string word, short i) {
    if (obj != nullptr) {
        if (i <= short(word.length() - 1)) {
            deleteNode(obj->ptrs[word[i] - 'a'], word, i + 1);
        }
        else {
            obj->isWord = false;
            if (hasNoChildren(obj)) {
                delete obj;
                obj = nullptr;
            }
        }
    }
}

bool ttr::TrieTree::hasNoChildren(Node* obj) {
    bool result = true;
    for (int i = 0; i < 26 && result; i++) {
        if (obj->ptrs[i] != nullptr) {
            result = false;
        }
    }
    return result;
}

void ttr::TrieTree::clear(Node*& obj) {
    for (int i = 0; i < 26; i++) {
        if (obj->ptrs[i] != nullptr) {
            clear(obj->ptrs[i]);
        }
    }
    delete obj;
    obj = nullptr;
}

void ttr::TrieTree::print(Node* obj, std::string word) {
    if (obj->isWord) {
        std::cout << word << std::endl;
    }
    for (int i = 0; i < 26; i++) {
        if (obj->ptrs[i] != nullptr) {
            print(obj->ptrs[i], word + char('a' + i));
        }
    }
}

// bool ttr::TrieTree::subDeleteWords(Node*& obj, char letter, int* letters) {
//     bool result = false;
//     if (obj != nullptr) {
//         if (letters[letter - 'a'] == 1) {
//             result = true;
//             clear(obj);
//         }
//         else {
//             for (int i = 0; i < 26 && !result; i++) {
//                 if (subDeleteWords(obj->ptrs[i], 'a' + i, letters) && hasNoChildren(obj)) {
//                     if (letter != ' ') {
//                         clear(obj);
//                     }
//                     result = true;
//                 }
//             }
//         }
//     }
//     return result;
// }

bool ttr::TrieTree::subDeleteWords(Node*& obj, char letter, int* letters) {
    bool result = false;
    if (obj != nullptr) {
        // if (letter != ' ' && letters[letter - 'a']++ >= 0 && everyLetterMet(letters)) {
        //     clear(obj);
        //     result = true;
        //     letters[letter - 'a']--;
        // }
        if (letter != ' ' && letters[letter - 'a'] >= 0) {
            letters[letter - 'a']++;
            if (everyLetterMet(letters)) {
                clear(obj);
                result = true;
                letters[letter - 'a']--;
            }
            else {
                for (int i = 0; i < 26 && !result; i++) {
                    if (subDeleteWords(obj->ptrs[i], 'a' + i, letters) && hasNoChildren(obj) && !obj->isWord) {
                        clear(obj);
                        if (letters[letter - 'a'] >= 1) {
                        }
                        result = true;
                    }
                }
                letters[letter - 'a']--;
            }
        }
        else {
            // ...
            for (int i = 0; i < 26 && !result; i++) {
                if (subDeleteWords(obj->ptrs[i], 'a' + i, letters) && hasNoChildren(obj) && !obj->isWord) {
                    clear(obj);
                    if (letters[letter - 'a'] >= 1) {
                        letters[letter - 'a']--;
                    }
                    result = true;
                }
            }
        }
    }
    return result;
}

bool ttr::TrieTree::everyLetterMet(int* letters) {
    bool result = true;
    for (int i = 0; i < 26 && result; i++) {
        if (letters[i] == 0) {
            result = false;
        }
    }
    return result;
}

void ttr::TrieTree::printAllWords() {
    print(root, "");
}