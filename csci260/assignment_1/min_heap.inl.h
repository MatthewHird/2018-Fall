//------------------------------------------------------------------------------
// @file       min_heap.inl.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

template <typename Key, typename Data>
MinHeap<Key,Data>::MinHeap(int maxSize)
    : maxSize(maxSize)
    , size(0)
{
    heapArray = new Node[maxSize];
}


template <typename Key, typename Data>
MinHeap<Key,Data>::~MinHeap() {
    for (int i = 0; i < maxSize; i++) {
        delete heapArray[i].data;
    }
    delete heapArray;
}


template <typename Key, typename Data>
void MinHeap<Key,Data>::insert(Key key, Data &data) {}


template <typename Key, typename Data>
Data* MinHeap<Key,Data>::removeMin() {}


template <typename Key, typename Data>
Key MinHeap<Key,Data>::minPriority() {}


template <typename Key, typename Data>
const Data* MinHeap<Key,Data>::minData() {}


template <typename Key, typename Data>
void MinHeap<Key,Data>::decreaseKey(int index, Key newValue) {}


template <typename Key, typename Data>
bool MinHeap<Key,Data>::isEmpty() {}


template <typename Key, typename Data>
bool MinHeap<Key,Data>::isFull() {}


template <typename Key, typename Data>
int MinHeap<Key,Data>::getSize() {}


template <typename Key, typename Data>
void MinHeap<Key,Data>::upheap(int index) {}


template <typename Key, typename Data>
void MinHeap<Key,Data>::downheap(int index) {}


template <typename Key, typename Data>
int MinHeap<Key,Data>::leftChild(int index) {}


template <typename Key, typename Data>
int MinHeap<Key,Data>::rightChild(int index) {}


template <typename Key, typename Data>
int MinHeap<Key,Data>::parent(int index) {}


