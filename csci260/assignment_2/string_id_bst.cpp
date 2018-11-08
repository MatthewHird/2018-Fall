//------------------------------------------------------------------------------
// @file    id_string_bst.cpp
// @author  Matthew Hird
// @date    November 7, 2018
//
// @brief   A binary search tree that uses non-unique strings as keys, and
//          stores the key with an integer ID. getAlphabeticalDataList() does an
//          inorder traversal, returning a string containing the stringId key
//          and intId at each node.
//------------------------------------------------------------------------------

#include "string_id_bst.h"
#include "my_exceptions.h"
#include <iostream>
#include <regex>
#include <algorithm>


StringIdBST::StringIdBST()
    : root(nullptr)
    , dataList(nullptr)
    , size(0)
{}


StringIdBST::~StringIdBST() {
    if (root) {
        postOrderDestroyData(root);
    }
}


void StringIdBST::insert(std::string stringId, int intId) {
    Node* temp = new Node;
    temp->keyString = generateKeyString(stringId);
    temp->dataString = stringId;
    temp->dataInt = intId;
    temp->left = nullptr;
    temp->right = nullptr;
    size++;

    if (isEmpty()) {
        root = temp;
        return;
    }

    Node* current = root;
    while(true) {
        if (temp->keyString < current->keyString)  {
            if (current->left == nullptr) {
                current->left = temp;
                return;
            }
            current = current->left;
        } else if (temp->keyString >= current->keyString) {
            if (current->right == nullptr) {
                current->right = temp;
                return;
            }
            current = current->right;
        }
    }
}


std::string& StringIdBST::getAlphabeticalDataList() {
    dataList = new std::string;
    dataList->append(std::to_string(size));
    inorderListData(root);
    std::string& temp = *(dataList);
    dataList = nullptr;
    return temp;
}


bool StringIdBST::isEmpty() {
    return root == nullptr;
}


std::string StringIdBST::generateKeyString(std::string dataString) {
    std::string keyString = dataString;
    std::transform(keyString.begin(), keyString.end(), keyString.begin(), ::tolower);

    std::regex letterPattern ("[^a-z]");
    keyString = std::regex_replace(keyString, letterPattern, "");

    return keyString;
}


void StringIdBST::inorderListData(StringIdBST::Node* node) {
    if (node == nullptr) {
        return;
    }
    inorderListData(node->left);

    dataList->append("\n");
    dataList->append(node->dataString);
    dataList->append("\n");
    dataList->append(std::to_string(node->dataInt));

    inorderListData(node->right);
}


void StringIdBST::postOrderDestroyData(StringIdBST::Node* node) {
    if (node == nullptr) {
        return;
    }
    postOrderDestroyData(node->left);
    postOrderDestroyData(node->right);
    delete node;
}
