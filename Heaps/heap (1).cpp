// Loveraj Sidhu
// heap.cpp
// implementation for heap class

#include "heap.h"
#include <iostream>

using namespace std;

Heap::Heap() 
{
    arrsize = 10;
    size = 0;
    arr = new Node[arrsize];
}

Heap::Heap(Heap& toCopy)
{
    size = toCopy.size;
    arrsize = toCopy.arrsize;
    arr = new Node[arrsize];
    for (int i = 1; i <= size; i++) {
        arr[i] = toCopy.arr[i];
    }
}

Heap& Heap::operator=(Heap& toCopy)
{
    if (arr != toCopy.arr) {
        size = toCopy.size;
        arrsize = toCopy.arrsize;
        Node* newarr;
        newarr = new Node[arrsize];
        for (int i = 1; i <= size; i++) {
            newarr[i] = toCopy.arr[i];
        }
        delete arr;
        arr = newarr;
    }
    return *this;
}

Heap::~Heap()
{
    delete arr;
} 

void Heap::insert(int k)
{
    int hole = ++size;
    if (isFull()) {
        grow();
    }
    while (hole > 1 && k < arr[hole/2].opriority) {
        arr[hole] = arr[hole/2];
        hole = hole/2;
    }
    Node newNode;
    newNode.opriority = k;
    newNode.rpriority = k;
    arr[hole] = newNode;
}

bool Heap::remove(int& orig, int& reset)
{
    if (isEmpty()) {
        return false;
    }
    else {
        orig = arr[1].opriority;
        reset = arr[1].rpriority;
        arr[1] = arr[size];
        size--;
        percDown(1);
        return true;
    }

}

bool Heap::resetPriority(int orig)
{
    int index = 1;
    Node temp;
    while (index < size && orig != arr[index].opriority) {
        index++;
    }
    if (orig != arr[index].opriority) {
        return false;
    }
    else {
        arr[index].rpriority = 1;
        temp = arr[index];
        while (index > 1) {
            arr[index] = arr[index/2];
            index /= 2;
        }   
        arr[1] = temp;
        return true;
    }
}

bool Heap::isEmpty() 
{
    return (size == 0);
}

bool Heap::isFull()
{
    return (size >= arrsize-1);
}

void Heap::grow() 
{
    arrsize *= 1.5;
    Node* newarr;
    newarr = new Node[arrsize];
    for (int i = 0; i < size; i++) {
        newarr[i] = arr[i];
    }
    delete arr;
    arr = newarr;
}

void Heap::percDown(int hole) 
{
    int temp = arr[hole].rpriority;
    while ((hole*2 <= size && temp > arr[hole*2].rpriority)
    || (hole*2 + 1 <= size && temp > arr[hole*2 + 1].rpriority)) {
        if (hole*2 + 1 <= size 
        && arr[hole*2 + 1].rpriority < arr[hole*2].rpriority) {
            arr[hole] = arr[hole*2 + 1];
            hole = hole*2 + 1;
        }
        else {
            arr[hole] = arr[hole*2];
            hole = hole*2;
        }
    } 
    Node newNode;
    newNode.opriority = temp;
    newNode.rpriority = temp;
    arr[hole] = newNode;
}