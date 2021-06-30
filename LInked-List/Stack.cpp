/*
 * File: Stack.cpp
 * Author: Loveraj Sidhu
 *
 *
*/

#include "Stack.h"

  // calling constructor
  Stack::Stack(){
    capacity = 5;
    data = new int[maximum];
    size = 0;
  }
  //
  Stack::Stack(const Stack &s){
    maximum = s.maximum;
    data = new int[maximum];
    size = s.size;
    for(int i = 0; i < size; i++)
    {
      data[i] = s.data[i];
    }
  }
  //
  Stack& Stack::operator = (const Stack &s){
    if(this != &s)
    {
      delete []data;
      maximum = s.maximum;
      data = new int[maximum];
      size = s.size;
      for(int i = 0; i < size; i++)
      {
        data[i] = s.data[i];
      }
      return *this;
    }
    // calling our deconstructor
    Stack::~Stack(){
      delete []data;
    }
    // isPrime function to make sure data entered is a prime number
    bool Stack::isPrime(int x){
      for(int i = 2; i < x; i++)
      {
        if(x % i == 0)
        return false;
      }
      return true;
    }
    //
    void Stack::resize(in newMax){
      maximum = newMax;
      int *temp = new int[maximum];
      for(int i = 0; i < size; i++)
      {
        temp[i] = data[i];
        delete []data;
        data = temp;
      }
    }
    //
    void Stack::Push(int x){
      if(isPrime(x))
      {
        if(size == maximum)
          resize(1.5 * maximum);
          data[size++] = x;
      }
    }
    //
    void Stack::Pop(){
      if(size > 0)
      size--;
    }
    //
    int Stack::Peek(){
      if(size > 0)
      return data[size-1];
      else
      return 0;
    }
    //
    bool Stack::empty(){
      return size == 0;
    }

  }
