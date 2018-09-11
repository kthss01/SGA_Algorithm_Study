#include <iostream>
#include <assert.h>
using namespace std;

#define MAX_VALUES 3

template<typename T> class Stack
{
public:
	Stack() : top(-1)
	{
		memset(values, 0, sizeof(T) * MAX_VALUES);
	}

	void Push(T val)
	{
		assert(top + 1 < MAX_VALUES);

		values[++top] = val;
	}

	T Pop()
	{
		// 릴리즈 모드일때를 대비해 assert 안에 Empty 넣으면 안됨 
		bool bCheck = Empty();
		assert(bCheck == false);
		
		T val = values[top];
		values[top--] = 0;

		return val;
	}

	T Top()
	{
		return values[top];
	}

	bool Empty()
	{
		//if (top < 0)
		//	return true;
		//
		//return false;

		// 삼항 연산자
		return top < 0 ? true : false;
	}

private:
	int top; // top of pointer 꼭대기 가리키는거 크기 넘어가면 오버플로 -1보다 아래면 언더플로

	T values[MAX_VALUES];
};

void main()
{
	Stack<int>* stack = new Stack<int>();
	stack->Push(10);
	stack->Push(5);
	stack->Push(6);
	//stack->Push(8); // assert 뜸

	cout << stack->Pop() << " ";
	cout << stack->Pop() << " ";
	cout << stack->Pop() << " ";
	//cout << stack->Pop() << " ";

	delete stack;

	cout << endl;

	///////////////////////////////////////////////////////////////////////////

	Stack<char>* stack2 = new Stack<char>();
	stack2->Push('A');
	stack2->Push('B');
	stack2->Push('C');
	//stack2->Push(8); // assert 뜸

	cout << stack2->Pop() << " ";
	cout << stack2->Pop() << " ";
	cout << stack2->Pop() << " ";
	//cout << stack2->Pop() << " ";

	delete stack2;
}