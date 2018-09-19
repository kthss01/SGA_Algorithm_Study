#pragma once

class SimpleHashing
{
public:
	SimpleHashing(int size);
	~SimpleHashing();

	void Set(int key, int value);
	int Get(int key);

private:
	int Hashing(int key);

private:
	struct Node
	{
		int Key;
		int Value; // ��κ� void* ������ ǥ����
	};

	int size;
	Node* nodes; // node���� �����ϴ� ����
};