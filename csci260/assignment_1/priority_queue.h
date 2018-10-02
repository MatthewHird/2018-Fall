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

    void insert(Priority priority, Data *data) throw(FullHeapException);
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

    void decreasePriority(int index, Priority newValue) throw(InvalidPriority);

    int leftChildIndex(int index);
    int rightChildIndex(int index);
    int parentIndex(int index);

    void swap(Node *x, Node *y);

    Node* heapArray;
    int maxSize;
    int size;
};

#include "priority_queue.inl.h"

#endif //ASSIGNMENT_1_PRIORITY_QUEUE_H
