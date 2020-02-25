#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>

template <class T>
class DoublyLinkedList {
private:
    //std::atomic<DoublyLinkedListNode<T>*> root = NULL;
    //std::atomic<DoublyLinkedListNode<T>*> tail = NULL;

    DoublyLinkedListNode<T>* root = NULL;
    DoublyLinkedListNode<T>* tail = NULL;
    int currentSize = 0;

public:
    void insert(T element);

    void remove();

    DoublyLinkedListNode<T>* getRoot();

    DoublyLinkedListNode<T>* getTail();

    void CAS(void* loc, void* exp, void* val);
};

template <class T>
void DoublyLinkedList<T>::insert(T element) {
    //Creates new node pointer and gives it a value
    DoublyLinkedListNode<T>* newNode = (DoublyLinkedListNode<T>*) malloc(sizeof(DoublyLinkedListNode<T>));
    *newNode = DoublyLinkedListNode(element, (DoublyLinkedListNode<T>*) NULL);

    //TODO - CAS for value in tail to newNode->previous
    //newNode->previous = tail.load(std::memory_order_relaxed);

    //Restructure so that there is a single CAS to update tail
    if (tail != NULL) {
        tail->next = newNode;

        //CAS(&tail, &newNode->previous, newNode);

    } else {
        //CAS to update root
        root = newNode;
    }

    //CAS(&tail, &newNode->previous, newNode);
    tail = newNode;
}

template <class T>
void DoublyLinkedList<T>::remove() {
    if (root != NULL) {
        DoublyLinkedListNode<T>* temp = root;
        if (root->next != NULL)
            root = root->next;
        free(temp);
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
