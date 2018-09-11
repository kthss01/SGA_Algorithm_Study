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
		// data�� �켱���� �� �ٸ��� ����ϴµ� �ϴ��� data�� �켱���� �Űܺ���
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
		// �θ� ŭ
		// �θ� Ŀ�� ó�� ���� �ڸ��� �׳� �� 
		if (values[position].Data < values[position / 2].Data || position == 1)
			return 0;

		// �θ� ����
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
		// ����
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