﻿//Copyright 2020, Bradley Peterson, Weber State University, all rights reserved. (11/2020)

#include <cstdio>
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>

using std::thread;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;
using std::mutex;

//*** Prototypes ***
void sortOneVector(vector<unsigned int>& bucket);
void _sortOneVector(vector<unsigned int>& arr, int first, int last);
int _quickSortPartition(vector<unsigned int>& arr, int first, int last);
void printArray(const string& msg);
void printArray2(const string& msg, int arr2[]);
void printAllBuckets(const string& msg);
void pressEnterToContinue();
void step1();
void step2();
void step3();

//***GLOBAL VARIABLES***  (These are global as they will help with an upcoming multithreaded assignment)
unsigned int numBuckets{ 0 };
unsigned int numThreads{ 0 };
const unsigned int UINTMAX = 4294967295;
unsigned int* arr{ nullptr };
unsigned int arrSize{ 0 };
vector<unsigned int>* buckets{ nullptr };
unsigned int currentBucket{ 0 };

bool useMultiThreading{ true }; // To turn off multithreading for any debugging purposes, set this to false.

mutex myMutex;

int passed = 0;
int failed = 0;

//**************************************************My Code*****************************************************************
void bucketSort() 
{
  //cout << "step 1" << endl;
  step1();
  //printAllBuckets("After step 1");

  //step 2
  //cout << "step 2" << endl;
  if(useMultiThreading)
  {
    //create thread tracker objects
    thread* myThreads = new thread[numThreads];
    currentBucket = 0;

    // fork and call step2()
    int i = 0;
    while(i < numThreads)
    {
      myThreads[i] = thread(step2);
      i++;
    }
  
    // join and wait for child threads to die
    i = 0;
    while(i < numThreads)
    {
      myThreads[i].join();
      i++;
    }  

    //clean up the thread tracker objects
    delete[] myThreads;
  }
  else
  {
    step2();
  }
  
  //printAllBuckets("After step 2");

  //cout << "step 3" << endl;
  step3();
}

void step1()
{
  //iterate throught all values in arr
  int i = 0;
  while(i < arrSize)
  {
    // if numbuckets is 1 write to bucket 0, else do following math:
    if(numBuckets == 1)
    {
      //cout << "only one bucket" << endl;
      buckets[0].push_back(arr[i]);
    }
    else
    {
      // do the math outlined earlyier (value) / ((max range)/(num buckets) +1)
      int index = (arr[i]) / ((UINTMAX)/(numBuckets) +1);
      // that gives a bucket index
      // go to that bucket (buckets[index].pushback() )
      buckets[index].push_back(arr[i]);
    }
    i++;
  }
}

void step2()
{
  if(useMultiThreading)
  {
    unsigned int myWorkBucket{ 0 };
    while(true)
    {
      // obtain a number for myworkbucket from currentBucket
      
      //lock the mutex
      myMutex.lock();
      // store currentbucket into my workbucket, and then increment currentbucket
      myWorkBucket = currentBucket;
      currentBucket++;
      //unlock the mutex
      myMutex.unlock();

      //check if this myworkbucket makes sense, is it a valid bucket?
      //if valid bucket, simply sort that bucket
      if(myWorkBucket < numBuckets)
      {
        sortOneVector(buckets[myWorkBucket]);
      }
      else
      {
        break;
      }
    }
  }
  else
  {
    int i = 0;
    while(i < numBuckets)
    {
      sortOneVector(buckets[i]);
      i++;
    }
  }
}

void step3()
{

  // iterate for every bucket
  
  int k = 0;
  if(numBuckets == 1)
  {
    int j = 0;
    while(j < buckets[0].size())
    {
      arr[k] = buckets[0][j];

      j++;
      k++;
    }
  }
  else
  {
    int i = 0;
    while(i < numBuckets)
    {
      //iterate for all values whithin the ith bucket
      int j = 0;
      while(j < buckets[i].size())
      {
        //put the jth value of the ith bucket into the kth element of the output arr
        arr[k] = buckets[i][j];

        j++;
        k++;
      }

      i++;
    }
   
    //printArray("arr: ");

    //cout << " " << endl;

    //printArray2("temp: ", temp);

    // the trickiest part here, 3 indexes!
  }
}

//**************************************************End Of My Code*****************************************************************
  

// The function you want to use.  Just pass in a vector, and this will sort it.
void sortOneVector(vector<unsigned int>& bucket) {
  _sortOneVector(bucket, 0, bucket.size());
}

// A function used by sortOneVector().  You won't call this function.
void _sortOneVector(vector<unsigned int>& bucket, int first, int last) {
  //first is the first index
  //last is the one past the last index (or the size of the array
  //if first is 0)

  if (first < last) {
    //Get this subarray into two other subarrays, one smaller and one bigger
    int pivotLocation = _quickSortPartition(bucket, first, last);
    _sortOneVector(bucket, first, pivotLocation);
    _sortOneVector(bucket, pivotLocation + 1, last);
  }
}

