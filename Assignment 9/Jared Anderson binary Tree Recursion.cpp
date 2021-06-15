// Copyright 2020, Bradley Peterson, Weber State University, all rights reserved. (11/2020)

#include <iostream>
#include <string>
#include <array>

using std::endl;
using std::cout;
using std::cin;
using std::string;

template <typename T>
struct Node 
{
  T data{};
  Node<T>* llink{ nullptr };
  Node<T>* rlink{ nullptr };
};

template <typename T>
class Tree 
{
  public:
    Tree();
    ~Tree();
    void insert(const T& item);
    void inOrder();
    string getInOrder();

    // TODO: Implement methods for nodeCount, leavesCount, singleChildCount, and levelCount
    int nodeCount();
    int leavesCount();
    int singleChildCount();
    int levelCount(int lvl);

    void runCustomLambda(void (myLambda)(int& value));

  private:
    void clear(Node<T>* ptr);
    void inOrder(Node<T>* ptr, int lvl);
    void runCustomLambda(Node<T>* ptr, void (myLambda)(int& value));

    Node<T>* root{ nullptr };
    string values;

    int nodes = 0;
    int leaves = 0;
    int oneChild = 0;
    int onLevel = 0;
    int level = 0;
};

template <typename T>
Tree<T>::Tree()
{
  inOrder();
}

template <typename T>
Tree<T>::~Tree() 
{
  clear(root);
}

template <typename T>
void Tree<T>::insert(const T& item) 
{
  Node<T>* newNode = new Node<T>();
  newNode->data = item;

  if (!root) 
  {
    root = std::move(newNode);
  }
  else 
  {
    Node<T>* curr = root;
    while (true) 
    {
      if (item < curr->data) 
      {
        if (curr->llink) 
        {
          curr = curr->llink; //go left
        }
        else 
        {
          //nothing on the left, add it in
          curr->llink = std::move(newNode);
          return;
        }
      }
      else 
      {
        if (curr->rlink) 
        {
          curr = curr->rlink;
        }
        else 
        {
          curr->rlink = std::move(newNode);
          return;
        }
      }
    }
  }
}

template <typename T>
void Tree<T>::inOrder() 
{
  nodes = 0;
  leaves = 0;
  oneChild = 0;
  onLevel = 0;
  
  inOrder(root, 1);
  //cout << values << endl;
}

template <typename T>
void Tree<T>::inOrder(Node<T>* ptr, int lvl) 
{
  if (ptr) 
  {
    if(lvl == level)
    {
      onLevel++;
    }

    inOrder(ptr->llink, lvl+1);          // Go left
    values = values + " ";
    values = values + std::to_string(ptr->data);

    nodes++;
    if(!ptr->llink && !ptr->rlink)
    {
      leaves++;
    }
    else if((!ptr->llink && ptr->rlink) || (ptr->llink && !ptr->rlink))
    {
      oneChild++;;
    }

    inOrder(ptr->rlink, lvl+1);          // Go right
  }
}

template <typename T>
string Tree<T>::getInOrder() 
{
  values = "";
  inOrder();
  return values;
}

template <typename T>
int Tree<T>::nodeCount()
{
  inOrder();
  return nodes;
}

template <typename T>
int Tree<T>::leavesCount()
{
  inOrder();
  return leaves;
}

template <typename T>
int Tree<T>::singleChildCount()
{
  inOrder();
  return oneChild;
}

template <typename T>
int Tree<T>::levelCount(int lvl)
{
  if(lvl < 1)
  {
    cout << "There is no level: " << lvl << endl;
    return 0;
  }

  level = lvl;
  inOrder();
  return onLevel;
}

// TODO: Call the private lambda, passing in 2 arguments: 1) the root pointer and 2) the myLambda
template <typename T>
void Tree<T>::runCustomLambda(void (myLambda)(int& value)) 
{
  runCustomLambda(root, myLambda);
}

// TODO: Perform a tree traversal.  
// For the action, call the lambda and pass in the node's data into it.
// For the traversal, pass in 2 arguments: 1) the node's left or right pointer and 2) the myLambda
template <typename T>
void Tree<T>::runCustomLambda(Node<T>* ptr, void (myLambda)(int& value)) 
{
  if (ptr) 
  {
    myLambda(ptr->data);
    runCustomLambda(ptr->llink, myLambda);          // Go left    
    runCustomLambda(ptr->rlink, myLambda);          // Go right
  }
}

template <typename T>
void Tree<T>::clear(Node<T>* ptr) 
{
  if (ptr) 
  {
    clear(ptr->llink);         // Go left
    clear(ptr->rlink);         // Go right
    delete ptr;
  }
}

void pressAnyKeyToContinue() 
{
  printf("Press any key to continue\n");
  cin;
}

//This helps with testing, do not modify.
template <typename T>
bool checkTest(string testName, T whatItShouldBe, T whatItIs) {

  if (whatItShouldBe == whatItIs) 
  {
    cout << "Passed " << testName << endl;
    return true;
  }
  else 
  {
    cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    return false;
  }
}

int main() {

  Tree<int> myTree;

  myTree.insert(37);
  myTree.insert(32);
  myTree.insert(73);
  myTree.insert(95);
  myTree.insert(42);
  myTree.insert(12);
  myTree.insert(00);
  myTree.insert(49);
  myTree.insert(98);
  myTree.insert(7);
  myTree.insert(27);
  myTree.insert(17);
  myTree.insert(47);
  myTree.insert(87);
  myTree.insert(77);
  myTree.insert(97);
  myTree.insert(67);
  myTree.insert(85);
  myTree.insert(15);
  myTree.insert(5);
  myTree.insert(35);
  myTree.insert(55);
  myTree.insert(65);
  myTree.insert(75);
  myTree.insert(25);
  myTree.insert(45);
  myTree.insert(3);
  myTree.insert(93);
  myTree.insert(83);
  myTree.insert(53);
  myTree.insert(63);
  myTree.insert(23);
  myTree.insert(13);
  myTree.insert(43);
  myTree.insert(33);
  checkTest<int>("Test #1, number of nodes", 35, myTree.nodeCount());
  checkTest<int>("Test #2, number of leaves, (i.e. nodes with no children)", 11, myTree.leavesCount());
  checkTest<int>("Test #3, number of nodes with one child", 14, myTree.singleChildCount());
  checkTest<int>("Test #4, number of nodes on level 1 (the root level)", 1, myTree.levelCount(1));
  checkTest<int>("Test #5, number of nodes on level 2", 2, myTree.levelCount(2));
  checkTest<int>("Test #6, number of nodes on level 3", 4, myTree.levelCount(3));
  checkTest<int>("Test #7, number of nodes on level 4", 6, myTree.levelCount(4));
  checkTest<int>("Test #8, number of nodes on level 5", 7, myTree.levelCount(5));
  checkTest<int>("Test #9, number of nodes on level 6", 7, myTree.levelCount(6));
  checkTest<int>("Test #11, number of nodes on level 8", 1, myTree.levelCount(8));
  checkTest<int>("Test #10, number of nodes on level 7", 7, myTree.levelCount(7));
  checkTest<int>("Test #12, number of nodes on level 9", 0, myTree.levelCount(9));

  // TODO: complete the lambda
  myTree.runCustomLambda([](int& value){value = value *2;});
  checkTest<string>("Test #13, lambda to doubled values", " 0 6 10 14 24 26 30 34 46 50 54 64 66 70 74 84 86 90 94 98 106 110 126 130 134 146 150 154 166 170 174 186 190 194 196", myTree.getInOrder());


  pressAnyKeyToContinue();
  return 0;
}