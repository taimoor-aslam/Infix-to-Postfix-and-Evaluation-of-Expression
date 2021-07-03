
#ifndef Header.h

#define Header

#include<iostream>
#include<math.h>
using namespace std;

class Stack
{
private :
	int top;
	int size;
	char StackArr[30];

public:
	Stack(int);
	int isEmpty();
	int isFull();
	void Push(char);
	char Pop();
	char stackTopValue();
	//void printStack();
};

char* infixToPostfix(char[],int&);
int PostfixExprsnEvaluation(char[],int&);

#endif





