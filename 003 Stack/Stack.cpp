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
		// ������ ����϶��� ����� assert �ȿ� Empty ������ �ȵ� 
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

		// ���� ������
		return top < 0 ? true : false;
	}

private:
	int top; // top of pointer ����� ����Ű�°� ũ�� �Ѿ�� �����÷� -1���� �Ʒ��� ����÷�

	T values[MAX_VALUES];
};

void main()
{
	Stack<int>* stack = new Stack<int>();
	stack->Push(10);
	stack->Push(5);
	stack->Push(6);
	//stack->Push(8); // assert ��

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
	//stack2->Push(8); // assert ��

	cout << stack2->Pop() << " ";
	cout << stack2->Pop() << " ";
	cout << stack2->Pop() << " ";
	//cout << stack2->Pop() << " ";

	delete stack2;
}