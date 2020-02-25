#include "lockFreeQueue.h"
#include <iostream>

int main(void) {
  CQueue<int> queue;
  queue.enqueue(17);
  queue.enqueue(12);
  queue.enqueue(46);

  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;

  queue.enqueue(4);
  queue.enqueue(5);
  queue.enqueue(6);

  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;

  queue.enqueue(7);
  queue.enqueue(8);

  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;
  std::cout << queue.dequeue() << std::endl;
}
