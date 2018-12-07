#include <iostream>


int* makeArray(int size) {
    auto array = new int[size]
    for (int i = 0; i < size; i++) {
        array[i] = i + 1;
    }
    return array;
}


class Tree {
public:
    Tree() {
        root = nullptr;
    };
    ~Tree();

    void insert(int value) {
        if (!root) {
            root = new Node(value);
        }

        
    };
private:
    Node* root;
};


class Node {
public:
    explicit Node(int value, Node* left=nullptr, Node* right=nullptr) 
    : value(value)
    , balance(0)
    , left(left)
    , right(right)
    {};

    int value;
    int balance;
    Node* left;
    Node* right;
};


int main() {
    int size = 15;
    int* myArray = makeArray(size);





    return 0;
}
