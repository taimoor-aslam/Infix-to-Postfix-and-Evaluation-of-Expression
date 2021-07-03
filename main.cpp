#include"stack.h"
#include <iostream>
using namespace std;
int main()
{
	
    char exprsn[40],*OutputExprsn;   int count=0,total;
	
	cout<<"Enter an infix expression"<<endl;
    cin.getline(exprsn,40);

	OutputExprsn=infixToPostfix(exprsn,count);
	cout<<"\n After converting to postfix notation expression will be"<<endl;
	cout<<OutputExprsn<<endl;

	total=PostfixExprsnEvaluation(exprsn,count);
	if(count==0)
	{
	     cout<<"Result is "<<total<<endl;
	}
	system("pause");
}