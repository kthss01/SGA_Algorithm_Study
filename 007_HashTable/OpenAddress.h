#pragma once

class OpenAddress
{
private:
	enum States { Empty, Occupied };

	typedef string KeyType;
	typedef string ValueType;

	struct Node;

public:
	OpenAddress(int size);
	~OpenAddress();

	Node* CreateNode(KeyType key, ValueType value);
	void Set(KeyType key, ValueType value);
	void Set(vector<Node*>& nodes, KeyType key, ValueType value);
	ValueType Get(KeyType key);

private:
	int Hashing(KeyType key);
	int Hashing2(KeyType key);

	void ReHashing();

private:
	struct Node
	{
		KeyType Key;
		ValueType Value; // 대부분 void* 형으로 표현함

		States State = Empty;
	};

	int occupiedCount; // 해쉬 차있는거 확인하려고 75%이상이면 재해싱하려고
	vector<Node*> nodes;
};