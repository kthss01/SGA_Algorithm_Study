#include <iostream>
#include <cstdio>
#include <assert.h>
using namespace std;

template<typename T>
class Queue
{
private:
	struct Node
	{
		// data랑 우선순위 값 다르게 써야하는데 일단은 data로 우선순위 매겨볼꺼
		T Data;
	};

public:
	Queue(int maxSize = 10) : maxSize(maxSize), cursor(1)
	{
		values = new Node[maxSize];
		memset(values, 0, sizeof(Node) * maxSize);
	}

	~Queue()
	{
		delete[] values;
	}

private:
	int CompareAdd(int position)
	{
		// 부모가 큼
		// 부모가 커서 처음 넣은 자리에 그냥 둠 
		if (values[position].Data < values[position / 2].Data || position == 1)
			return 0;

		// 부모가 작음
		if (values[position].Data > values[position / 2].Data)
		{
			// Swap
			T data = values[position].Data;
			values[position].Data = values[position / 2].Data;
			values[position / 2].Data = data;

			return CompareAdd(position / 2);
		}

		return 0;
	}

public:
	void Add(T item)
	{
		// 최초
		if (cursor == 1)
		{
			values[cursor].Data = item;
			cursor++;

			return;
		}

		values[cursor].Data = item;
		CompareAdd(cursor);

		//for (int i = 0; i < maxSize; i++)
		//	cout << values[i].Data << "\t";

		for (int i = 1; i < maxSize; i++)
			printf("%2d ", values[i].Data);

		cout << endl;

		cursor++;
	}

private:
	int cursor;

	int maxSize;
	Node* values;
};

void main()
{
	Queue<int>* queue = new Queue<int>();

	queue->Add(10);
	queue->Add(8);
	queue->Add(11);
	queue->Add(12);
	queue->Add(4);
	queue->Add(5);

	delete queue;
}