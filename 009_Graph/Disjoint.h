#pragma once

struct DisjointSet
{
	DisjointSet* Parent = NULL;
	void* Data = NULL;
};

void UnionSet(DisjointSet* set1, DisjointSet* set2);
DisjointSet* FindSet(DisjointSet* set);
DisjointSet* MakeSet(void* newData);
void DestroySet(DisjointSet* set);