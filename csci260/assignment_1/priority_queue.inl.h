//------------------------------------------------------------------------------
// @file       priority_queue.inl.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#include <cstdlib>
#include <iostream>


template <typename Priority, typename Data>
PriorityQueue<Priority,Data>::PriorityQueue(int maxSize)
        : maxSize(maxSize)
        , size(0)
{
    heapArray = new Node[maxSize];
}


template <typename Priority, typename Data>
PriorityQueue<Priority,Data>::~PriorityQueue() {
    for (int i = 0; i < maxSize; i++) {
        delete heapArray[i].data;
    }
    delete heapArray;
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::insert(Priority priority, const Data &data) throw() {
    if (isFull()) {
        // throw full_heap_exception
    }

    heapArray[size] = Node();
    heapArray[size].priority = priority;
    heapArray[size].data = data;
    size++;
    // upheap
}


template <typename Priority, typename Data>
Data* PriorityQueue<Priority,Data>::removeMin() {
    Node tempNode = std::move(heapArray[0]);
    heapArray[0] = std::move(heapArray[size - 1]);
    size--;
    // downheap
    return tempNode.data;
}


template <typename Priority, typename Data>
Data* PriorityQueue<Priority,Data>::removeRandom() {
    int index = std::rand() % getSize();
    decreasePriority(index, 0);
    return removeMin();
}


template <typename Priority, typename Data>
Priority PriorityQueue<Priority,Data>::minPriority() const {
    return heapArray[0].priority;
}


template <typename Priority, typename Data>
const Data* PriorityQueue<Priority,Data>::minData() const {
    return heapArray[0].data;
}


template <typename Priority, typename Data>
bool PriorityQueue<Priority,Data>::isEmpty() const {
    return size <= 0;
}


template <typename Priority, typename Data>
bool PriorityQueue<Priority,Data>::isFull() const {
    return size >= maxSize;
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::getSize() const {
    return size;
}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::upheap(int index) {}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::downheap(int index) {}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::decreasePriority(int index, Priority newValue) throw() {
    if (newValue < 0) {
        // invalid priority exception
    }
    heapArray[index].priority = newValue;

    // upheap
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::leftChild(int index) {
    return 2 * index + 1;
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::rightChild(int index) {
    return 2 * index + 2;
}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::parent(int index) {
    return (index - 1) / 2;
}
