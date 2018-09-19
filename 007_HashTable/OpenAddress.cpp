#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <assert.h>
using namespace std;

#include "OpenAddress.h"

OpenAddress::OpenAddress(int size)
	: occupiedCount(0)
{
	nodes.resize(size, NULL);
}

OpenAddress::~OpenAddress()
{
	for (Node* node : nodes)
	{
		if (node == NULL) continue;

		delete node;
	}
}

OpenAddress::Node * OpenAddress::CreateNode(KeyType key, ValueType value)
{
	Node* node = new Node();
	node->Key = key;
	node->Value = value;
	node->State = Occupied;

	return node;
}

void OpenAddress::Set(KeyType key, ValueType value)
{
	Set(this->nodes, key, value);
}

void OpenAddress::Set(vector<Node*>& nodes, KeyType key, ValueType value)
{
	float usage = (float)occupiedCount / (float)nodes.size();
	if (usage >= 0.75f)
		ReHashing();

	int addr = Hashing(key);
	int step = Hashing2(key);

	int cnt = 0;
	while (nodes[addr] != NULL && nodes[addr]->State != Empty && nodes[addr]->Key != key)
	{
		cout << "충돌 Key : " << key << " Addr : " << addr;
		cout << " Step : " << step << endl;

		addr = (addr + step) % (int)nodes.size();
		cnt++;
		if (cnt >= nodes.size()) {
			cnt = 0;
			step--;
		}
	}
	

	nodes[addr] = CreateNode(key, value);
	occupiedCount++;
}

// 못찾으면 assert 같은거 추가해줘야함
OpenAddress::ValueType OpenAddress::Get(KeyType key)
{
	int addr = Hashing(key);
	int step = Hashing2(key);

	int cnt = 0;
	while (nodes[addr] == NULL && nodes[addr]->State != Empty && nodes[addr]->Key != key) {
		addr = (addr + step) % (int)nodes.size();

		cnt++;
		if (cnt >= nodes.size()) {
			cnt = 0;
			step--;
		}
	}

	return nodes[addr]->Value;
}

int OpenAddress::Hashing(KeyType key)
{
	int value = 0;

	for (size_t i = 0; i < key.size(); i++)
		value += (value << 3) + (int)key[i];

	//for (size_t i = 0; i < key.size(); i++)
	//	value += (int)key[i];

	return value % (int)nodes.size();
}

int OpenAddress::Hashing2(KeyType key)
{
	int value = 0;

	for (size_t i = 0; i < key.size(); i++)
		value = (value << 2) + key[i];

	value = value % ((int)nodes.size() - 3);

	return value + 1;

	//for (size_t i = 0; i < key.size(); i++)
	//	value = (value << 3) + key[i];

	//value = value % ((int)nodes.size());

	return value;
}

void OpenAddress::ReHashing()
{
	vector<Node *> re;
	re.resize(nodes.size() * 2);

	cout << "리해싱 : " << re.size() << endl;

	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] == NULL) continue;

		if (nodes[i]->State == Occupied)
		{
			int addr = Hashing(nodes[i]->Key);
			int step = Hashing2(nodes[i]->Key);

			while (re[addr] != NULL && re[addr]->State != Empty && re[addr]->Key != nodes[i]->Key)
			{
				cout << "충돌 Key : " << nodes[i]->Key << " Addr : " << addr;
				cout << " Step : " << step << endl;

				addr = (addr + step) % (int)re.size();
			}

			re[addr] = nodes[i];
		}

	}

	//for (Node* node : nodes) {
	//	if (node != NULL)
	//		delete node;
	//}

	nodes.resize(re.size());
	nodes.assign(re.begin(), re.end());
}

void main()
{
	OpenAddress chaining(1);
	chaining.Set("MSFT", "Microsoft Corporation");
	chaining.Set("JAVA", "Sun Microsystems");
	chaining.Set("REDH", "Red Hat Linux");
	chaining.Set("APAC", "Apache Org");
	chaining.Set("ZYMZZ", "Unisys Ops Check"); /*  APAC와 충돌 */
	chaining.Set("IBM", "IBM Ltd.");
	chaining.Set("ORCL", "Oracle Corporation");
	chaining.Set("CSCO", "Cisco Systems, Inc.");
	chaining.Set("GOOG", "Google Inc.");
	chaining.Set("YHOO", "Yahoo! Inc.");
	chaining.Set("NOVL", "Novell, Inc.");

	cout << endl;
	cout << "MSFT " << chaining.Get("MSFT") << endl;
	cout << "REDH " << chaining.Get("REDH") << endl;
	cout << "APAC " << chaining.Get("APAC") << endl;
	cout << "ZYMZZ " << chaining.Get("ZYMZZ") << endl;
	cout << "JAVA " << chaining.Get("JAVA") << endl;
	cout << "IBM " << chaining.Get("IBM") << endl;
	cout << "ORCL " << chaining.Get("ORCL") << endl;
	cout << "CSCO " << chaining.Get("CSCO") << endl;
	cout << "GOOG " << chaining.Get("GOOG") << endl;
	cout << "YHOO " << chaining.Get("YHOO") << endl;
	cout << "NOVL " << chaining.Get("NOVL") << endl;
}


								