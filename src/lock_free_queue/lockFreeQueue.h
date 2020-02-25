#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H
#include "../doublyLinkedList.h"
#include <iostream>

template <class T>
class CQueue {
private:
  DoublyLinkedList<T> data;

public:
  CQueue() = default;
  void enqueue(T payload);
  T dequeue();
};

template <class T>
void CQueue<T>::enqueue(T payload) {
  data.insert(payload);
}

template <class T>
T CQueue<T>::dequeue() {
  T element = data.getRoot()->element;
  data.remove();
  return element;
}

#endif
