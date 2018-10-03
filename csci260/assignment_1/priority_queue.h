//------------------------------------------------------------------------------
// @file    priority_queue.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   PriorityQueue is a templated priority queue ADT. It is implemented
//          using a binary heap ADT. The expected performance of standard
//          methods are listed below (N = number of Nodes in queue):
//          insert = O(LogN), removeMin = O(logN), decreaseKey = O(logN),
//          minPriority = O(1), minData = O(1)
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_PRIORITY_QUEUE_H
#define ASSIGNMENT_1_PRIORITY_QUEUE_H


#include "my_exceptions.h"
#include <iostream>


template <typename Priority, typename Data>
class PriorityQueue {
public:
    /**
     * @brief
     * @param maxSize
     */
    explicit PriorityQueue(int maxSize);

    /**
     * @brief
     */
    ~PriorityQueue();

    /**
     * @brief
     * @param priority
     * @param data
     */
    void insert(Priority priority, Data *data) throw(FullHeapException);

    /**
     * @brief
     * @return
     */
    Data* removeMin() throw (EmptyHeapException);

    /**
     * @brief
     * @return
     */
    Data* removeRandom() throw (EmptyHeapException);

    /**
     * @brief
     * @return
     */
    Priority minPriority() const;

    /**
     * @brief
     * @return
     */
    const Data* minData() const;

    /**
     * @brief
     * @return
     */
    bool isEmpty() const;

    /**
     * @brief
     * @return
     */
    bool isFull() const;

    /**
     * @brief
     * @return
     */
    int getSize() const;

private:
    struct Node {
        Priority priority;
        Data* data;
    };

    /**
     * @brief
     * @param index
     */
    void upheap(int index);

    /**
     * @brief
     * @param index
     */
    void downheap(int index);

    /**
     * @brief
     * @param index
     * @param newValue
     */
    void decreasePriority(int index, Priority newValue) throw(InvalidPriority);

    /**
     * @brief
     * @param index
     * @return
     */
    int leftChildIndex(int index);

    /**
     * @brief
     * @param index
     * @return
     */
    int rightChildIndex(int index);

    /**
     * @brief
     * @param index
     * @return
     */
    int parentIndex(int index);

    /**
     * @brief
     * @param x
     * @param y
     */
    void swap(Node *x, Node *y);

    Node* heapArray;
    int maxSize;
    int size;
};

#include "priority_queue.inl.h"

#endif //ASSIGNMENT_1_PRIORITY_QUEUE_H
