#include <iostream>
#include <string>
using namespace std;

#include "Merge.h"

MergeHashing::MergeHashing(int size)
	: size(size)
{
	nodes = new Node[size];
}

MergeHashing::~MergeHashing()
{
	delete[] nodes;
}

void MergeHashing::Set(string key, int value)
{
	int address = Hashing(key);

	nodes[address].Key = key;
	nodes[address].Value = value;
}

int MergeHashing::Get(string key)
{
	int address = Hashing(key);

	return nodes[address].Value;
}

int MergeHashing::Hashing(string key)
{
	int value = 0;

	for (size_t i = 0; i < key.size(); i++)
		value += value << 3 + (int)key[i];

	return value % size;
}

void main()
{
	MergeHashing hashing(12289);
	hashing.Set("aabb", 10000);
	hashing.Set("qqaz", 8888);
	hashing.Set("wwww", 999);
	hashing.Set("qqzz", 10092);

	cout << "aabb / " << hashing.Get("aabb") << endl;
	cout << "qqaz / " << hashing.Get("qqaz") << endl;
	cout << "wwww / " << hashing.Get("wwww") << endl;
	cout << "qqzz / " << hashing.Get("qqzz") << endl;

}
