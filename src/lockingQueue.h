#ifndef LOCKING_QUEUE_H
#define LOCKING_QUEUE_H
#include <mutex>
#include <queue>
#include <iostream>

template <class T>
class CQueue {
private:
  T t;
  std::queue<T> data;
  std::mutex data_mutex;

public:
  CQueue() = default;
  void enqueue(T payload);
  T dequeue();
};

template <class T>
void CQueue<T>::enqueue(T payload) {
  std::lock_guard<std::mutex> data_guard(data_mutex);
  data.push(payload);
}

template <class T>
T CQueue<T>::dequeue() {
  std::lock_guard<std::mutex> data_guard(data_mutex);
  T element = data.front();
  data.pop();
  return element;
}

#endif