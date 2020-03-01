#include "lockFreeQueue.h"
#include <iostream>
#include <thread>
#include <set>
#include <vector>
#include <fstream>

//Max number of items to enqueue/dequeue
#define MAX_WORKLOAD 500000
//Initial number of items to enqueue/dequeue
#define INITIAL_WORKLOAD 1000
//Number of items to add for each test
#define INCREMENT 1000
//Number of threads enqueuing/dequeuing
#define NUM_THREADS 1000

//Queue which the threads enqueue to and dequeue from
CQueue<int> in_queue;

//Queue which final values are enqueued to for correctness checking
CQueue<int> out_queue;

//Set used to verify that all values are present and unique
std::set<int> resultSet;

//Vector to store the spawned threads
std::vector<std::thread> threads;

//Function which each threads runs as part of the benchmark
void enqueueDequeueTest(int start, int end);

//Runs benchmark for CQueue implementation
int main(void) {
  //Runs 5 repeat readings
  for (int run = 1; run <= 5; run++) {
    //Names and creates file to write results of current test run to
    std::string fileName = "../data/lockfree" + std::to_string(run) + ".csv";
    std::ofstream outputFile(fileName);
    
    //Runs series of tests, starting at 1000 items to enqueue/dequeue and ending with 500,000
    for (int workload = INITIAL_WORKLOAD; workload <= MAX_WORKLOAD; workload += INCREMENT) {
      //Allocates a share of the work (data items) to each thread
      int workShare = workload / NUM_THREADS;
      //Marks the first item to enqueue/dequeue
      int start = 1;

      //Records start time of current test
      auto startTime = std::chrono::high_resolution_clock::now();

      //Creates and runs threads, each enqueuing and dequeuing integers for the current test
      for (int threadNum = 1; threadNum <= NUM_THREADS; threadNum++) {
        //Threads are spawned and allocated their share of the work
        threads.push_back(std::thread(enqueueDequeueTest, start, start + workShare));
        
        //Calculates next share of work to assign to a thread
        start = start + workShare;
      }

      //Joins threads after they finish
      for (int threadNum = 0; threadNum < NUM_THREADS; threadNum++) {
        threads[threadNum].join();
      }

      //Records end time of current test
      auto stopTime = std::chrono::high_resolution_clock::now(); 

      //Calculates the duration of the current test
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime);

      //Places all of the items into a set to ensure the correct integers were preserved during the test
      for (int i = 1; i <= workload; i++) {
        resultSet.insert(out_queue.dequeue());
      }

      //Writes size of set (for correctness and to indicate the current test) 
      //and time taken to run that test both to file and to stdout
      outputFile << resultSet.size() << ", " << duration.count() << std::endl;
      std::cout << resultSet.size() << " - " << duration.count() << "ms" << std::endl;

      //Clears list of threads and resultSet to ensure all tests are carried out from the same point
      threads.clear();
      resultSet.clear();
    }
  }
}

/**
 * Enqueue and dequeue test for threads to run
 * @start - first integer thread should enqueue
 * @end - integer thread should stop enqueuing at
 */
void enqueueDequeueTest(int start, int end) {
  //Enqueues the integers from start to end - 1 to in_queue
  for (int i = start; i < end; i++) {
    in_queue.enqueue(i);
  }

  //Dequeues the same number of integers from in_queue that
  //the thread enqueued, and enqueues them to the out_queue
  //for later verification of correctness
  for (int i = start; i < end; i++) {
      //Tries to dequeue an item from in_queue
        //and enqueue it to out_queue
      try {
        out_queue.enqueue(in_queue.dequeue());

      //If the queue is currently empty, the thread
      //decrements i (so that it will try to dequeue again)
      } catch (std::exception& e) {
        i--;
      }
  }
}