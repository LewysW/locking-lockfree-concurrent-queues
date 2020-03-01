#ifndef LOCKING_QUEUE_H
#define LOCKING_QUEUE_H
#include <mutex>
#include "linkedList.h"
#include <iostream>

//Locking implementation of concurrent queue
template <class T>
class CQueue {
private:
  //Underlying linked list data structure
  LinkedList<T> data;
  //Mutex to restrict access to data
  std::mutex data_mutex;

public:
  //Enqueue function
  void enqueue(T payload);

  //Dequeue function
  T dequeue();
};

/**
 * Enqueue function
 * @payload - element to insert into front of queue
 */
template <class T>
void CQueue<T>::enqueue(T payload) {
  //locks mutex until out of scope of function
  std::lock_guard<std::mutex> data_guard(data_mutex);
  //Inserts payload into linked list
  data.insert(payload);
}

/**
 * Dequeue function
 * return - element of type T
 */
template <class T>
T CQueue<T>::dequeue() {
  //locks mutex until out of scope of function
  std::lock_guard<std::mutex> data_guard(data_mutex);
  //Returns payload removed from front of linked list
  return data.remove();
}

#endif
