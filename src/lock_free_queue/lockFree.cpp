#include "lockFreeQueue.h"
#include <iostream>
#include <thread>
#include <set>
#include <vector>
#include <chrono>
#include <fstream>

#define MAX_WORKLOAD 500000
#define INITIAL_WORKLOAD 1000
#define INCREMENT 1000
#define NUM_THREADS 1000

CQueue<int> in_queue;
CQueue<int> out_queue;
std::set<int> resultSet;
std::vector<std::thread> threads;

void enqueueDequeueTest(int start, int end);

int main(void) {
  for (int run = 1; run <= 5; run++) {
    std::string fileName = "../data/lockfree" + std::to_string(run) + ".csv";
    std::ofstream outputFile(fileName);
    //Runs tests
    for (int workload = INITIAL_WORKLOAD; workload <= MAX_WORKLOAD; workload += INCREMENT) {
      int workShare = workload / NUM_THREADS;
      int start = 1;

      auto startTime = std::chrono::high_resolution_clock::now();

      //Runs threads, each enqueuing and dequeuing integers for the current test
      for (int threadNum = 1; threadNum <= NUM_THREADS; threadNum++) {
        //std::cout << "START: " << start << " END: " << end << " Workload: " << workload << std::endl;
        threads.push_back(std::thread(enqueueDequeueTest, start, start + workShare));
        
        start = start + workShare;
      }

      //Joins each thread after they finish
      for (int threadNum = 0; threadNum < NUM_THREADS; threadNum++) {
        threads[threadNum].join();
      }

      auto stopTime = std::chrono::high_resolution_clock::now(); 

      // //Places all of the items into a set to verify the number of unique integers
      for (int i = 1; i <= workload; i++) {
        resultSet.insert(out_queue.dequeue());
      }


      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);

      //Displays the size of the set
      outputFile << resultSet.size() << ", " << duration.count() << std::endl;
      std::cout << resultSet.size() << " - " << duration.count() << "ms" << std::endl;



      threads.clear();
      resultSet.clear();
    }
  }
}

void enqueueDequeueTest(int start, int end) {
  for (int i = start; i < end; i++) {
    in_queue.enqueue(i);
  }

  for (int i = start; i < end; i++) {
      try {
        out_queue.enqueue(in_queue.dequeue());
      } catch (std::exception& e) {
        i--;
      }
  }
}

