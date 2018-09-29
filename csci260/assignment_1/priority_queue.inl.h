//------------------------------------------------------------------------------
// @file       priority_queue.inl.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------


template <typename Priority, typename Data>
PriorityQueue<Priority,Data>::PriorityQueue(int maxSize) {
    minHeap = new MinHeap<Priority,Data>(maxSize);
}


template <typename Priority, typename Data>
PriorityQueue<Priority,Data>::~PriorityQueue() {}


template <typename Priority, typename Data>
void PriorityQueue<Priority,Data>::insert(double priority, const Data &data) {}


template <typename Priority, typename Data>
Data* PriorityQueue<Priority,Data>::removeMin() {}


template <typename Priority, typename Data>
Data* PriorityQueue<Priority,Data>::removeRandom() {}


template <typename Priority, typename Data>
double PriorityQueue<Priority,Data>::minPriority() const {}


template <typename Priority, typename Data>
const Data* PriorityQueue<Priority,Data>::minData() const {}


template <typename Priority, typename Data>
bool PriorityQueue<Priority,Data>::isEmpty() const {}


template <typename Priority, typename Data>
bool PriorityQueue<Priority,Data>::isFull() const {}


template <typename Priority, typename Data>
int PriorityQueue<Priority,Data>::size() const {}
