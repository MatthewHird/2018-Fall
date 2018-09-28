//------------------------------------------------------------------------------
// @file       priority_queue.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_PRIORITY_QUEUE_H
#define ASSIGNMENT_1_PRIORITY_QUEUE_H

template <typename Data>
class PriorityQueue {
public:
    PriorityQueue(int maxSize);
    ~PriorityQueue();

    void insert(int priority, const Data& data);
    Data* removeMin();
    Data* removeRandom();

    int minPriority() const;
    const Data* minData() const;

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

private:
    struct Node {
        int priority;
        Data* data;
    };

    Node* heapArray;
    int maxSize;
    int nodeCount;
};

#include "priority_queue.inl.h"

#endif //ASSIGNMENT_1_PRIORITY_QUEUE_H
