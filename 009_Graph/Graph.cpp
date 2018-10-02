#include <windows.h>
#include <iostream>
using namespace std;

#include <cstdio>

#include "Graph.h"

Graph * CreateGraph()
{
	Graph* graph = new Graph();
	graph->Vertices = NULL;
	graph->VertexCount = 0;

	return graph;
}

void DestroyGraph(Graph * graph)
{
	while (graph->Vertices != NULL)
	{
		Vertex* Vertices = graph->Vertices->Next;
		DestroyVertex(graph->Vertices);

		graph->Vertices = Vertices;
	}

	delete graph;
}

Vertex * CreateVertex(VertexDataType data)
{
	Vertex* vertex = new Vertex();

	vertex->Data = data;
	vertex->Next = NULL;
	vertex->Adjacency = NULL;
	vertex->Visited = false;
	vertex->Index = -1;

	return vertex;
}

void DestroyVertex(Vertex * vertex)
{
	while (vertex->Adjacency != NULL)
	{
		Edge* edge = vertex->Adjacency->Next;
		DestroyEdge(vertex->Adjacency);

		vertex->Adjacency = edge;
	}

	delete vertex;
}

Edge * CreateEdge(Vertex * from, Vertex * to, int weight)
{
	Edge* edge = new Edge();
	edge->From = from;
	edge->To = to;
	edge->Next = NULL;
	edge->Weight = weight;

	return edge;
}

void DestroyEdge(Edge * edge)
{
	delete edge;
}

void AddVertex(Graph * graph, Vertex * vertex)
{
	Vertex* vertices = graph->Vertices;

	if (vertices == NULL)
	{
		graph->Vertices = vertex;
	}
	else
	{
		while (vertices->Next != NULL)
			vertices = vertices->Next;

		vertices->Next = vertex;
	}

	vertex->Index = graph->VertexCount++;
}

void AddEdge(Vertex * vertex, Edge * edge)
{
	if (vertex->Adjacency == NULL)
	{
		vertex->Adjacency = edge;
	}
	else
	{
		Edge* adjacency = vertex->Adjacency;

		while (adjacency->Next != NULL)
			adjacency = adjacency->Next;

		adjacency->Next = edge;
	}
}

void PrintGraph(Graph * graph)
{
	Vertex* vertex = NULL;
	Edge* edge = NULL;

	if ((vertex = graph->Vertices) == NULL)
		return;

	while (vertex != NULL)
	{
		cout << (char)vertex->Data << " : ";

		if ((edge = vertex->Adjacency) == NULL) 
		{
			vertex = vertex->Next;
			cout << endl;

			continue;
		}

		while (edge != NULL)
		{
			//cout << (char)edge->To->Data << "[" << edge->Weight << "] ";
			printf("%c[%3d] ", edge->To->Data, edge->Weight);
			edge = edge->Next;
		}

		vertex = vertex->Next;
		cout << endl;
	}

	cout << endl;
}
