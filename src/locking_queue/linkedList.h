#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>

template <class T>
class LinkedList {
private:
    LinkedListNode<T>* root = NULL;
    LinkedListNode<T>* tail = NULL;

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

    if (tail != NULL) {
        tail->next = newNode;
    } else {
        root = newNode;
    }

    tail = newNode;
}

template <class T>
void LinkedList<T>::remove() {
    if (root != NULL) {
        root = root->next;

        if (root == NULL) {
            tail = NULL;
        }
    }
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
