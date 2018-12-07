#include <iostream>
#include <map>
#include <vector>


class Trie {
public:
    Trie() {
        root = new Node;
        alphabet[' '] = 0;
        for (int i = 0; i < 26; ++i) {
            alphabet[(char) i + 'a'] = i + 1;
        }
    };
    ~Trie();

    void insert(std::string word) {

    };


    bool search(std::string word) {

    };


    int encode() {

    };


    std::string decode() {

    };
    
private:
    class Node {
    public:
        Node();
        ~Node();

    
    };

    Node* root;
    std::map<char,int> alphabet;

};



int main() {

    return 0;
}