#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H
#include <stdint.h>
#include <stddef.h>

template <class T>
class LinkedListNode {
public:
    T element;
    LinkedListNode<T>* next;

    LinkedListNode(T element, LinkedListNode<T>* next) :
        element(element),
        next(next)
    {
    }
};
#endif
