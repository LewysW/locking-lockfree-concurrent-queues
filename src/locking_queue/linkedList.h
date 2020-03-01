#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>
#include <stdexcept>

//Linked list class acting as the underlying 
//implementation for the locking queue
template <class T>
class LinkedList {
private:
    //Pointer to head of list
    LinkedListNode<T>* head;
    //Pointer to tail of list
    LinkedListNode<T>* tail;
    //Dummy node (avoids having to initially check for NULL pointers)
    LinkedListNode<T>* temp;

public:
    LinkedList() {
        //Initialises dummy node with next as NULL (payload is irrelevant so set to 0)
        temp = new LinkedListNode<T>(0, (LinkedListNode<T>*) NULL);
        //Sets head and tail to dummy node as list is initially empty
        head = tail = temp;
    }

    //Inserts node with payload T to tail of linked list
    void insert(T element);

    //Removes node from front of linked list 
    //and returns its payload of type T
    T remove();
};

/**
 * Inserts a node at the tail of the linked list
 * @element - payload to assign node 
 * inserted at tail of linked list
 */
template <class T>
void LinkedList<T>::insert(T element) {
    //Creates new node pointer and sets its payload to the given element
    LinkedListNode<T>* newNode = new LinkedListNode<T>(element, (LinkedListNode<T>*) NULL);

    //Sets the current next pointer of tail to the new node..
    tail->next = newNode;
    
    //..and updates the new node to be the new tail of the list
    tail = newNode;
}

/**
 * Removes a node from the front of the linked list
 * return - payload T of node at head->next
**/
template <class T>
T LinkedList<T>::remove() {
    T element;

    //If there is only a dummy node in the list
    if (head->next == NULL) {
        //List must be empty so throw exception
        throw std::exception();
    } else {
        //Otherwise get the payload of the next node in the list
        element = head->next->element;
        //And set that node to the new dummy node
        head = head->next;
    }
    
    //Returns payload of 'removed' node (i.e. new dummy node)
    return element;
}

#endif
