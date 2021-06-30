// Loveraj Sidhu
// heap.h
// min heap class

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

class Heap
{
 public:
   Heap();
   Heap(Heap& toCopy);
   Heap& operator=(Heap& toCopy);
   ~Heap();      
   void insert(int k);
   bool remove(int& orig, int& reset);
   bool resetPriority(int orig);
   bool isEmpty();
   bool isFull();
 private:
   struct Node {
      int opriority;
      int rpriority; 
   };
   void grow();
   void percDown(int hole);
   Node* arr;
   int size;
   int arrsize;
};

#endif