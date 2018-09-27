#include <iostream>
using namespace std;

#include "Disjoint.h"

void UnionSet(DisjointSet * set1, DisjointSet * set2)
{
	set2 = FindSet(set2);
	set2->Parent = set1;
}

DisjointSet * FindSet(DisjointSet * set)
{
	while (set->Parent != NULL)
		set = set->Parent;

	return set;
}

DisjointSet * MakeSet(void * newData)
{
	DisjointSet* node = new DisjointSet();
	node->Data = newData;
	node->Parent = NULL;

	return node;
}

void DestroySet(DisjointSet * set)
{
	delete set;
	set = NULL;
}
