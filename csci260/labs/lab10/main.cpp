#include <iostream>


class SkipList {
public:
    SkipList() {
        root = new Cell;
        root->key = ;
    };


    ~SkipList() {

    };


    std::string& lookup(int key) {

    };


    bool insert(int key, std::string data) {

    };
    
private:
    struct Cell;

    Cell* search(int key) {

    };


    Cell* insertUpRight(Cell* p, Cell*q, int key, std::string* data) {

    };


    struct Cell {
        int key;
        std::string* data;
        Cell* up;
        Cell* down;
        Cell* left;
        Cell* right;
    };

    Cell* root;
};


int main() {
    SkipList skipList;

    return 0;
}