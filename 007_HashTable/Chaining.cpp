#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

#include "Chaining.h"

Chaining::Chaining(int size)
{
	nodes.resize(size);
}

Chaining::~Chaining()
{
	for (Node* node : nodes)
	{
		if (node == NULL) continue;

		stack<Node*> nodeStack;
		while (node->Next != NULL)
		{
			nodeStack.push(node);
			node = node->Next;
		}

		while (!nodeStack.empty())
		{
			delete nodeStack.top();
			nodeStack.pop();
		}
	}
}

Chaining::Node * Chaining::CreateNode(KeyType key, ValueType value)
{
	Node* node = new Node();
	node->Key = key;
	node->Value = value;
	node->Next = NULL;

	return node;
}

void Chaining::Set(KeyType key, ValueType value)
{
	int address = Hashing(key);

	Node* node = CreateNode(key, value);

	if (nodes[address] == NULL)
	{
		nodes[address] = node;
		return;
	}

	Node* current = nodes[address];
	node->Next = current;

	nodes[address] = node;

	cout << "Collision Key : " << key << " Value : " << value << endl;
}

Chaining::ValueType Chaining::Get(KeyType key)
{
	int address = Hashing(key);

	Node* node = nodes[address];
	assert(node != NULL);

	Node* target = NULL;
	while (true)
	{
		if (node->Key == key) 
		{
			target = node;
			break;
		}

		assert(node->Next != NULL);

		node = node->Next;
	}

	return target->Value;
}

int Chaining::Hashing(KeyType key)
{
	int value = 0;

	//for (size_t i = 0; i < key.size(); i++)
	//	value += (value << 3) + (int)key[i];

	for (size_t i = 0; i < key.size(); i++)
		value += (int)key[i];

	return value % (int)nodes.size();
}

void main()
{
	Chaining chaining(12289);
	chaining.Set("AXVCD", "후비적");
	chaining.Set("ZZeee", "서울게임아카데미");
	chaining.Set("zziil", "내 마음이야");
	chaining.Set("XAVCD", "충돌1");
	chaining.Set("lzzii", "충돌2");
	
	cout << "Key : AXVCD - " << chaining.Get("AXVCD") << endl;
	cout << "Key : ZZeee - " << chaining.Get("ZZeee") << endl;
	cout << "Key : lzzii - " << chaining.Get("lzzii") << endl;
	cout << "Key : AXVCD - " << chaining.Get("XAVCD") << endl;
	cout << "Key : zziil - " << chaining.Get("zziil") << endl;
}


								