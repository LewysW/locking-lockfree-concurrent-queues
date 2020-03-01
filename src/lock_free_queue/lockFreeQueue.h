#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H
#include "linkedList.h"
#include <iostream>

//Lock-free implementation of concurrent queue
template <class T>
class CQueue {
private:
  //Underlying linked list data structure
  LinkedList<T> data;

public:
  //Enqueue function
  void enqueue(T payload);

  //Dequeue function
  T dequeue();
};

/**
 * Enqueue function
 * @payload - element to insert into front of queue
**/ 
template <class T>
void CQueue<T>::enqueue(T payload) {
  //Inserts payload into linked list
  data.insert(payload);
}

/**
 * Dequeue function
 * return - element of type T
**/
template <class T>
T CQueue<T>::dequeue() {
  //Returns payload removed from front of linked list
  return data.remove();
}

#endif
