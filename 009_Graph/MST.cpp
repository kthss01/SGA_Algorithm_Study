#include <Windows.h>

#include "Graph.h"
#include "Priority.h"
#include "Disjoint.h"

#include "MST.h"

#include <cstdio>

#define MAX_WEIGHT 32767 // short int

void Prim(Graph * graph, Vertex * startVertex, Graph * mst)
{
	QueueNode startNode;
	startNode.Data = startVertex;
	startNode.Priority = 0;

	int* weights = new int[graph->VertexCount];
	// 포인터 배열
	Vertex** mstVertices = new Vertex*[graph->VertexCount];
	Vertex** fringes = new Vertex*[graph->VertexCount]; // 가장자리
	Vertex** precedences = new Vertex*[graph->VertexCount];

	Vertex* currentVertex = graph->Vertices;

	int i = 0;
	while (currentVertex != NULL)
	{
		Vertex* vertex = CreateVertex(currentVertex->Data);
		AddVertex(mst, vertex);

		fringes[i] = NULL;
		precedences[i] = NULL;
		mstVertices[i] = vertex;
		weights[i] = MAX_WEIGHT;
		currentVertex = currentVertex->Next;

		i++;
	}
	
	PriorityQueue* q = CreateQueue(10);
	Enqueue(q, startNode);
	weights[startVertex->Index] = 0;

	Edge* currentEdge = NULL;
	while (IsEmptyQueue(q) == false) 
	{
		QueueNode pop;

		Dequeue(q, &pop);
		currentVertex = (Vertex *)pop.Data;

		// 방문한곳 체크
		fringes[currentVertex->Index] = currentVertex;

		currentEdge = currentVertex->Adjacency;
		while (currentEdge != NULL)
		{
			Vertex* toVertex = currentEdge->To;

			if (fringes[toVertex->Index] == NULL
				&& currentEdge->Weight < weights[toVertex->Index])
			{
				QueueNode newNode = { currentEdge->Weight, toVertex };
				Enqueue(q, newNode);

				precedences[toVertex->Index] = currentEdge->From;
				weights[toVertex->Index] = currentEdge->Weight;
			}

			currentEdge = currentEdge->Next;
		} // while(currentEdge)
	} // while(IsEmptyQueue)

	for (i = 0; i < graph->VertexCount; i++)
	{
		int from, to;

		if (precedences[i] == NULL)
			continue;

		from = precedences[i]->Index;
		to = i;

		// 양방향이라 둘다 한거 단방향이면 하나만 하면됨
		AddEdge(mstVertices[from], CreateEdge(mstVertices[from], mstVertices[to], weights[i]));
		AddEdge(mstVertices[to], CreateEdge(mstVertices[to], mstVertices[from], weights[i]));

		printf("%c -> %c, %3d\n", mstVertices[from]->Data, mstVertices[to]->Data, weights[i]);
	}
	printf("\n");

	delete[] fringes;
	delete[] precedences;
	delete[] mstVertices;
	delete[] weights;

	DestroyQueue(q);
}

