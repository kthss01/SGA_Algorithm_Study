#pragma once

class Graph
{
private:
	typedef char ElementType;
	struct Edge;
	struct Node;

public:
	Graph();
	~Graph();

	Node* CreateNode(ElementType data);
	void AddNode(Node* node);

	Edge* CreateEdge(Node* from, Node* target, int weight);
	void AddEdge(Node* node, Edge* edge);

	void DFS(Node* node);
	void BFS(Node* node, queue<Node *>& nodeQueue);
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