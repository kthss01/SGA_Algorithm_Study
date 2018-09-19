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
		ValueType Value; // ��κ� void* ������ ǥ����

		States State = Empty;
	};

	int occupiedCount; // �ؽ� ���ִ°� Ȯ���Ϸ��� 75%�̻��̸� ���ؽ��Ϸ���
	vector<Node*> nodes;
};