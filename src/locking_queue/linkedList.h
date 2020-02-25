#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>

template <class T>
class DoublyLinkedList {
private:
    DoublyLinkedListNode<T>* root = NULL;
    DoublyLinkedListNode<T>* tail = NULL;

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

    if (tail != NULL) {
        tail->next = newNode;
    } else {
        root = newNode;
    }

    tail = newNode;
}

template <class T>
void DoublyLinkedList<T>::remove() {
    if (root != NULL) {
        root = root->next;

        if (root == NULL) {
            tail = NULL;
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