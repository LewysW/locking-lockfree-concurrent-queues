#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>
#include <iostream>
#include <stdexcept>

//Linked list class acting as the underlying 
//implementation for the lock-free queue
template <class T>
class LinkedList {
private:
    //Atomic pointer to head of list
    std::atomic<LinkedListNode<T>*> head;
    //Atomic pointer to tail of list
    std::atomic<LinkedListNode<T>*> tail;
    //Dummy node (avoids having to initially check for NULL pointers)
    LinkedListNode<T>* temp;

public:
    LinkedList() {
        //Initialises dummy node with next as NULL (payload is irrelevant so set to 0)
        temp = new LinkedListNode<T>(0, (LinkedListNode<T>*) NULL);
        //Initialises head and tail to the dummy node as list is initially empty
        std::atomic_init(&head, temp);
        std::atomic_init(&tail, temp);
    }

    //Inserts node with payload T to tail of linked list
    void insert(T element);

    //Removes node from front of linked list
    //and returns its payload of type T
    T remove();
};

/**
 * Inserts a node at the tail of the linked list using compare and swap
 * (atomic_compare_exchange weak_explicit)
 * @element - payload to assign node inserted at tail of linked list
**/
template <class T>
void LinkedList<T>::insert(T element) {
    //Create node to be inserted and initialise with payload
    LinkedListNode<T>* newNode = new LinkedListNode<T>(element, (LinkedListNode<T>*) NULL);
    //Stores current value of tail
    LinkedListNode<T>* tempTail;
    //Stores NULL - cannot explicity compare NULL in CAS operation
    LinkedListNode<T>* tempNext;

    //Loops while insert has not succeeded
    while (true) {
        //Loads current value of tail
        tempTail = tail.load(std::memory_order_relaxed);
        //Stores NULL in next for CAS comparison
        tempNext = NULL;
        
        //CAS operation:
        //if no other thread has tried to insert since we
        //loaded tail (i.e. tempTail->next is NULL),
        //set value of next to newNode (inserts value)
        if (std::atomic_compare_exchange_weak_explicit(
            &tempTail->next,
            &tempNext,
            newNode,
            std::memory_order_release,
            std::memory_order_relaxed)) {
                break;
            }

    }

    /**
     * CAS operation:
     * Updates tail of list to newNode.
     * Will always succeed for last thread which
     * has updated tail->next because the first CAS\textbf{void insert(T element):}
    \begin{verbatim}
     * so the comparison will fail as tempTail->next
     * is not equal to tempNext (NULL).
    **/
    std::atomic_compare_exchange_weak_explicit(

            &tail,
            &tempTail,
            newNode,
            std::memory_order_release,
            std::memory_order_relaxed);

}

/**
 * Removes a node from the front of the linked list using compare and swap
 * return - payload T of node at head->next
**/
template <class T>
T LinkedList<T>::remove() {
    //Local variables to store head, tail and head->next
    LinkedListNode<T>* tempHead;
    LinkedListNode<T>* tempTail;
    LinkedListNode<T>* tempNext;
    T element;

    //Loop while deletion has not succeeded
    while (true) {
        //Load head, tail and head->next
        tempHead = head.load(std::memory_order_relaxed);
        tempTail = tail.load(std::memory_order_relaxed);
        tempNext = tempHead->next.load(std::memory_order_relaxed);
        
        //If the head and tail pointers are equal
        if (tempTail == tempHead) {
            //Throw exception if list is empty
            if (tempNext == NULL) {
                throw std::exception();
            }

            /**
             * Otherwise we must be deleting an item while
             * another thread is inserting the first item
             * in the list but before it has updated the tail pointer.
             * This CAS operation ensures the tail pointer is correctly
             * updated before we proceed:
            **/
            std::atomic_compare_exchange_weak_explicit(
            &tail,
            &tempTail,
            tempNext,
            std::memory_order_release,
            std::memory_order_relaxed);
        } else {
            //Otherwise if there is an item in the list and
            //the tail pointer has been correctly updated,
            //using CAS, set head to head->next.
            if (std::atomic_compare_exchange_weak_explicit(
                &head,
                &tempHead,
                tempNext,
                std::memory_order_release,
                std::memory_order_relaxed)) {
                    break;
                }
        }
    }
    
    //Return the value of head->next->element
    return tempNext->element;
}

#endif
