#include "lockFreeQueue.h"
#include <iostream>
#include <thread>
#include <set>
CQueue<int> in_queue;
CQueue<int> out_queue;
std::set<int> resultSet;

void enqueueDequeueTest(int start, int end);

int main(void) {
  std::thread t1(enqueueDequeueTest, 1, 1000);
  std::thread t2(enqueueDequeueTest, 1001, 2000);
  std::thread t3(enqueueDequeueTest, 2001, 3000);
  std::thread t4(enqueueDequeueTest, 3001, 4000);
  std::thread t5(enqueueDequeueTest, 4001, 5000);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  for (int i = 1; i <= 5000; i++) {
    resultSet.insert(out_queue.dequeue());
  }

  std::cout << resultSet.size() << std::endl;

  for (auto i = resultSet.begin(); i != resultSet.end(); i++) {
    std::cout << *i << std::endl;
  }
}

void enqueueDequeueTest(int start, int end) {
  for (int i = start; i <= end; i++) {
    in_queue.enqueue(i);
  }

  for (int i = start; i <= end; i++) {
     out_queue.enqueue(in_queue.dequeue());
  }
}

