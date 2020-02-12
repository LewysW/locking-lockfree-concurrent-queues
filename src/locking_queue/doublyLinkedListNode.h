#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H
#include <stdint.h>
#include <stddef.h>

template <class T>
class DoublyLinkedListNode {
public:
    T element;
    DoublyLinkedListNode<T>* next;
    DoublyLinkedListNode<T>* previous;

    DoublyLinkedListNode(T element, DoublyLinkedListNode<T>* next, DoublyLinkedListNode<T>* previous) :
        element(element),
        next(next),
        previous(previous)
    {
    }
};
#endif