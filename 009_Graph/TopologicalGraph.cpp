#include <iostream>
#include <queue>
#include <list>
using namespace std;

#include "TopologicalGraph.h"

TopologicalGraph::TopologicalGraph()
{
	nodes = NULL;
	size = 0;
}

TopologicalGraph::~TopologicalGraph()
{
}

TopologicalGraph::Node* TopologicalGraph::CreateNode(ElementType data)
{
	Node* node = new Node();
	node->Data = data;
	node->Next = NULL;
	node->AdjacencyList = NULL;
	node->Visited = false;
	node->Index = -1;
	
	return node;
}

void TopologicalGraph::AddNode(Node * node)
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

TopologicalGraph::Edge * TopologicalGraph::CreateEdge(Node * from, Node * target, int weight)
{
	Edge* edge = new Edge();
	edge->From = from;
	edge->To = target;
	edge->Next = NULL;
	edge->Weight = weight;

	return edge;
}

void TopologicalGraph::AddEdge(Node * node, Edge * edge)
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

void TopologicalGraph::DFS(Node * node)
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

void TopologicalGraph::BFS(Node * node, queue<Node*>& nodeQueue)
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

void TopologicalGraph::Sort(Node * node, list<Node*>& nodeList)
{
	while (node != NULL && node->Visited == false)
	{
		DFS(node, nodeList);

		node = node->Next;
	}
}

void TopologicalGraph::DFS(Node * node, list<Node*>& nodeList)
{
	node->Visited = true;

	cout << node->Data << " ";

	Node* newNode = new Node();
	memcpy(newNode, node, sizeof(Node));
	nodeList.push_back(newNode);

	//Edge* e = node->AdjacencyList;
	//while (e != NULL)
	//{
	//	if (e->To != NULL && e->To->Visited == false)
	//		DFS(e->To, nodeList);
	//
	//	e = e->Next;
	//}
}

void TopologicalGraph::Print()
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
	TopologicalGraph* g = new TopologicalGraph();

	TopologicalGraph::Node* n1 = g->CreateNode('A');
	TopologicalGraph::Node* n2 = g->CreateNode('B');
	TopologicalGraph::Node* n3 = g->CreateNode('C');
	TopologicalGraph::Node* n4 = g->CreateNode('D');
	TopologicalGraph::Node* n5 = g->CreateNode('E');

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

	//queue<TopologicalGraph::Node*> q;
	//g->BFS(n1, q);
	//cout << endl;

	list<TopologicalGraph::Node*> nodeList;
	g->Sort(n1, nodeList);
	cout << endl;

	delete g;
}
