#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>
#include <iostream>

template <class T>
class LinkedList {
private:
    std::atomic<LinkedListNode<T>*> head;
    std::atomic<LinkedListNode<T>*> tail;
    std::atomic<LinkedListNode<T>*> temp;

public:
    LinkedList() {
        temp = new LinkedListNode<T>(0, (LinkedListNode*) NULL);
        head = tail = temp;
    }

    void insert(T element);

    T remove();

    LinkedListNode<T>* getHead();

    LinkedListNode<T>* getTail();
};

template <class T>
void LinkedList<T>::insert(T element) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(element, (LinkedListNode*) NULL)
    LinkedListNode<T>* tempTail;

    while (true) {
        tempTail = tail.load(std::memory_order_relaxed);
        if (std::atomic_compare_exchange_weak_explicit(
            &tempTail->next,
            nullptr,
            new_node,
            std::memory_order_release,
            std::memory_order_relaxed)) {
                break;
            }
    }

    std::atomic_compare_exchange_weak_explicit(
            &tail,
            &tempTail,
            new_node,
            std::memory_order_release,
            std::memory_order_relaxed)
}

//TODO - update algorithm to use that of saved page
template <class T>
T LinkedList<T>::remove() {
    LinkedListNode<T>* tempHead;
    T element;
    while (true) {
        tempHead = head.load(std::memory_order_relaxed);

        if (tempHead->next == NULL) {
            throw std::exception("Queue empty!");
        } else {
            if (std::atomic_compare_exchange_weak_explicit(
            &head,
            &tempHead,
            tempHead->next,
            std::memory_order_release,
            std::memory_order_relaxed)) {
                break;
            }
        }
    }

    return tempHead->next->element;
}

template <class T>
LinkedListNode<T>* LinkedList<T>::getHead() {
    return head;
}

template <class T>
LinkedListNode<T>* LinkedList<T>::getTail() {
    return tail;
}

#endif
