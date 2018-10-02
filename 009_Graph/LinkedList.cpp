#include <windows.h>
#include "Graph.h"
#include "LinkedList.h"

Node * CreateListNode(Vertex * newData)
{
	Node* node = new Node();

	node->Data = newData;
	node->Next = NULL;

	return node;
}

void DestoryListNode(Node * node)
{
	delete node;
}

void AppendListNode(Node ** head, Node * newNode)
{
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		Node* tail = *head;

		while (tail->Next != NULL)
		{
			tail = tail->Next;
		}

		tail->Next = newNode;
	}
}

void InsertAfterListNode(Node ** Current, Node ** NewNode)
{
	(*NewNode)->Next = (*Current)->Next;
	(*Current)->Next = *NewNode;
}

void InsertNewListHead(Node ** Head, Node ** NewHead)
{
	if (Head == NULL)
	{
		*Head = *NewHead;
	}
	else
	{
		(*NewHead)->Next = *Head;
		*Head = *NewHead;
	}
}

void RemoveListNode(Node ** Head, Node ** Remove)
{
	if (*Head == *Remove)
	{
		*Head = (*Remove)->Next;
	}
	else
	{
		Node* current = *Head;
		while (current != NULL && current->Next != *Remove)
			current = current->Next;

		if (current != NULL)
			current->Next = (*Remove)->Next;
	}
}

Node * GetListNodeAt(Node * Head, int Location)
{
	Node* current = Head;
	while (current != NULL && (--Location) >= 0)
		current = current->Next;

	return current;
}

int GetListNodeCount(Node * Head)
{
	UINT count = 0;
	Node* current = Head;

	while (current != NULL)
	{
		current = current->Next;

		count++;
	}

	return count;
}
