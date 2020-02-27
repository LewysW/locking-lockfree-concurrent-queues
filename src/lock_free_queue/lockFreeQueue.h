#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H
#include "linkedList.h"
#include <iostream>

template <class T>
class CQueue {
private:
  LinkedList<T> data;

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
  return data.remove();
}

#endif
