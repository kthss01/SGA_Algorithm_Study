#pragma once

#include "Disjoint.h"

class Graph
{
private:
	typedef char ElementType;
	struct Edge;
	struct Node;

	struct cmp
	{

	};

public:
	Graph();
	~Graph();

	Node* CreateNode(ElementType data);
	void AddNode(Node* node);

	Edge* CreateEdge(Node* from, Node* target, int weight);
	void AddEdge(Node* node, Edge* edge);

	void Prim(Node* node, Graph* mst);

	void Print();

public:

	struct Edge
	{
		int Weight;
		Edge* Next;

		Node* From;
		Node* To;
	};

	struct Node
	{
		ElementType Data;
		bool Visited;
		int Index; // 해당 노드의 번호

		Node* Next;
		Edge* AdjacencyList;
	};

private:
	Node* nodes;
	size_t size; // unsigned int
};

struct Compare
{
	bool operator()(const Graph::Node* n1, const Graph::Node* n2)
	{
		Graph::Edge* e1 = n1->AdjacencyList;
		Graph::Edge* e2 = n2->AdjacencyList;

		if (e1->Weight > e2->Weight)
			return true;
		else
			return false;
	}
};