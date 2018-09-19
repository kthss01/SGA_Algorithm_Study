#include <iostream>
using namespace std;

#include "Simple.h"

SimpleHashing::SimpleHashing(int size)
	: size(size)
{
	nodes = new Node[size];
}

SimpleHashing::~SimpleHashing()
{
	delete[] nodes;
}

void SimpleHashing::Set(int key, int value)
{
	int address = Hashing(key);

	nodes[address].Key = key;
	nodes[address].Value = value;
}

int SimpleHashing::Get(int key)
{
	int address = Hashing(key);

	return nodes[address].Value;
}

int SimpleHashing::Hashing(int key)
{
	return key % size;
}

void main()
{
	SimpleHashing hashing(193);
	hashing.Set(399, 10000);
	hashing.Set(419, 8888);
	hashing.Set(5, 999);
	hashing.Set(815, 10092);

	cout << "399 / " << hashing.Get(399) << endl;
	cout << "419 / " << hashing.Get(419) << endl;
	cout << "5 / " << hashing.Get(5) << endl;
	cout << "815 / " << hashing.Get(815) << endl;

}
