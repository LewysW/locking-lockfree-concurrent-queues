#include "lockingQueue.h"

template <class T>
void CQueue<T>::enqueue(T payload) {
  std::lock_guard<std::mutex> data_guard(data_mutex);
  data.push(payload);
}

template <class T>
T CQueue<T>::dequeue() {
  std::lock_guard<std::mutex> data_guard(data_mutex);
  T* element = data.front();
  data.pop();
  return data.pop();
}