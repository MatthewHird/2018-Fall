//------------------------------------------------------------------------------
// @file       min_heap.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_MIN_HEAP_H
#define ASSIGNMENT_1_MIN_HEAP_H


template <typename Key, typename Data>
class MinHeap {
public:
    explicit MinHeap(int maxSize);
    ~MinHeap();

    void insert(Key key, Data& data);
    Data* removeMin();
    Key minPriority();
    const Data* minData();
    void decreaseKey(int index, Key newValue);

    bool isEmpty();
    bool isFull();
    int getSize();

private:
    struct Node {
        Key key;
        Data* data;
    };

    void upheap(int index);
    void downheap(int index);
    // heapify

    int leftChild(int index);
    int rightChild(int index);
    int parent(int index);

    Node* heapArray;
    int maxSize;
    int size;
};

#include "min_heap.inl.h"

#endif //ASSIGNMENT_1_MIN_HEAP_H
