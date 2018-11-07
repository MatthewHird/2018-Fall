//------------------------------------------------------------------------------
// @file    two_four_tree.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief
//------------------------------------------------------------------------------

#include "two_four_tree.h"
#include <iostream>
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
        if (foundNode->key[i] == numberId) {
            return *(foundNode->data[i]);
        }
    }

    std::cout << "Oops\n";
    return *(new Student());
}


void TwoFourTree::insert(int numberId, Student &studentInfo) throw(DuplicateKeyError) {
    if (root == nullptr) {
        root = new TwoFourNode();
        root->key[0] = numberId;
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

            int i = (newRoot->key[0] < numberId) ? 0 : 1;

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


TwoFourNode* TwoFourNode::search(int k) {
    int index = findKey(k);

    if (index < size && key[index] == k) {
        return this;
    }

    if (isLeaf) {
        return nullptr;
    }

    return childPtr[index]->search(k);
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


int TwoFourNode::findKey(int k) {
    int index;
    for (index = 0; index < size && key[index] < k; index++) {}

    return index;
}


void TwoFourNode::insertNotFull(int k, Student &newData) throw(FullNodeError) {
    if (size == maxSize) {
        throw FullNodeError();
    }
    int index;

    if (isLeaf) {
        for (index = size; index > 0 && key[index - 1] > k; index--) {
            key[index] = key[index - 1];
            data[index] = data[index - 1];
        }
        key[index] = k;
        data[index] = &newData;
        size++;
    } else {
        for (index = size; index > 0 && key[index - 1] > k; index--) {}

        if (childPtr[index]->size == maxSize) {
            splitChild(index, childPtr[index]);

            if (key[index] < k) {
                index++;
            }
        }
        childPtr[index]->insertNotFull(k, newData);
    }
}


void TwoFourNode::splitChild(int index, TwoFourNode *y) {
    TwoFourNode* z = new TwoFourNode(y->isLeaf);
    z->size = 1;

    z->key[0] = y->key[2];
    z->data[0] = y->data[2];
    y->data[2] = nullptr;

    if (!y->isLeaf) {
        z->childPtr[0] = y->childPtr[1];
        y->childPtr[1] = nullptr;
        z->childPtr[1] = y->childPtr[2];
        y->childPtr[2] = nullptr;
    }

    y->size = 1;

    for (int i = 1; i > 0; i--) {
        childPtr[i + 1] = childPtr[i];
    }

    childPtr[index + 1] = z;

    for (int i = size; i > index; i--) {
        key[i] = key[i - 1];
        data[i] = data[i - 1];
    }

    key[index] = y->key[1];
    data[index] = y->data[1];

    size++;
}


Student* TwoFourNode::remove(int k) {
    int index = findKey(k);

    if (index < size && key[index] == k) {
        return isLeaf ? removeFromLeaf(k) : removeFromNonLeaf(k);
    } else {
        if (isLeaf) {
            return nullptr;
        }
    }
}


Student* TwoFourNode::removeFromLeaf(int idx) {

}


Student* TwoFourNode::removeFromNonLeaf(int idx) {

}


int TwoFourNode::getPred(int idx) {

}


int TwoFourNode::getSucc(int idx) {

}


void TwoFourNode::fill(int idx) {

}


void TwoFourNode::borrowFromPrev(int idx) {

}


void TwoFourNode::borrowFromNext(int idx) {

}


void TwoFourNode::merge(int idx) {

}
