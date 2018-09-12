#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

template<typename T> class Tree
{
public:
	struct Node;

public:
	Node* Root() 
	{ 
		return root; 
	}

	Tree(T data) 
	{
		root = new Node(data);
	}
	~Tree()
	{
		delete root;
	}

	Node* Add(Node* parent, T data)
	{
		Node* node = new Node(data);
		node->Parent = parent;

		parent->Childs.push_back(node);
		
		return node;
	}

	void Print(Node* node, int depth)
	{
		if (node->Parent != NULL)
			cout << "�θ��� ������ : " << node->Parent->Data;

		// setw(2) == printf("%2d") �� ������
		cout << " ������ : " << node->Data << "\t\t\t���� : " << setw(5) << depth << endl;

		for (size_t i = 0; i < node->Childs.size(); i++)
			Print(node->Childs[i], depth + 1);
	}

public:
	struct Node
	{
		T Data;

		// �ڽ��� �θ� ����Ű��
		Node* Parent;
		vector<Node *> Childs;

		Node(T data) : Parent(NULL), Data(data) {}
	};

private:
	Node* root;
};
 
void main()
{
	Tree<int>* tree = new Tree<int>(20);
	Tree<int>::Node* node = NULL;
	node = tree->Add(tree->Root(), 30);
	tree->Add(node, 100);
	tree->Add(node, 200);
	tree->Add(node, 300);

	node = tree->Add(tree->Root(), 40);
	node = tree->Add(node, 400);
	tree->Add(node, 2000);

	node = tree->Add(tree->Root(), 50);
	tree->Add(node, 500);

	tree->Print(tree->Root(), 0);

	delete tree;
}