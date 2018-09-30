//------------------------------------------------------------------------------
// @file       priority_queue.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_PRIORITY_QUEUE_H
#define ASSIGNMENT_1_PRIORITY_QUEUE_H


#include "my_exceptions.h"
#include <iostream>


template <typename Priority, typename Data>
class PriorityQueue {
public:
    explicit PriorityQueue(int maxSize);
    ~PriorityQueue();

    void insert(Priority priority, const Data &data) throw();
    Data* removeMin();
    Data* removeRandom();

    Priority minPriority() const;
    const Data* minData() const;

    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;

private:
    struct Node {
        Priority priority;
        Data* data;
    };

    void upheap(int index);
    void downheap(int index);
    // heapify

    void decreasePriority(int index, Priority newValue) throw();

    int leftChild(int index);
    int rightChild(int index);
    int parent(int index);

    Node* heapArray;
    int maxSize;
    int size;
};


#include "priority_queue.inl.h"

#endif //ASSIGNMENT_1_PRIORITY_QUEUE_H
