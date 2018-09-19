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
		int Value; // 대부분 void* 형으로 표현함
	};

	int size;
	Node* nodes; // node들을 저장하는 공간
};