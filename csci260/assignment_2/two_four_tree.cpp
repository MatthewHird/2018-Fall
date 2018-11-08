//------------------------------------------------------------------------------
// @file    two_four_tree.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#include "two_four_tree.h"
#include <iostream>
#include <utility>
#include "student.h"
#include "my_exceptions.h"


TwoFourTree::TwoFourTree()
    : root(nullptr)
    , dataList(nullptr)
    , size(0)
{}


TwoFourTree::~TwoFourTree() {
    if (root) {
        root->postorderDestroyData();
    }
}


Student& TwoFourTree::lookup(int numberId) throw(EmptyTreeError, KeyNotFoundError) {
    if (root == nullptr) {
        throw EmptyTreeError();
    }
    TwoFourNode* foundNode = root->search(numberId);
    if (foundNode == nullptr) {
        throw KeyNotFoundError();
    }

    for (int i = 0; i < 3; i++) {
        if (foundNode->keys[i] == numberId) {
            return *(foundNode->data[i]);
        }
    }

    std::cout << "Oops\n";
    return *(new Student());
}


void TwoFourTree::insert(int numberId, Student &studentInfo) throw(DuplicateKeyError) {
    if (root == nullptr) {
        root = new TwoFourNode(true);
        root->keys[0] = numberId;
        root->data[0] = &studentInfo;
        root->size = 1;
    } else {
        if (root->search(numberId) != nullptr) {
            throw DuplicateKeyError();
        }

        if (root->size == 3) {
            TwoFourNode* newRoot = new TwoFourNode(false);
            newRoot->childPtr[0] = root;
            newRoot->splitChild(0, root);

            int i = (newRoot->keys[0] < numberId) ? 1 : 0;

            newRoot->childPtr[i]->insertNotFull(numberId, studentInfo);
            root = newRoot;
        } else {
            root->insertNotFull(numberId, studentInfo);
        }
    }
}


Student& TwoFourTree::remove(int numberId) throw(EmptyTreeError, KeyNotFoundError) {
    if (root == nullptr) {
        throw EmptyTreeError();
    }
    Student* removedData = root->remove(numberId);
    if (removedData == nullptr) {
        throw KeyNotFoundError();
    }

    if (root->size == 0) {
        TwoFourNode* oldRoot = root;
        if (root->isLeaf) {
            root = nullptr;
        } else {
            root = root->childPtr[0];
        }
        delete oldRoot;
    }
    return *removedData;
}


std::string& TwoFourTree::getKeyDataList() {
    dataList = new std::string;
    dataList->append(std::to_string(size));
    root->inorderListData(dataList);
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


void TwoFourNode::insertNotFull(int key, Student &newData) throw(FullNodeError) {
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
        data[index] = &newData;
        size++;
    } else {
        for (index = size; index > 0 && keys[index - 1] > key; index--) {}

        if (childPtr[index]->size == maxSize) {
            splitChild(index, childPtr[index]);

            if (key > keys[index]) {
                index++;
            }
        }
        childPtr[index]->insertNotFull(key, newData);
    }
}


