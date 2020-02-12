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
    void insertAfter(T element, DoublyLinkedListNode<T>* predecessor);

    void emplaceBack(T element);

    void remove(DoublyLinkedListNode<T>* node);
    
    int size();
    
    void clear();

    DoublyLinkedListNode<T>* getRoot();

    DoublyLinkedListNode<T>* getTail();
};

template <class T>
void DoublyLinkedList<T>::insertAfter(T element, DoublyLinkedListNode<T>* predecessor) {
    if (currentSize == 0) {
            tail = (DoublyLinkedListNode<T>*) malloc(sizeof(DoublyLinkedListNode<T>));
            *tail = DoublyLinkedListNode(element, (DoublyLinkedListNode<T>*) NULL, (DoublyLinkedListNode<T>*) NULL);
            root = tail;
        }
        else {
            DoublyLinkedListNode<T>* new_node = (DoublyLinkedListNode<T>*) malloc(sizeof(DoublyLinkedListNode<T>));

            //If root node
            if (predecessor == NULL) {
                //Set previous to NULL and next to current root
                *new_node = DoublyLinkedListNode(element, (DoublyLinkedListNode<T>*) root, (DoublyLinkedListNode<T>*) NULL);
                //Sets root to new_node
                root = new_node;
            //Otherwise if any other node
            } else {
                *new_node = DoublyLinkedListNode(element, predecessor->next, predecessor);
                predecessor->next = new_node;

                //If next is NULL, new_node becomes tail node
                if (new_node->next == NULL) tail = new_node;
            }
        }

        currentSize++;
}

template <class T>
void DoublyLinkedList<T>::emplaceBack(T element) {
    insertAfter(element, getTail());
}

template <class T>
void DoublyLinkedList<T>::remove(DoublyLinkedListNode<T>* node) {
    if (currentSize == 1)
            clear();
        else {
            if (node != root) node->previous->next = node->next;

            if (node != tail) node->next->previous = node->previous;

            if (root == node) root = node->next;

            if (tail == node) tail = node->previous;

            free(node);
            currentSize--;
        }
}

template <class T>
int DoublyLinkedList<T>::size() {
    return currentSize;
}

template <class T>
void DoublyLinkedList<T>::clear() {
    root = tail = NULL;
    currentSize = 0;
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