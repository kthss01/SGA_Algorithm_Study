#include <iostream>
#include <queue>
using namespace std;

#include "Graph.h"

Graph::Graph()
{
	nodes = NULL;
	size = 0;
}

Graph::~Graph()
{
}

Graph::Node* Graph::CreateNode(ElementType data)
{
	Node* node = new Node();
	node->Data = data;
	node->Next = NULL;
	node->AdjacencyList = NULL;
	node->Visited = false;
	node->Index = -1;
	
	return node;
}

void Graph::AddNode(Node * node)
{
	Node* nodeList = nodes;

	if (nodeList == NULL)
	{
		nodes = node;
	}
	else
	{
		while (nodeList->Next != NULL)
			nodeList = nodeList->Next;

		nodeList->Next = node;
	}

	node->Index++;
}

Graph::Edge * Graph::CreateEdge(Node * from, Node * target, int weight)
{
	Edge* edge = new Edge();
	edge->From = from;
	edge->To = target;
	edge->Next = NULL;
	edge->Weight = weight;

	return edge;
}

void Graph::AddEdge(Node * node, Edge * edge)
{
	if (node->AdjacencyList == NULL)
	{
		node->AdjacencyList = edge;
	}
	else
	{
		Edge* e = node->AdjacencyList;

		while (e->Next != NULL)
			e = e->Next;

		e->Next = edge;
	}
}

void Graph::DFS(Node * node)
{
	cout << node->Data << " ";
	node->Visited = true;

	Edge* e = node->AdjacencyList;
	while (e != NULL)
	{
		if (e->To != NULL && e->To->Visited == false)
			DFS(e->To);

		e = e->Next;
	}
}

void Graph::BFS(Node * node, queue<Node*>& nodeQueue)
{
	cout << node->Data << " ";
	node->Visited = true;
	nodeQueue.push(node);

	while (nodeQueue.size() > 0)
	{
		Node* pop = nodeQueue.front();
		nodeQueue.pop();

		node = pop;
		Edge* e = node->AdjacencyList;

		while (e != NULL)
		{
			node = e->To;
			if (node != NULL && node->Visited == false)
			{
				cout << node->Data << " ";
				node->Visited = true;
				nodeQueue.push(node);
			}

			e = e->Next;
		}
	}
}

void Graph::Print()
{
	Node* node = NULL;
	Edge* edge = NULL;

	if ((node = nodes) == NULL)
		return;

	while (node != NULL)
	{
		cout << node->Data << " : ";

		if ((edge = node->AdjacencyList) == NULL)
		{
			node = node->Next;
			cout << endl;

			continue;
		}

		while (edge != NULL)
		{
			cout << edge->To->Data << " [" << edge->Weight << "] ";
			edge = edge->Next;
		}

		cout << endl;
		node = node->Next;
	}

	cout << endl;
}

void main()
{
	Graph* g = new Graph();

	Graph::Node* n1 = g->CreateNode('A');
	Graph::Node* n2 = g->CreateNode('B');
	Graph::Node* n3 = g->CreateNode('C');
	Graph::Node* n4 = g->CreateNode('D');
	Graph::Node* n5 = g->CreateNode('E');

	g->AddNode(n1);
	g->AddNode(n2);
	g->AddNode(n3);
	g->AddNode(n4);
	g->AddNode(n5);

	g->AddEdge(n1, g->CreateEdge(n1, n2, 0));
	g->AddEdge(n1, g->CreateEdge(n1, n3, 0));
	g->AddEdge(n1, g->CreateEdge(n1, n4, 0));
	g->AddEdge(n1, g->CreateEdge(n1, n5, 0));

	g->AddEdge(n2, g->CreateEdge(n2, n1, 0));
	g->AddEdge(n2, g->CreateEdge(n2, n3, 0));
	g->AddEdge(n2, g->CreateEdge(n2, n5, 0));

	g->AddEdge(n3, g->CreateEdge(n3, n1, 0));
	g->AddEdge(n3, g->CreateEdge(n3, n2, 0));

	g->AddEdge(n4, g->CreateEdge(n4, n1, 0));
	g->AddEdge(n4, g->CreateEdge(n4, n5, 0));

	g->AddEdge(n5, g->CreateEdge(n5, n1, 0));
	g->AddEdge(n5, g->CreateEdge(n5, n2, 0));
	g->AddEdge(n5, g->CreateEdge(n5, n4, 0));

	g->Print();
	cout << endl;

	//g->DFS(n1);
	//cout << endl;

	queue<Graph::Node*> q;
	g->BFS(n1, q);
	cout << endl;

	delete g;
}
