#pragma once

class Chaining
{
private:
	typedef string KeyType;
	typedef string ValueType;

	struct Node;

public:
	Chaining(int size);
	~Chaining();

	Node* CreateNode(KeyType key, ValueType value);
	void Set(KeyType key, ValueType value);
	ValueType Get(KeyType key);

private:
	int Hashing(KeyType key);

private:
	struct Node
	{
		KeyType Key;
		ValueType Value; // 대부분 void* 형으로 표현함

		Node* Next = NULL;
	};

	vector<Node*> nodes;
};