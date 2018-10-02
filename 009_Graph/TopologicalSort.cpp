#include <Windows.h>
#include "LinkedList.h"
#include "Graph.h"

#include "TopologicalSort.h"

#include <iostream>
using namespace std;

void TopologicalSort(Vertex * vertex, Node ** list)
{
	while (vertex != NULL && vertex->Visited == false) {
		TopologicalDFS(vertex, list);

		vertex = vertex->Next;
	}
}

void TopologicalDFS(Vertex * vertex, Node ** list)
{
	Node* head = NULL;
	Edge* edge = NULL;

	vertex->Visited = true;
	edge = vertex->Adjacency;

	while (edge != NULL)
	{
		if (edge->To != NULL && edge->To->Visited == false)
			TopologicalDFS(edge->To, list);

		edge = edge->Next;
	}

	cout << (char)vertex->Data << " ";

	head = CreateListNode(vertex);
	InsertNewListHead(list, &head);
}
