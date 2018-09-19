#pragma once

class MergeHashing
{
public:
	MergeHashing(int size);
	~MergeHashing();

	void Set(string key, int value);
	int Get(string key);

private:
	int Hashing(string key);

private:
	struct Node
	{
		string Key;
		int Value; // ��κ� void* ������ ǥ����
	};

	int size;
	Node* nodes; // node���� �����ϴ� ����
};