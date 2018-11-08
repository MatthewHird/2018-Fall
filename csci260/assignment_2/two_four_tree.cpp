//------------------------------------------------------------------------------
// @file    two_four_tree.cpp
// @author  Matthew Hird
// @date    November 7, 2018
//
// @brief   A specialized two-four tree that stores (int key)/(Student data)
//          pairs. getKeyDataList() does an inorder traversal, returning a
//          string containing the studentNumber and studentName of every Student
//          object stored in the tree. lookup() searches the tree for the
//          specified key, and returns the associated Student object.
//------------------------------------------------------------------------------

#include "two_four_tree.h"
#include <iostream>
#include <utility>
#include "student.h"
#include "my_exceptions.h"


TwoFourTree::TwoFourTree()
    : root(nullptr)
    , dataList(nullptr)
    , keyCount(0)
{}


TwoFourTree::~TwoFourTree() {
    if (root) {
        root->postorderDestroyData();
    }
}


void TwoFourTree::insert(int key, Student &studentData) throw(DuplicateKeyError) {
    if (root == nullptr) {
        root = new TwoFourNode(true);
        root->keys[0] = key;
        root->data[0] = &studentData;
        root->size = 1;
    } else {
        if (root->search(key) != nullptr) {
            throw DuplicateKeyError();
        }

        if (root->size == 3) {
            TwoFourNode* newRoot = new TwoFourNode(false);
            newRoot->childPtr[0] = root;
            newRoot->splitChild(0);

            int i = (newRoot->keys[0] < key) ? 1 : 0;

            newRoot->childPtr[i]->insertNotFull(key, studentData);
            root = newRoot;
        } else {
            root->insertNotFull(key, studentData);
        }
    }
    keyCount++;
}


Student& TwoFourTree::lookup(int key) throw(EmptyTreeError, KeyNotFoundError) {
    if (root == nullptr) {
        throw EmptyTreeError();
    }
    TwoFourNode* foundNode = root->search(key);
    if (foundNode == nullptr) {
        throw KeyNotFoundError();
    }

    for (int i = 0; i < 3; i++) {
        if (foundNode->keys[i] == key) {
            return *(foundNode->data[i]);
        }
    }

    throw KeyNotFoundError();
}


std::string& TwoFourTree::getKeyDataList() {
    dataList = new std::string;
    dataList->append(std::to_string(keyCount));
    if (root != nullptr) {
        root->inorderListData(dataList);
    }
    std::string& temp = *(dataList);
    dataList = nullptr;
    return temp;
}


TwoFourNode::TwoFourNode()
    : TwoFourNode(false)
{}


TwoFourNode::TwoFourNode(bool isLeaf)
    : isLeaf(isLeaf)
    , size(0)
{}


TwoFourNode::~TwoFourNode() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
}


TwoFourNode* TwoFourNode::search(int key) {
    int index = findKey(key);

    if (index < size && keys[index] == key) {
        return this;
    }

    if (isLeaf) {
        return nullptr;
    }

    return childPtr[index]->search(key);
}


void TwoFourNode::inorderListData(std::string* dataList) {
    for (int i = 0; i < size; i ++) {
        if (!isLeaf) {
            childPtr[i]->inorderListData(dataList);
        }
        dataList->append("\n");
        dataList->append(std::to_string(data[i]->getStudentNumber()));
        dataList->append("\n");
        dataList->append(data[i]->getStudentName());
    }
    if (!isLeaf) {
        childPtr[size]->inorderListData(dataList);
    }
}


void TwoFourNode::postorderDestroyData() {
    if (!isLeaf) {
        for (int i = 0; i < size + 1; i++) {
            childPtr[i]->postorderDestroyData();
        }
    }
    delete this;
}


int TwoFourNode::findKey(int key) {
    int index;
    for (index = 0; index < size && keys[index] < key; index++) {}

    return index;
}


void TwoFourNode::insertNotFull(int key, Student &studentData) throw(FullNodeError) {
    if (size == maxSize) {
        throw FullNodeError();
    }
    int index;

    if (isLeaf) {
        for (index = size; index > 0 && keys[index - 1] > key; index--) {
            keys[index] = keys[index - 1];
            data[index] = data[index - 1];
        }
        keys[index] = key;
        data[index] = &studentData;
        size++;
    } else {
        for (index = size; index > 0 && keys[index - 1] > key; index--) {}

        if (childPtr[index]->size == maxSize) {
            splitChild(index);

            if (key > keys[index]) {
                index++;
            }
        }
        childPtr[index]->insertNotFull(key, studentData);
    }
}


void TwoFourNode::splitChild(int index) {
    TwoFourNode* oldChild = childPtr[index];
    TwoFourNode* newChild = new TwoFourNode(oldChild->isLeaf);
    newChild->size = 1;

    newChild->keys[0] = oldChild->keys[2];
    newChild->data[0] = oldChild->data[2];
    oldChild->data[2] = nullptr;

    if (!oldChild->isLeaf) {
        newChild->childPtr[0] = oldChild->childPtr[2];
        newChild->childPtr[1] = oldChild->childPtr[3];
    }

    oldChild->size = 1;

    for (int i = size; i > index; i--) {
        childPtr[i + 1] = childPtr[i];
    }

    childPtr[index + 1] = newChild;

    for (int i = size; i > index; i--) {
        keys[i] = keys[i - 1];
        data[i] = data[i - 1];
    }

    keys[index] = oldChild->keys[1];
    data[index] = oldChild->data[1];
    oldChild->data[1] = nullptr;

    size++;
}
