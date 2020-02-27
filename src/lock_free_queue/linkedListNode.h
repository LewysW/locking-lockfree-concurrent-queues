#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H
#include <stdint.h>
#include <stddef.h>
#include <atomic>

template <class T>
class LinkedListNode {
public:
    T element;
    std::atomic<LinkedListNode<T>*> next;

    LinkedListNode(T element, LinkedListNode<T>* next) :
        element(element),
        next(next)
    {
    }
};
#endif
