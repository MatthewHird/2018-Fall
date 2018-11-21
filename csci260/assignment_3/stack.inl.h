//------------------------------------------------------------------------------
// @file       stack.inl.h
// @author     Matthew Hird
// @date       March 17, 2018
//
// @brief      Implementation of the templated class Stack. Contains basic
//             public methods typical of a stack (push, pop, peek, is_empty,
//             and clear). The stack is implemented using a singly linked list.
//------------------------------------------------------------------------------

#include "my_exceptions.h"


template<typename Data>
Stack<Data>::Stack()
{
    head = nullptr;
}


template<typename Data>
Stack<Data>::~Stack()
{
    while (! is_empty())
    {
        pop();
    }
}


template<typename Data>
void Stack<Data>::push(const Data& data)
{
    Node* ptr = new Node;
    ptr->data = data;

    ptr->next = head;
    head = ptr;
}


template<typename Data>
Data Stack<Data>::pop()throw(EmptyStack)
{
    if (is_empty())
    {
        throw EmptyStack();
    }

    Node* ptr = head;
    Data data = head->data;
    head = head->next;
    delete ptr;
    return data;
}


template<typename Data>
const Data& Stack<Data>::peek()throw(EmptyStack)
{
    if (is_empty())
    {
        throw EmptyStack();
    }

    return head->data;
}


template<typename Data>
bool Stack<Data>::is_empty()
{
    return (head == nullptr);
}


template<typename Data>
void Stack<Data>::clear()
{
    while (! is_empty())
    {
        pop();
    }
}
