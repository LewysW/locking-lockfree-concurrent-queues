#include "lockingQueue.h"
#include <iostream>

int main(void) {
  CQueue<int> queue;

  queue.enqueue(17);
  queue.enqueue(12);
  queue.enqueue(46);

  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;
}