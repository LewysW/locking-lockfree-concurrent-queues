#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>

template <class T>
class DoublyLinkedList {
private:
    std::atomic<DoublyLinkedListNode<T>*> root = NULL;
    std::atomic<DoublyLinkedListNode<T>*> tail = NULL;

    int currentSize = 0;

public:
    void insert(T element);

    void remove();

    DoublyLinkedListNode<T>* getRoot();

    DoublyLinkedListNode<T>* getTail();
};

template <class T>
void DoublyLinkedList<T>::insert(T element) {
    //Creates new node pointer and gives it a value
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(element, (DoublyLinkedListNode<T>*) NULL);
    DoublyLinkedListNode<T>* tailTemp = tail.load(std::memory_order_relaxed);
    DoublyLinkedListNode<T>* rootTemp = root.load(std::memory_order_relaxed);

    //Restructure so that there is a single CAS to update tail
    if (tailTemp != NULL) {
        //Sets tail next pointer to newNode
        tailTemp->next = newNode;
    } else {
        //Sets root to newNode
        while(!std::atomic_compare_exchange_weak_explicit(
                            &root,
                            &rootTemp,
                            newNode,
                            std::memory_order_release,
                            std::memory_order_relaxed));
    }

    while(!std::atomic_compare_exchange_weak_explicit(
                        &tail,
                        &tailTemp,
                        newNode,
                        std::memory_order_release,
                        std::memory_order_relaxed));
}

template <class T>
void DoublyLinkedList<T>::remove() {
    if (root != NULL) {
        DoublyLinkedListNode<T>* temp = root.load(std::memory_order_relaxed);
        if (temp != NULL) {
            //Sets root to root->next to remove the front node
            while(!std::atomic_compare_exchange_weak_explicit(
                                &root,
                                &temp,
                                temp->next,
                                std::memory_order_release,
                                std::memory_order_relaxed));
        }
    }
}

template <class T>
DoublyLinkedListNode<T>* DoublyLinkedList<T>::getRoot() {
    return root;
}

template <class T>
DoublyLinkedListNode<T>* DoublyLinkedList<T>::getTail() {
    return tail;
}

#endif
