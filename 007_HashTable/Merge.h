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
		int Value; // 대부분 void* 형으로 표현함
	};

	int size;
	Node* nodes; // node들을 저장하는 공간
};