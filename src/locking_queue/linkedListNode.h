#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H
#include <stdint.h>
#include <stddef.h>

template <class T>
class DoublyLinkedListNode {
public:
    T element;
    DoublyLinkedListNode<T>* next;

    DoublyLinkedListNode(T element, DoublyLinkedListNode<T>* next) :
        element(element),
        next(next)
    {
    }
};
#endif