// A function used by sortOneVector().  You won't call this function.
int _quickSortPartition(vector<unsigned int>& arr, int first, int last) {
  unsigned long pivot;
  int index, smallIndex;

  unsigned long temp;

  //Take the middle value as the pivot.
  //swap(first, (first + last) / 2);
  pivot = arr[first];
  smallIndex = first;
  for (index = first + 1; index < last; index++) {
    if (arr[index] < pivot) {
      smallIndex++;
      //swap the two
      temp = arr[smallIndex];
      arr[smallIndex] = arr[index];
      arr[index] = temp;
    }
  }

  //Move pivot into the sorted location
  temp = arr[first];
  arr[first] = arr[smallIndex];
  arr[smallIndex] = temp;

  //Tell where the pivot is
  return smallIndex;

}

// A function to create and load the array with random values.  The tests call this method, you won't call it directly.
void createArray() {
  arr = new unsigned int[arrSize];

  //std::random_device rd;
  //std::mt19937 gen(rd());
  std::mt19937 gen(0);
  std::uniform_int_distribution<unsigned long> dis(0, UINTMAX);

  for (unsigned int i = 0; i < arrSize; i++) {
    arr[i] = dis(gen);
  }
}

// A function to delete the array
void deleteArray() {
  delete[] arr;
}

// Print the array in hexadecimal.  Printing in hex is beneficial for the next function, printAllBuckets()
void printArray(const string& msg) {
  if (arrSize <= 100) {
    printf("%s\n", msg.c_str());
    for (unsigned int i = 0; i < arrSize; i++) {
      printf("%08x ", arr[i]);
    }
    printf("\n");
  }
}

void printArray2(const string& msg, int arr2[]) {
  if (arrSize <= 100) {
    printf("%s\n", msg.c_str());
    for (unsigned int i = 0; i < arrSize; i++) {
      printf("%08x ", arr2[i]);
    }
    printf("\n");
  }
}

// A function to determine how many threads to use on a given machine, depending on its number of cores
unsigned int getNumThreadsToUse() {
  unsigned int numThreadsToUse{ 0 };

  if (useMultiThreading) {
    //Find out how many threads are supported
    unsigned int threadsSupported = std::thread::hardware_concurrency();
    printf("This machine has %d cores.\n", threadsSupported);
    if (threadsSupported == 1 && numBuckets > 1) {
      numThreadsToUse = 2;
    }
    else if (numBuckets < threadsSupported) {
      numThreadsToUse = numBuckets;
    }
    else {
      numThreadsToUse = threadsSupported;
    }
    printf("For the upcoming problem, %d threads will be used\n", numThreadsToUse);
  }
  else {
    numThreadsToUse = 1;
  }
  return numThreadsToUse;
}

// A function to print the array in hexadecimal.  Hex is incredibly useful as an output over base 10/decimal.
// For example, suppose numBuckets = 2.  Then bucket 0 should have all values starting with digit 0-7, and bucket 1 should have all values starting with digit 8-f.
// Also, suppose numBuckets = 4.  Bucket = 0's first digits should be 0-3, bucket 1's first digits should be 4-7, bucket 2's first digits should be 8-b, bucket 3's first digits should be c-f
void printAllBuckets(const string& msg) {

  //Displays the contents of all buckets to the screen.
  if (arrSize <= 100) {
    printf("%s\n", msg.c_str());
    // just uncomment this code when you have arr properly declared as a data member
    printf("******\n");
    for (unsigned int bucketIndex = 0; bucketIndex < numBuckets; bucketIndex++) {
      printf("bucket number %d\n", bucketIndex);
      for (unsigned int elementIndex = 0; elementIndex < buckets[bucketIndex].size(); elementIndex++) {
        printf("%08x ", buckets[bucketIndex][elementIndex]);

      }
      printf("\n");
    }
    printf("\n");
  }
}


// A helper function to verify if the sort is correct.  The test code calls this for you.
void verifySort(unsigned int* arr, unsigned int arraySize, std::chrono::duration<double, std::milli>& diff, const string& sortTest) {
  double val = diff.count();
  for (unsigned int i = 1; i < arraySize; i++) {
    if (arr[i] < arr[i - 1]) {
      printf("------------------------------------------------------\n");
      printf("SORT TEST %s\n", sortTest.c_str());

      if (val != 0.0) {
        printf("Finished bucket sort in %1.16lf milliseconds\n", diff.count());
      }
      printf("ERROR - This list was not sorted correctly.  At index %d is value %08X.  At index %d is value %08X\n", i - 1, arr[i - 1], i, arr[i]);
      printf("------------------------------------------------------\n");

      failed++;
      return;
    }
  }
  printf("------------------------------------------------------\n");
  printf("SORT TEST %s\n", sortTest.c_str());
  if (val != 0.0) {
    printf("Finished bucket sort in %1.16lf milliseconds\n", diff.count());
  }
  printf("PASSED SORT TEST %s - The list was sorted correctly\n", sortTest.c_str());
  printf("------------------------------------------------------\n");

  passed++;
}