void Kruskal(Graph * graph, Graph * mst)
{
	// weight 오름차순 정렬 후 부분집합으로 이어가기
	Vertex** mstVertices = new Vertex*[graph->VertexCount];
	DisjointSet** vertexSet = new DisjointSet*[graph->VertexCount];

	PriorityQueue* q = CreateQueue(10);

	int i = 0;
	Vertex* currentVertex = graph->Vertices;
	// 정렬한거라고 생각하면됨
	while (currentVertex != NULL)
	{
		Edge* currentEdge;

		vertexSet[i] = MakeSet(currentVertex);
		mstVertices[i] = CreateVertex(currentVertex->Data);
		AddVertex(mst, mstVertices[i]);

		currentEdge = currentVertex->Adjacency;
		while (currentEdge != NULL)
		{
			QueueNode newNode = { currentEdge->Weight, currentEdge };
			Enqueue(q, newNode);

			currentEdge = currentEdge->Next;
		}

		currentVertex = currentVertex->Next;
		i++;
	}

	while (IsEmptyQueue(q) == false)
	{
		QueueNode pop;
		Dequeue(q, &pop);
		
		Edge* currentEdge = (Edge *)pop.Data;

		printf("%c - %c : %d\n",
			currentEdge->From->Data, currentEdge->To->Data, currentEdge->Weight);

		int from = currentEdge->From->Index;
		int to = currentEdge->To->Index;

		if (FindSet(vertexSet[from]) != FindSet(vertexSet[to]))
		{
			AddEdge(mstVertices[from], CreateEdge(mstVertices[from], mstVertices[to], currentEdge->Weight));
			AddEdge(mstVertices[to], CreateEdge(mstVertices[to], mstVertices[from], currentEdge->Weight));

			UnionSet(vertexSet[from], vertexSet[to]);
		}
	}

	for (int i = 0; i < graph->VertexCount; i++)
		DestroySet(vertexSet[i]);

	delete[] vertexSet;
	delete[] mstVertices;
}

void Dijkstra(Graph * graph, Vertex * startVertex, Graph * mst)
{
	QueueNode startNode;
	startNode.Data = startVertex;
	startNode.Priority = 0;

	int* weights = new int[graph->VertexCount];
	// 포인터 배열
	Vertex** fringes = new Vertex*[graph->VertexCount]; // 가장자리
	Vertex** precedences = new Vertex*[graph->VertexCount];
	Vertex** shortest = new Vertex*[graph->VertexCount];

	int i = 0;
	Vertex* currentVertex = graph->Vertices;

	while (currentVertex != NULL)
	{
		Vertex* vertex = CreateVertex(currentVertex->Data);
		AddVertex(mst, vertex);

		fringes[i] = NULL;
		precedences[i] = NULL;
		shortest[i] = vertex;
		weights[i] = MAX_WEIGHT;
		currentVertex = currentVertex->Next;

		i++;
	}

	PriorityQueue* q = CreateQueue(10);
	Enqueue(q, startNode);
	weights[startVertex->Index] = 0;

	Edge* currentEdge = NULL;
	while (IsEmptyQueue(q) == false)
	{
		QueueNode pop;

		Dequeue(q, &pop);
		currentVertex = (Vertex *)pop.Data;

		// 방문한곳 체크
		fringes[currentVertex->Index] = currentVertex;

		currentEdge = currentVertex->Adjacency;
		while (currentEdge != NULL)
		{
			Vertex* toVertex = currentEdge->To;

			if (fringes[toVertex->Index] == NULL
				&& currentEdge->Weight + weights[currentVertex->Index] < weights[toVertex->Index])
			{
				QueueNode newNode = { currentEdge->Weight, toVertex };
				Enqueue(q, newNode);

				precedences[toVertex->Index] = currentEdge->From;
				weights[toVertex->Index] = currentEdge->Weight + weights[currentVertex->Index];
			}

			currentEdge = currentEdge->Next;
		} // while(currentEdge)
	} // while(IsEmptyQueue)

	for (i = 0; i < graph->VertexCount; i++)
	{
		int from, to;

		if (precedences[i] == NULL)
			continue;

		from = precedences[i]->Index;
		to = i;

		// 양방향이라 둘다 한거 단방향이면 하나만 하면됨
		AddEdge(shortest[from], CreateEdge(shortest[from], shortest[to], weights[i]));
		AddEdge(shortest[to], CreateEdge(shortest[to], shortest[from], weights[i]));

		printf("%c -> %c, %3d\n", shortest[from]->Data, shortest[to]->Data, weights[i]);
	}
	printf("\n");

	delete[] fringes;
	delete[] precedences;
	delete[] shortest;
	delete[] weights;

	DestroyQueue(q);
}
