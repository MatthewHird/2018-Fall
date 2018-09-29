//------------------------------------------------------------------------------
// @file       priority_queue.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_PRIORITY_QUEUE_H
#define ASSIGNMENT_1_PRIORITY_QUEUE_H

#include "min_heap.h"


template <typename Priority, typename Data>
class PriorityQueue {
public:
    explicit PriorityQueue(int maxSize);
    ~PriorityQueue();

    void insert(double priority, const Data &data);
    Data* removeMin();
    Data* removeRandom();

    double minPriority() const;
    const Data* minData() const;

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

private:

    MinHeap<Priority,Data>* minHeap;
};

#include "priority_queue.inl.h"

#endif //ASSIGNMENT_1_PRIORITY_QUEUE_H
