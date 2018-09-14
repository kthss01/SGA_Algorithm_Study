#include <iostream>
using namespace std;

// transpose : ������ �ڹٲٴ�
// ���� Ž�� : ����

template <typename T> class Transpose
{
private:
	struct Node;

public:
	Transpose()
	{
	}

	~Transpose()
	{
	}

	Node* MoveToFront(Node** head, T data)
	{
		Node* current = *head;
		Node* prev = NULL;
		Node* match = NULL;

		while (current != NULL)
		{
			if (current->Data == data) 
			{
				match = current;
				if (prev != NULL)
				{
					prev->Next = current->Next;

					current->Next = *head;
					*head = current;
				}
				break;
			}
			else
			{
				prev = current;
				current = current->Next;
			}
		}

		return match;
	}

	Node* MoveToHead(Node** head, T data)
	{
		Node* current = *head;
		Node* pprev = NULL; // ���� ����� ���� ���
		Node* prev = NULL;
		Node* match = NULL;

		while (current != NULL) 
		{
			if (current->Data == data)
			{
				match = current;

				if (prev != NULL)
				{
					if (pprev != NULL)
						pprev->Next = current;
					else
						*head = current;

					prev->Next = current->Next;
					current->Next = prev;
				} // if(prev)
				break;
			}
			else
			{
				if (prev != NULL)
					pprev = prev;

				prev = current;
				current = current->Next;
			}
		}

	}

public:
	struct Node
	{
		Node* Next;

		T Data;

		Node(T data) : Data(data) {}
	};
};

void main()
{

}
