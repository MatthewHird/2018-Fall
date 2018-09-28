//------------------------------------------------------------------------------
// @file       priority_queue.cpp
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

template <typename Data>
PriorityQueue<Data>::PriorityQueue(int maxSize) {}


template <typename Data>
PriorityQueue<Data>::~PriorityQueue() {}


template <typename Data>
void PriorityQueue<Data>::insert(int priority, const Data& data) {}


template <typename Data>
Data* PriorityQueue<Data>::removeMin() {}


template <typename Data>
Data* PriorityQueue<Data>::removeRandom() {}


template <typename Data>
int PriorityQueue<Data>::minPriority() const {}


template <typename Data>
const Data* PriorityQueue<Data>::minData() const {}


template <typename Data>
bool PriorityQueue<Data>::isEmpty() const {}


template <typename Data>
bool PriorityQueue<Data>::isFull() const {}


template <typename Data>
int PriorityQueue<Data>::size() const {}
