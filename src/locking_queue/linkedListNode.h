#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H
#include <stdint.h>
#include <stddef.h>

//Linked list node
template <class T>
class LinkedListNode {
public:
    //Payload of node
    T element;
    //Next pointer
    LinkedListNode<T>* next;

    /**
     * Constructor
     * @element - payload of node
     * @next - pointer to next node 
    **/
    LinkedListNode(T element, LinkedListNode<T>* next) :
        element(element),
        next(next)
    {
    }
};
#endif
