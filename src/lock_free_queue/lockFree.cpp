#include "lockFreeQueue.h"
#include <iostream>
#include <thread>
#include <set>
#include <vector>

#define MAX_WORKLOAD 100000
#define INITIAL_WORKLOAD 10000
#define INCREMENT 1000
#define NUM_THREADS 1000

CQueue<int> in_queue;
CQueue<int> out_queue;
std::set<int> resultSet;
std::vector<std::thread> threads;

void enqueueDequeueTest(int start, int end);

int main(void) {
  // //Runs tests
  // for (int workload = INITIAL_WORKLOAD; workload <= MAX_WORKLOAD; workload += INCREMENT) {
  //   int workShare = workload / NUM_THREADS;
  //   int start = 1;

  //   //Runs threads, each enqueuing and dequeuing integers for the current test
  //   for (int threadNum = 1; threadNum <= NUM_THREADS; threadNum++) {
  //     //std::cout << "START: " << start << " END: " << end << " Workload: " << workload << std::endl;
  //     threads.push_back(std::thread(enqueueDequeueTest, start, start + workShare));
      
  //     start = start + workShare;
  //   }

  //   //Joins each thread after they finish
  //   for (int threadNum = 0; threadNum < NUM_THREADS; threadNum++) {
  //     threads[threadNum].join();
  //   }

  //   //Places all of the items into a set to verify the number of unique integers
  //   for (int i = 1; i <= workload; i++) {
  //     //std::cout << "Inserting " << i <<"th element into set" << std::endl;
  //     resultSet.insert(out_queue.dequeue());
  //   }

  //   //Displays the size of the set
  //   std::cout << resultSet.size() << std::endl;

  //   //Prints each number in the set
  //   for (auto i = resultSet.begin(); i != resultSet.end(); i++) {
  //     std::cout << *i << std::endl;
  //   }

  //   threads.clear();
  //   resultSet.clear();
  // }

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

void enqueueDequeueTest(int start, int end) {
  for (int i = start; i < end; i++) {
    in_queue.enqueue(i);
  }

  for (int i = start; i < end; i++) {
      out_queue.enqueue(in_queue.dequeue());
  }
}

