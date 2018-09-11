#include <iostream>
#include <assert.h>
using namespace std;

#define MAX_VALUES 5

template<typename T> class Queue
{
public:
	Queue() : front(-1), rear(-1)
	{
		memset(values, 0, sizeof(T) * MAX_VALUES);
	}

	bool IsEmpty()
	{
		return front == rear ? true : false;
	}

	bool IsFull()
	{
		// rear가 증가해서 rear 랑 체크한 거
		return rear == MAX_VALUES - 1 ? true : false;
	}

	void Enqueue(T val)
	{
		bool bCheck = IsFull();
		assert(bCheck == false);

		values[++rear] = val;
	}

	T Dequeue()
	{
		bool bCheck = IsEmpty();
		assert(bCheck == false);

		return values[++front];
	}

private:
	int front, rear;

	T values[MAX_VALUES];
};

void main()
{
	Queue<int>* q = new Queue<int>();
	q->Enqueue(10);
	q->Enqueue(20);
	q->Enqueue(30);

	cout << q->Dequeue() << " ";
	cout << q->Dequeue() << " ";
	cout << q->Dequeue() << " ";

	delete q;
}