//#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// 양방향 연결 리스트
template<typename T> class LinkedList
{
public:
	struct Node;

private:
	Node* NewNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		node->Prev = node->Next = NULL;

		return node;
	}

public:
	LinkedList(T data)
	{
		head = NewNode(data);
		tail = NewNode(data);

		head->Next = tail;
		tail->Prev = head;
		
		count = 0;
	}

	~LinkedList()
	{
		Clear();

		delete head;
		delete tail;
	}

	void Add(T data)
	{
		Node* node = NewNode(data);
		node->Prev = tail->Prev;
		node->Next = tail;

		tail->Prev->Next = node;
		tail->Prev = node;

		count++;
	}

	void Remove(Node* node)
	{
		node->Prev->Next = node->Next;
		node->Next->Prev = node->Prev;

		delete node;
		count--;
	}

	Node* Find(T data)
	{
		Node* seek = head->Next;
		while (seek != tail)
		{
			if (seek->Data == data)
				return seek;

			seek = seek->Next;
		}

		return NULL;
	}

	// 해당 위치에서부터 검색
	Node* Find(Node* seek, T data)
	{
		seek = seek->Next;
		while (seek != tail)
		{
			if (seek->Data == data)
				return seek;

			seek = seek->Next;
		}

		return NULL;
	}

	void Print()
	{
		Node* seek = head->Next;
		cout << "리스트 노드 갯수 : " << count;

		for (int i = 0; seek != tail; i++)
		{
			if (i % 5 == 0)
				cout << endl;
		
			cout << seek->Data << " ";

			seek = seek->Next;
		}

		cout << endl;
	}

	void Clear()
	{
		Node* seek = tail->Prev;

		while (seek != head)
		{
			Remove(seek);

			seek = tail->Prev;
		}
	}

public:
	struct Node
	{
		T Data;

		Node* Prev;
		Node* Next;
	};

private:
	Node* head;
	Node* tail;

	int count;
};

void main()
{
	srand(time(NULL));

	LinkedList<int>* list = new LinkedList<int>(0);

	for (int i = 0; i < 20; i++)
	{
		list->Add(rand() % 100);
	}

	list->Print();

	delete list;
}