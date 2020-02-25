#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include "doublyLinkedListNode.h"
#include <stdlib.h>

template <class T>
class DoublyLinkedList {
private:
    DoublyLinkedListNode<T>* root = NULL;
    DoublyLinkedListNode<T>* tail = NULL;
    int currentSize = 0;

public:
    void insert(T element);

    void remove();

    int size();

    DoublyLinkedListNode<T>* getRoot();

    DoublyLinkedListNode<T>* getTail();
};

template <class T>
void DoublyLinkedList<T>::insert(T element) {
    //Creates new node pointer and gives it a value
    DoublyLinkedListNode<T>* newNode = (DoublyLinkedListNode<T>*) malloc(sizeof(DoublyLinkedListNode<T>));
    *newNode = DoublyLinkedListNode(element, (DoublyLinkedListNode<T>*) NULL, (DoublyLinkedListNode<T>*) NULL);

    //TODO - CAS for value in tail to newNode->previous
    newNode->previous = tail;

    //Restructure so that there is a single CAS to update tail
    if (tail != NULL) {
        tail->next = newNode;
    } else {
        //CAS to update root
        root = newNode;
    }

    tail = newNode;

    //CAS to update currentSize
    currentSize++;
}

template <class T>
void DoublyLinkedList<T>::remove() {
    if (currentSize > 0) {
        DoublyLinkedListNode<T>* temp = root;
        if (root->next != NULL)
            root = root->next;
        free(temp);
        currentSize--;
    }
}

template <class T>
int DoublyLinkedList<T>::size() {
    return currentSize;
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
