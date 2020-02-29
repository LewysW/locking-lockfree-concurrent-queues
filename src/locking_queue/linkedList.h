#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "linkedListNode.h"
#include <stdlib.h>
#include <atomic>
#include <stdexcept>

template <class T>
class LinkedList {
private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    LinkedListNode<T>* temp;

public:
    LinkedList() {
        temp = new LinkedListNode<T>(0, (LinkedListNode<T>*) NULL);
        head = tail = temp;
    }

    void insert(T element);

    T remove();

    LinkedListNode<T>* getHead();

    LinkedListNode<T>* getTail();
};

template <class T>
void LinkedList<T>::insert(T element) {
    //Creates new node pointer and gives it a value
    LinkedListNode<T>* newNode = new LinkedListNode<T>(element, (LinkedListNode<T>*) NULL);

    tail->next = newNode;

    tail = newNode;
}

template <class T>
T LinkedList<T>::remove() {
    T element;

    if (head->next == NULL) {
        throw std::exception();
    } else {
        element = head->next->element;
        head = head->next;
    }

    return element;
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