void pressEnterToContinue() {
  printf("Press Enter key to continue\n");
  std::cin.get();

}

//Copyright 2020, Bradley Peterson, Weber State University, all rights reserved. (11/2020)

int main() {

  std::chrono::duration<double, std::milli> diff{ 0 };
  double baselineTime{ 9999999.0 };
  double bestMultiThreadedTime{ 9999999.0 };
  int bestMultiThreadedBuckets{ 0 };
  double bestSingleThreadedTime{ 9999999.0 };
  int bestSingleThreadedBuckets{ 0 };


  //Set the listSize, numBuckets, and numThreads global variables.  
  arrSize = 100;

  numBuckets = 2;
  createArray();
  buckets = new vector<unsigned int>[numBuckets];
  numThreads = getNumThreadsToUse();
  printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d, number of cores = %d\n", arrSize, numBuckets, numThreads, std::thread::hardware_concurrency());
  //printf("Displaying the unsorted list array:\n");
  //printArray("test"); //useful for debugging small amounts of numbers.  
  pressEnterToContinue();
  auto start = std::chrono::high_resolution_clock::now();
  bucketSort();
  auto end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  verifySort(arr, arrSize, diff, "2 buckets");
  delete[] buckets;
  deleteArray();
  pressEnterToContinue();

  numBuckets = 4;
  createArray();
  buckets = new vector<unsigned int>[numBuckets];
  numThreads = getNumThreadsToUse();
  printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d, number of cores = %d\n", arrSize, numBuckets, numThreads, std::thread::hardware_concurrency());
  pressEnterToContinue();
  bucketSort();
  verifySort(arr, arrSize, diff, "4 buckets");
  delete[] buckets;
  deleteArray();
  pressEnterToContinue();

  printf("\n\n*** Note, remember to run on performance mode for useful data (for VS, RELEASE instead of DEBUG.  For gcc, /O3 instead of just /g)\n\n");
  pressEnterToContinue();

  arrSize = 4000000;
  numBuckets = 1;
  createArray();
  numThreads = getNumThreadsToUse();
  buckets = new vector<unsigned int>[numBuckets];
  printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d, number of cores = %d\n", arrSize, numBuckets, numThreads, std::thread::hardware_concurrency());
  start = std::chrono::high_resolution_clock::now();
  bucketSort();
  end = std::chrono::high_resolution_clock::now();
  diff = end - start;
  baselineTime = diff.count();
  verifySort(arr, arrSize, diff, "4000000 items in 1 bucket with 1 thread - BASELINE");
  delete[] buckets;
  deleteArray();

  for (int mode = 0; mode < 2; mode++) {

    useMultiThreading = (bool)mode; // Run all tests without multithreading, then run all with multithreading.  

    for (numBuckets = 2; numBuckets <= 1024; numBuckets *= 2) {
      arrSize = 4000000;
      createArray();
      numThreads = getNumThreadsToUse();
      buckets = new vector<unsigned int>[numBuckets];
      printf("\nStarting bucket sort for listSize = %d, numBuckets = %d, numThreads = %d, number of cores = %d\n", arrSize, numBuckets, numThreads, std::thread::hardware_concurrency());
      start = std::chrono::high_resolution_clock::now();
      bucketSort();
      end = std::chrono::high_resolution_clock::now();
      diff = end - start;
      if (useMultiThreading && (diff.count() < bestMultiThreadedTime)) {
        bestMultiThreadedTime = diff.count();
        bestMultiThreadedBuckets = numBuckets;
      }
      else if (!useMultiThreading && (diff.count() < bestSingleThreadedTime)) {
        bestSingleThreadedTime = diff.count();
        bestSingleThreadedBuckets = numBuckets;
      }
      stringstream ss;
      ss << arrSize << " items in " << numBuckets << " buckets";
      verifySort(arr, arrSize, diff, ss.str());
      delete[] buckets;
      deleteArray();
    }
  }

  printf("\n-----------------------------------------------------------\n");
  printf("              FINAL RESULTS                      \n");
  printf("The baseline (quicksort on 1 thread/1 bucket):  completed in %g ms\n", baselineTime);
  printf("The best singlethreaded result:     %d buckets completed in %g ms\n", bestSingleThreadedBuckets, bestSingleThreadedTime);
  if (useMultiThreading) {
    printf("The best multithreaded result:      %d buckets completed in %g ms\n", bestMultiThreadedBuckets, bestMultiThreadedTime);
  }
  printf("\n-----------------------------------------------------------\n");

  cout << "Tests passed: " << passed << endl;
  cout << "Tests failed: " << failed << endl;

  pressEnterToContinue();
  return 0;
}

