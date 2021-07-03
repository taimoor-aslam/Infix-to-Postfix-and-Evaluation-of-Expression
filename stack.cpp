#include"stack.h"
#include <iostream>

Stack::	Stack(int length)
{
	top=-1;
	size=length;
}


int Stack::	isEmpty()
{
	if(top==-1)
	{
		return 1;
	}
	return 0;
}
int Stack:: isFull()
{
	if(top==size-1)
	{
		return 1;
	}
	return 0;
}
void Stack:: Push(char val)
{
	if(!isFull())
    {
		top++;
		StackArr[top]=val;
	}
	else
	{
		cout<<"Stack is full"<<endl;
	}
}
	
char Stack:: stackTopValue()
{
	return StackArr[top];
}
char Stack:: Pop()
{
	char val;
	if(!isEmpty())
	{
		val=StackArr[top];
		top--;
		return val;
	}
	else
	{
		return '0';
	}
}
	
int OperatonToBeApply(int num1,int num2, char op)
{
	int total=0;
	switch(op)
	{
	    case '+':
		{
			total=num1+num2;
			break;
		}
		case '-':
		{
			total=num1-num2;
			break;
		}
		case '*':
		{
			total=num1*num2;
			break;
		}
		case '/':
		{
			total=num1/num2;
			break;
		}
		case '^':
		{
			total=pow(float(num1),num2);
			break;
		}
    }
	return total;
}

bool isOperator(char val)
{
	int asciiVal=int(val);
	if((asciiVal==47)||(asciiVal==45)||(asciiVal==42)||(asciiVal==43)||(asciiVal==94))
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*
bool IsGreaterInPrecedence(char a, char b)
{
    if((a==b)||((a=='+')&&(b=='-'))||((a=='-')&&(b=='+')))
	{
		return true;
	}
	else if(((a=='*')&&((b=='/')||(b=='^')))||((a=='/')&&((b=='*')||(b=='^'))))
	{
		return true;
	}
	else if(((a=='*')||(a=='/')||(a=='^'))&&((b=='+')||(b=='-')))
	{
		return false;
	}
	else if((a=='^')&&((b=='*')||(b=='/')))
	{
		return false;
	}
	else if((a=='+'||a=='-')&&(b=='*'||b=='/'||b=='^'))
	{
        return true;
	}
	else if(b=='(')        
	{
		return false;
	}
	return false;
}*/
int PrecedenceCheck(char op)
{
	switch(op)
	{
	    case'+':case '-':
		{
			return 1;
		    break;
	    }
	    case '*': case '/': case '^': 
	    {
		    return 2;
		    break;
	    }
	    case ')':
		{
			return 3;
			break;
		}
	    default:
		{
		     return 0;
		}                               //  A+(B*C-D/E)^(F-G)
	}
	return 0;
}
char* infixToPostfix(char exprsn[40],int& count)                 //3+(4-2^3-(6-3*2)+8
{
	char *OutputExprsn,stackTopVal;   int i=0,j=0,length=0;
    
	length=strlen(exprsn);
	OutputExprsn=new char[length];
	
	Stack obj(length);

	do 
	{
		if(isalpha(exprsn[i]))
		{
			count++;
			OutputExprsn[j]=exprsn[i];
			j++;
		}
		if(isdigit(exprsn[i]))
		{
            OutputExprsn[j]=exprsn[i];
			j++;
		}

		
		else if(exprsn[i]=='(')            //A+(B*C-D/E)^(F-G)
		{ 
			obj.Push('(');
		}
		else if(isOperator(exprsn[i]))
		{
			if(!obj.isEmpty())
			{
				stackTopVal=obj.stackTopValue(); 
				while(PrecedenceCheck(exprsn[i])<=PrecedenceCheck(stackTopVal))
				{
					 stackTopVal=obj.Pop();
					 OutputExprsn[j]=stackTopVal;
					 j++;
					 stackTopVal=obj.stackTopValue();
				 }
				 obj.Push(exprsn[i]);
			}
			else
			{
				obj.Push(exprsn[i]);
			}
		}
		/*else if(isOperator(exprsn[i]))
		{
			if(!obj.isEmpty())
			 {
				 stackTopVal=obj.stackTopValue();    
				
				 while(IsGreaterInPrecedence(exprsn[i],stackTopVal))
			     {
			         stackTopVal=obj.Pop();
					 OutputExprsn[j]=stackTopVal;
					 j++;
					 stackTopVal=obj.stackTopValue();
				 }
				 obj.Push(exprsn[i]);
			 }
		     else
		     {
			     obj.Push(exprsn[i]);
		     }
		}*/
		else if(exprsn[i]==')')
		{
			stackTopVal=obj.stackTopValue();
			
			while(stackTopVal!='(')
			{
				OutputExprsn[j]=obj.Pop();
				j++;
				stackTopVal=obj.stackTopValue();
			}
			stackTopVal=obj.Pop();
		}
		if(i==length-1)
		{
			
			while(!obj.isEmpty())
	        {
			   if(obj.stackTopValue()=='('||obj.stackTopValue()==')')
		        {
			        obj.Pop();
		        }
		        else
		        {
					OutputExprsn[j]=obj.Pop();
		            j++;
		        }
	        }
		}
		i++;
	}
	while(exprsn[i]!='\0');
	
	OutputExprsn[j]='\0';
   return OutputExprsn;
}

int PostfixExprsnEvaluation(char exprsn[],int& count)
{
	char num1,num2;     int total=0;

	Stack Object(strlen(exprsn));              // 436+7-423^*-+
	
	for(int i=0;exprsn[i]!='\0';i++)
	{
		if(isalpha(exprsn[i]))
		{
			i++;
		}
		if(isdigit(exprsn[i]))
		{
			Object.Push(exprsn[i]);
		}
		if((isOperator(exprsn[i]))&&(count==0))
		{
			num2=int(Object.Pop())-48;
			num1=int(Object.Pop())-48;

            total=OperatonToBeApply(num1,num2,exprsn[i]);
			Object.Push(total+48);
		}
	}
	
	return total;
}
