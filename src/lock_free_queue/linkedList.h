#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>
#include <iostream>

template <class T>
class LinkedList {
private:
    std::atomic<LinkedListNode<T>*> root = NULL;
    std::atomic<LinkedListNode<T>*> tail = NULL;

public:
    void insert(T element);

    void remove();

    LinkedListNode<T>* getRoot();

    LinkedListNode<T>* getTail();
};

template <class T>
void LinkedList<T>::insert(T element) {
    //Creates new node pointer and gives it a value
    LinkedListNode<T>* newNode = new LinkedListNode<T>(element, (LinkedListNode<T>*) NULL);
    LinkedListNode<T>* tailTemp;
    
    //Keep trying until insert successful
    while (true) {
        tailTemp = tail.load(std::memory_order_relaxed);
        LinkedListNode<T>* rootTemp = root.load(std::memory_order_relaxed);

        //If at least one item in list (to avoid segfault on tail->next)
        if (tailTemp != NULL) {
            //Sets tail next pointer to newNode
            LinkedListNode<T>* next = tailTemp->next.load(std::memory_order_relaxed);

            //If next is available to be updated with new node
            if (next == NULL) {
                //Update end of list and break
                if (std::atomic_compare_exchange_weak_explicit(
                    &tailTemp->next,
                    &next,
                    newNode,
                    std::memory_order_release,
                    std::memory_order_relaxed)) {
                        break;
                }
            //Otherwise point tail pointer to new value inserted by some other thread    
            } else {
                //If other thread inserted between this thread's operation then update tail to next
                std::atomic_compare_exchange_weak_explicit(
                    &tail,
                    &tailTemp,
                    next,
                    std::memory_order_release,
                    std::memory_order_relaxed);
            }
        //Nothing in list    
        } else {
            //If front of list is pointing to nothing
            if (rootTemp == NULL) {
                //Point root to new node
                if (std::atomic_compare_exchange_weak_explicit(
                    &root,
                    &rootTemp,
                    newNode,
                    std::memory_order_release,
                    std::memory_order_relaxed)) {
                        break;
                }
            //Otherwise other thread has updated root in the interim, need to update our tail    
            } else {
                std::atomic_compare_exchange_weak_explicit(
                    &tail,
                    &tailTemp,
                    root,
                    std::memory_order_release,
                    std::memory_order_relaxed);
            }
        }
    }

    std::atomic_compare_exchange_weak_explicit(
            &tail,
            &tailTemp,
            newNode,
            std::memory_order_release,
            std::memory_order_relaxed);

}

template <class T>
T LinkedList<T>::remove() {
    LinkedListNode<T>* tempRoot = root.load(std::memory_order_relaxed);
    LinkedListNode<T>* tempTail = tail.load(std::memory_order_relaxed);
    if (tempRoot != NULL) {
        //Sets root to root->next to remove the front node
        while(!std::atomic_compare_exchange_weak_explicit(
                            &root,
                            &tempRoot,
                            tempRoot->next,
                            std::memory_order_release,
                            std::memory_order_relaxed));

        if (tempRoot->next == NULL) {
            LinkedListNode<T>* temp = NULL;

            while(!std::atomic_compare_exchange_weak_explicit(
                                &tail,
                                &tempTail,
                                temp,
                                std::memory_order_release,
                                std::memory_order_relaxed));
        }
    }

    //TODO - ensure thread blocks if nothing to remove
    //Make sure concurrent code is correct
    //Return value from here to dequeue function
}

template <class T>
LinkedListNode<T>* LinkedList<T>::getRoot() {
    return root;
}

template <class T>
LinkedListNode<T>* LinkedList<T>::getTail() {
    return tail;
}

#endif
