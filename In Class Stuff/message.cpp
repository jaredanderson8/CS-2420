#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

template <typename T>
class SafeArray {
public:
  SafeArray(const unsigned int capacity);
  SafeArray(const SafeArray<T>& objToClone);      // copy constructor
  void operator=(const SafeArray<T>& objToCopy);  // copy assignment
  //SafeArray(const SafeArray<T>&& objToClone);      // move constructor
  //void operator=(const SafeArray<T>&& objToCopy);  // move assignment

  ~SafeArray();
  void insert(const unsigned int index, const T& item);
  T get(const unsigned int index) const;
  // C++ has typically 4 ways to pass in data
  // 1) Pass normally, which makes a copy of the data.  That can be fine if you are copying something 8-12 bytes or less
  // 2) Pass in by reference.  C++ takes care of all the compiler magic, and it avoid making a copy of the item
  // 3) Pass in by pointer.  You avoid a copy, but you do incur a small indirection penalty. 
  // 4) Move semantics reference (&&), passes in an R-value so that you can later "move" the item on in without any copies anywhere.
private:

  T* arr{ nullptr };
  unsigned int capacity{ 0 };
};

template <typename T>
SafeArray<T>::SafeArray(const unsigned int capacity) {
  this->capacity = capacity;

  this->arr = new T[capacity];

  // program:          operating system, can you give me sizeof(T) * capacity bytes 
  //                   (such as 4 * 10 for unsigned int = 4 bytes and capacity of 10 bytes)
  // operating system: sure, that's easy.  Done.  Here is the address of the first byte of the first element
  // program:          Thanks!  I'll store that address in a pointer called arr
  // operating system: Ok, remember, this is your memory.  No other program will get that chunk of memory
  //                   Please be kind and ensure you give it back before you are done, don't wait until the program exits
  //                   I do remember that your program has 40 bytes allocated at address, so I will clean it up on program exit if you don't
  // program:          I'll clean it up!  In fact, I'll write the delete[] right now
}

template <typename T>
SafeArray<T>::SafeArray(const SafeArray<T>& objToClone) {
  if (objToClone.capacity > 0 && objToClone.arr) {
    this->capacity = objToClone.capacity;
    this->arr = new T[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
      this->arr[i] = objToClone.arr[i];
    }
  }
}

template <typename T>
void SafeArray<T>::operator=(const SafeArray<T>& objToCopy) {  // copy assignment
  // The "this" object may already have data in it, so clear out the "this" in preparation to clone.
  delete[] this->arr;
  this->arr = nullptr;
  this->capacity = 0;

  if (objToCopy.capacity > 0 && objToCopy.arr) {
    this->capacity = objToCopy.capacity;
    this->arr = new T[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
      this->arr[i] = objToCopy.arr[i];
    }
  }
}

template <typename T>
SafeArray<T>::~SafeArray() {
  delete[] arr;    // program:          Ok operating system, I'm done with this memory at this location
                   // operating system: Yes, you did indeed own 40 bytes at that address, I'll let anyone now use that memory again
}

template <typename T>
void SafeArray<T>::insert(const unsigned int index, const T& item) {
  if (index >= capacity) {
    cout << "The index was out of bounds" << endl;
    return;
  }
  arr[index] = item;
}

template <typename T>
T SafeArray<T>::get(const unsigned int index) const {
  if (index >= capacity) {
    cout << "The index was out of bounds" << endl;
    throw 1;  // C++ lets you throw anything, in this class, I will throw 1.
  }
  return arr[index];
}

template <typename T>
void displayDataAtIndex1(SafeArray<T> obj) {
  cout << "displayDataAtIndex1: " << obj.get(1) << endl;
}

int main() {

  SafeArray<long> mySafeArray(10);
  mySafeArray.insert(0, 13);
  mySafeArray.insert(1, 50);
  mySafeArray.insert(2, 77);
  mySafeArray.insert(10, 666);
  mySafeArray.insert(-1, 666);
  cout << "The data at index 0 is " << mySafeArray.get(0) << endl;
  cout << "The data at index 1 is " << mySafeArray.get(1) << endl;
  cout << "The data at index 2 is " << mySafeArray.get(2) << endl;
  try {
    cout << "The data at index 10 is " << mySafeArray.get(10) << endl;
  }
  catch (int e) {
    cout << "Caught some error: " << e << endl;
  }
  displayDataAtIndex1(mySafeArray);
  displayDataAtIndex1(mySafeArray);

  // copy assignment
  SafeArray<long> cloneOfObject(10);
  
  cloneOfObject = mySafeArray;
  cloneOfObject.operator=(mySafeArray);



  //mySafeArray.update(0, 100);
  //mySafeArray.update(1, 101);
  //mySafeArray[2] = 200;

  //SafeArray<string> myStringArray(5);
  //string bradStory = "It was the best of times, it was the of times...."; // Imagine this goes on for several gigabytes
  //myStringArray.insert(0, bradStory)
  return 0;
}