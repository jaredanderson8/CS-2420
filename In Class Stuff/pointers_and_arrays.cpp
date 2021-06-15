#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;


int main() {
  cout << "How large should this multiplication table be: ";
  int size;
  cin >> size;

  //int arr[size][size];  // Stack array, nothing dynamic about it
                       // Stack arrays or fixed sized arrays must be known at compile time!
                       // We need a dynamic array

  int* arr{ nullptr };  // What will the value of arr be after this line?

  arr = new int[size * size]; // This creates an array in heap, but NOTHING in this program knows about it.


  //// How do I write elements into this array?
  ////*arr = 42;
  //arr[0] = 42;

  ////++arr;  // pointer arithmetic
  ////*arr = 43;
  //
  ////*(arr + 1) = 43; 
  //arr[1] = 43;  

  ////++arr;
  ////*arr = 100;
  //
  ////*(arr + 2) = 100;
  //arr[2] = 100;

  ////*(arr - 1) = 666;
  //arr[-1] = 666;




  for (int i = 0; i < size; i++) {  // rows
    for (int j = 0; j < size; j++) { // columns
      arr[i*size + j] = (i+1) * (j+1);
    }
  }
  // Display it!
  
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << std::setw(4);
      cout << arr[i*size + j] << " ";      
    }
    cout << endl;
  }

  // If you used new to create an array, you MUST use delete[] with the square brackets!
  delete[] arr;
  arr = nullptr;

  return 0;
}