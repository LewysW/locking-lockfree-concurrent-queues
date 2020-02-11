#ifndef LOCKING_QUEUE_H
#define LOCKING_QUEUE_H
#include <mutex>
#include <queue>

template <class T>
class CQueue {
private:
  std::queue<T> data;
  std::mutex data_mutex;

public:
  void enqueue(T payload);
  T dequeue();
};

#endif