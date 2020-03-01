#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>
#include <iostream>
#include <stdexcept>

template <class T>
class LinkedList {
private:
    std::atomic<LinkedListNode<T>*> head;
    std::atomic<LinkedListNode<T>*> tail;
    LinkedListNode<T>* temp;

public:
    LinkedList() {
        temp = new LinkedListNode<T>(0, (LinkedListNode<T>*) NULL);
        std::atomic_init(&head, temp);
        std::atomic_init(&tail, temp);
    }

    void insert(T element);

    T remove();
};

template <class T>
void LinkedList<T>::insert(T element) {
    LinkedListNode<T>* newNode = new LinkedListNode<T>(element, (LinkedListNode<T>*) NULL);
    LinkedListNode<T>* tempTail;
    LinkedListNode<T>* tempNext;

    while (true) {
        tempTail = tail.load(std::memory_order_relaxed);
        tempNext = NULL;

        if (std::atomic_compare_exchange_weak_explicit(
            &tempTail->next,
            &tempNext,
            newNode,
            std::memory_order_release,
            std::memory_order_relaxed)) {
                break;
            }
    }

    std::atomic_compare_exchange_weak_explicit(
            &tail,
            &tempTail,
            newNode,
            std::memory_order_release,
            std::memory_order_relaxed);

}

template <class T>
T LinkedList<T>::remove() {
    LinkedListNode<T>* tempHead;
    LinkedListNode<T>* tempTail;
    LinkedListNode<T>* tempNext;
    T element;
    while (true) {
        tempHead = head.load(std::memory_order_relaxed);
        tempTail = tail.load(std::memory_order_relaxed);
        tempNext = tempHead->next.load(std::memory_order_relaxed);

        if (tempTail == tempHead) {
            if (tempNext == NULL) {
                throw std::exception();
            }

            std::atomic_compare_exchange_weak_explicit(
            &tail,
            &tempTail,
            tempNext,
            std::memory_order_release,
            std::memory_order_relaxed);
        } else {
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

    return tempNext->element;
}

#endif
