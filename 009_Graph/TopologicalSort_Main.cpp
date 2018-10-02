#include <Windows.h>
#include "LinkedList.h"
#include "Graph.h"

#include "TopologicalSort.h"

#include <iostream>
#include <string>
using namespace std;

void main() 
{
	Node* sortedList = NULL;
	Node* currentNode = NULL;
	Graph* graph = CreateGraph();

	Vertex* A = CreateVertex('A');
	Vertex* B = CreateVertex('B');
	Vertex* C = CreateVertex('C');
	Vertex* D = CreateVertex('D');
	Vertex* E = CreateVertex('E');
	Vertex* F = CreateVertex('F');
	Vertex* G = CreateVertex('G');
	Vertex* H = CreateVertex('H');

	AddVertex(graph, A);
	AddVertex(graph, B);
	AddVertex(graph, C);
	AddVertex(graph, D);
	AddVertex(graph, E);
	AddVertex(graph, F);
	AddVertex(graph, G);
	AddVertex(graph, H);

	AddEdge(A, CreateEdge(A, C, 0));
	AddEdge(A, CreateEdge(A, D, 0));
	AddEdge(B, CreateEdge(B, C, 0));
	AddEdge(B, CreateEdge(B, E, 0));
	AddEdge(C, CreateEdge(C, F, 0));
	AddEdge(D, CreateEdge(D, F, 0));
	AddEdge(D, CreateEdge(D, G, 0));
	AddEdge(E, CreateEdge(E, G, 0));
	AddEdge(F, CreateEdge(F, H, 0));
	AddEdge(G, CreateEdge(G, H, 0));

	TopologicalSort(graph->Vertices, &sortedList);

	cout << endl;
	cout << "Sort Result : ";
	
	currentNode = sortedList;
	
	while (currentNode != NULL) 
	{
		cout << (char)currentNode->Data->Data << " ";
		
		currentNode = currentNode->Next;
	}

	cout << endl;

	DestroyGraph(graph);
}