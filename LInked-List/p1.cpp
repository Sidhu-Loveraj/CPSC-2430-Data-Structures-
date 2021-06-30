/*
 * File: p1.cpp
 * Author: Loveraj Sidhu
 *
 * Driver file
*/

#include <iostream>
#include "Stack.h"

using namespace std;

  int main(){
    Stack primes;
    cout << "Looking to add prime integers from numbers 1-75." << endl;
    cout << "Only prime integers will be pushed to the stack." << endl;
    for (int i = 1; i <= 75; i++)
    {
      primes.Push(i);
    }

    cout << "Top of the Stack: " << primes.Peek() << endl;
    cout << "Making a copy of the Stack \n" << endl;
    Stack copy = primes;
    cout << "The top of a new Stack is: " << copy.Peek() << endl;
    cout << endl << "Prime integers in our Stack:" << endl;
    while(!primes.empty())
    {
      cout << "Prime Integer: " << primes.Peek() << endl;
      primes.Pop();
    }
  }