void TwoFourNode::splitChild(int index, TwoFourNode *oldChild) {
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


Student* TwoFourNode::remove(int key) {
    int index = findKey(key);

    if (index < size && keys[index] == key) {
        return isLeaf ? removeFromLeaf(index) : removeFromNonLeaf(index);
    } else {
        if (isLeaf) {
            return nullptr;
        }

        if (childPtr[index]->size == 1) {
            fill(index);
        }

        if (index > size) {
            index--;
        }

        return childPtr[index]->remove(key);
    }
}


Student* TwoFourNode::removeFromLeaf(int index) {
    Student* temp = data[index];
    for (int i = index; i < size; i++) {
        keys[i] = keys[i + 1];
        data[i] = data[i + 1];
    }
    size--;
    data[size] = nullptr;

    return temp;
}


Student* TwoFourNode::removeFromNonLeaf(int index) {
    int removedKey = keys[index];
    Student* removedData = data[index];
    data[index] = nullptr;

    if (childPtr[index]->size > 1) {
        keys[index] = getPred(index);
        data[index] = childPtr[index]->remove(keys[index]);
    } else if (childPtr[index + 1]->size > 1) {
        keys[index] = getSucc(index);
        data[index] = childPtr[index + 1]->remove(keys[index]);
    } else {
        merge(index);
        childPtr[index]->remove(removedKey);
    }
    return  removedData;
}


int TwoFourNode::getPred(int index) {
    TwoFourNode* cursor = childPtr[index];

    while (!cursor->isLeaf) {
        cursor = cursor->childPtr[cursor->size];
    }
    return cursor->keys[cursor->size - 1];
}


int TwoFourNode::getSucc(int index) {
    TwoFourNode* cursor = childPtr[index + 1];

    while (!cursor->isLeaf) {
        cursor = cursor->childPtr[0];
    }
    return cursor->keys[0];
}


void TwoFourNode::fill(int index) {
    if (index > 0 && childPtr[index - 1]->size > 1) {
        borrowFromPrev(index);
    } else if (index < size && childPtr[index + 1]->size > 1) {
        borrowFromNext(index);
    } else {
        if (index < size) {
            merge(index);
        } else {
            merge(index - 1);
        }
    }
}


void TwoFourNode::borrowFromPrev(int index) {
    TwoFourNode* child = childPtr[index];
    TwoFourNode* sibling = childPtr[index - 1];

    for (int i = child->size; i > 0; i--) { // make space in child
        child->keys[i] = child->keys[i - 1];
        child->data[i] = child->data[i - 1];
    }

    child->keys[0] = keys[index - 1]; // insert from parent to child
    child->data[0] = data[index - 1];

    if (!child->isLeaf) { // make space in child
        for (int i = child->size + 1; i > 0; i--) {
            child->childPtr[i] = child->childPtr[i - 1];
        }
    }

    if(!child->isLeaf) { // insert from sibling to child
        child->childPtr[0] = sibling->childPtr[sibling->size];
    }


    keys[index - 1] = sibling->keys[sibling->size - 1]; // insert from sibling to parent
    data[index - 1] = sibling->data[sibling->size - 1];
    sibling->data[sibling->size - 1] = nullptr; // clean up sibling

    child->size++;
    sibling->size--;
}


void TwoFourNode::borrowFromNext(int index) {
    TwoFourNode* child = childPtr[index];
    TwoFourNode* sibling = childPtr[index + 1];

    child->keys[child->size] = keys[index]; // insert from parent to child
    child->data[child->size] = data[index];

    if (!child->isLeaf) { // insert from sibling to child
        child->childPtr[child->size + 1] = sibling->childPtr[0];
    }

    keys[index] = sibling->keys[0]; // insert from sibling to parent
    data[index] = sibling->data[0];

    for (int i = 0; i < sibling->size - 1; i++) { // close space in sibling
        sibling->keys[i] = sibling->keys[i + 1];
        sibling->data[i] = sibling->data[i + 1];
    }
    sibling->data[size - 1] = nullptr;

    if (!child->isLeaf) { // close space in sibling
        for (int i = 0; i < sibling->size; i++) {
            sibling->childPtr[i] = sibling->childPtr[i + 1];
        }
    }

    child->size++;
    sibling->size--;
}


void TwoFourNode::merge(int index) {
    TwoFourNode* child = childPtr[index];
    TwoFourNode* sibling = childPtr[index + 1];

    child->keys[1] = keys[index]; // insert from parent to child
    child->data[1] = data[index];

    child->keys[2] = sibling->keys[0]; // insert from sibling to child
    child->data[2] = sibling->data[0];
    sibling->data[0] = nullptr; // cleanup sibling

    if (!child->isLeaf) {
        for (int i = 0; i < sibling->size + 1 ; i++) { // insert from sibling to child
            child->childPtr[i + 2] = sibling->childPtr[i];
        }
    }

    for (int i = index; i < size - 1; i++) { // close space in parent
        keys[i] = keys[i + 1];
        data[i] = data[i + 1];
    }
    data[size] = nullptr;

    for (int i = index + 1; i < size; i++) { // close space in parent
        child[i] = child[i + 1];
    }

    child->size = 3;
    size--;

    delete sibling;
}
