/*
 * File: Stack.h
 * Author: Loveraj Sidhu
 *
 *
*/

#ifndef STACK_H
#define STACK_H

  // Stack only holds prime numbers
  class Stack {
  private:
    int *data;
    int size;
    int maximum;
    bool isPrime(int x);
    void resize(int newMax);

  public:
    // constructor
    Stack();
    Stack(const Stack &s);
    // Overload Assignment Operator
    Stack& operator = (const Stack &s);
    // deconstructor
    ~Stack();
    // Push fucntion to add in number to stack
    void Push(int n);
    // Pop function to remove numbers from stack
    void Pop();
    // Peek function
    int Peek();
    bool empty();

  };

#endif /*STACK_H*/
