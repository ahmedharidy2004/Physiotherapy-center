//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"

 //Unless spesificed by the stack user, the default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{
	enum { MAX_SIZE = 1000 };
private:
	T items[MAX_SIZE];		// Array of stack items
	int top;                   // Index to top of stack
	int count;
public:

	ArrayStack()
	{
		top = -1;
		count = 0;
	}  // end default constructor

	void PrintStack()const
	{
		int co = top;
		while (co >= 0)
		{
			cout << *items[co];
			if (co != 0)
			{
				cout << ", ";
			}
			co--;
		}
		cout << endl;
	}
	int GetCount()const
	{
		return count;
	}
	bool isEmpty() const
	{
		return top == -1;
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if (top == MAX_SIZE - 1) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;
		count++;
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		count--;
		return true;
	}  // end pop

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  // end peek

}; // end ArrayStack

#endif
