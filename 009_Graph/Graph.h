#pragma once

typedef int VertexDataType;

struct Vertex
{
	VertexDataType Data;
	bool Visited;
	int Index;

	Vertex* Next;
	struct Edge* Adjacency;
};

struct Edge
{
	int Weight;
	Edge* Next;
	Vertex* From;
	Vertex* To;
};

struct Graph
{
	Vertex* Vertices;
	int VertexCount;
};

Graph* CreateGraph();
void   DestroyGraph(Graph* graph);

Vertex* CreateVertex(VertexDataType data);
void    DestroyVertex(Vertex* vertex);

Edge*   CreateEdge(Vertex* from, Vertex* to, int weight);
void    DestroyEdge(Edge* edge);

void   AddVertex(Graph* graph, Vertex* vertex);
void   AddEdge(Vertex* vertex, Edge* edge);
void   PrintGraph(Graph* graph);