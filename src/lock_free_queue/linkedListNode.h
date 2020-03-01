#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H
#include <stdint.h>
#include <stddef.h>
#include <atomic>

//Linked list node
template <class T>
class LinkedListNode {
public:
    //Payload of node
    T element;
    //Next pointer (atomic to allow for thread safe updates)
    std::atomic<LinkedListNode<T>*> next;

    /**
     * Constructor
     * @element - payload of node
     * @nextNode - next node in linked list
    **/
    LinkedListNode(T element, LinkedListNode<T>* nextNode) :
        element(element)
    {
        //Atomically initialises next pointer of node
        std::atomic_init(&next, nextNode);
    }
};
#endif
