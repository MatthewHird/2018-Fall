//------------------------------------------------------------------------------
// @file    id_string_bst.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#include "string_id_bst.h"
#include "my_exceptions.h"
#include <iostream>


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
    temp->stringId = stringId;
    temp->intId = intId;
    temp->left = nullptr;
    temp->right = nullptr;
    size++;

    if (isEmpty()) {
        root = temp;
        return;
    }

    Node* current = root;
    while(true) {
        if (stringId <= current->stringId)  {
            if (current->left == nullptr) {
                current->left = temp;
                return;
            }
            current = current->left;
        } else if (stringId > current->stringId) {
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


void StringIdBST::inorderListData(StringIdBST::Node* node) {
    if (node == nullptr) {
        return;
    }
    inorderListData(node->left);

    dataList->append("\n");
    dataList->append(node->stringId);
    dataList->append("\n");
    dataList->append(std::to_string(node->intId));

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
