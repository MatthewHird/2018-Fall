//------------------------------------------------------------------------------
// @file    binary_search_tree.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_BINARY_SEARCH_TREE_H
#define ASSIGNMENT_2_BINARY_SEARCH_TREE_H

#include <iostream>


class BinarySearchTree {
public:
    /**
     * @brief
     */
    BinarySearchTree();

    /**
     * @brief
     */
    ~BinarySearchTree();

    void insert(std::string nameId, std::string numberId);

    std::string getAlphabeticalDataList();

    bool isEmpty();
private:
    struct Node {
        std::string nameId;
        std::string numberId;

        Node* left;
        Node* right;
    };

    void inorderListData(Node* node);

    void postOrderDestroyData(Node* node);

    Node* root;
    int size;
};


#endif //ASSIGNMENT_2_BINARY_SEARCH_TREE_H
