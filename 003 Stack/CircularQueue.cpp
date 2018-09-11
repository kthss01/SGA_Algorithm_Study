#include <iostream>
#include <assert.h>
using namespace std;

#define MAX_VALUES 5

template<typename T> class CircularQueue
{
public:
	CircularQueue() : front(0), rear(0)
	{
		memset(values, 0, sizeof(T) * MAX_VALUES);
	}

	bool IsEmpty()
	{
		return front == rear;
	}

	bool IsFull()
	{
		// rear가 증가해서 rear 랑 체크한 거
		return front == (rear + 1) % MAX_VALUES;
	}

	void Enqueue(T val)
	{
		bool bCheck = IsFull();
		assert(bCheck == false);

		rear = (++rear) % MAX_VALUES;
		values[rear] = val;
	}

	T Dequeue()
	{
		bool bCheck = IsEmpty();
		assert(bCheck == false);

		int index = front;
		front = (++front) % MAX_VALUES;

		return values[front];
	}

private:
	int front, rear;

	T values[MAX_VALUES];
};

void main()
{
	CircularQueue<int>* q = new CircularQueue<int>();
	q->Enqueue(10);
	q->Enqueue(20);
	q->Enqueue(30);

	cout << q->Dequeue() << " ";
	cout << q->Dequeue() << " ";
	cout << q->Dequeue() << " ";

	q->Enqueue(40);
	q->Enqueue(50);

	cout << q->Dequeue() << " ";

	q->Enqueue(60);

	cout << q->Dequeue() << " ";
	cout << q->Dequeue() << " ";

	delete q;
}
