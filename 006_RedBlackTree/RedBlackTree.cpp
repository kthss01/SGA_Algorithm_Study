#include <iostream>
#include <assert.h>
using namespace std;

class RedBlackTree
{
private:
	struct Node;
	// enum class class 내에 소속된거라 전역이 아님
	enum class Colors { Red = 0, Black };

public:
	RedBlackTree(int data)
	{
		root = new Node(data);
		root->Color = Colors::Black;
		root->L = nil;
		root->R = nil;
	}

	~RedBlackTree()
	{

	}

	void Insert(int data)
	{
		Node* node = new Node(data);
		Insert(root, node);

		node->Color = Colors::Red; // 처음 넣을때는 일단 Red Rebuild일 때 검증
		node->L = nil;
		node->R = nil;

		Rebuild(node);
	}

private:
	void Insert(Node* node, Node* newNode)
	{
		assert(node->Data != newNode->Data);

		if (node->Data < newNode->Data)
		{
			if (node->R == nil)
			{
				node->R = newNode;
				newNode->P = node;
			}
			else
				Insert(node->R, newNode);
		}
		else
		{
			if (node->L == nil)
			{
				node->L = newNode;
				newNode->P = node;
			}
			else
				Insert(node->L, newNode);
		}
	}

	void RotateRight(Node* parent) 
	{
		Node* leftChild = parent->L;
		parent->L = leftChild->R;

		if (leftChild->R != nil)
			leftChild->R->P = parent;

		leftChild->P = parent->P;

		if (parent->P == NULL)
		{
			root = leftChild;
		}
		else
		{
			if (parent == parent->P->L)
				parent->P->L = leftChild;
			else
				parent->P->R = leftChild;
		}

		leftChild->R = parent;
		parent->P = leftChild;
	}

	void RotateLeft(Node* parent)
	{
		Node* rightChild = parent->R;
		parent->R = rightChild->L;

		if (rightChild->L != nil)
			rightChild->L->P = parent;

		rightChild->P = parent->P;

		if (parent->P == NULL)
		{
			root = rightChild;
		}
		else
		{
			if (parent == parent->P->L)
				parent->P->L = rightChild;
			else
				parent->P->R = rightChild;
		}

		rightChild->L = parent;
		parent->P = rightChild;
	}

	void Rebuild(Node* node)
	{
		while (node != root && node->P->Color == Colors::Red)
		{
			if (node->P == node->P->P->L)
			{
				Node* uncle = node->P->P->R;
				// uncle이 Red일때는 Recoloring 
				if (uncle->Color == Colors::Red)
				{
					node->P->Color = Colors::Black;
					uncle->Color = Colors::Black;
					node->P->P->Color = Colors::Red;

					node = node->P->P;
				}
				// uncle이 Black일때는 Restructuring
				else
				{
					if (node == node->P->R)
					{
						node = node->P;

						RotateLeft(node);
					}

					node->P->Color = Colors::Black;
					node->P->P->Color = Colors::Red;

					RotateRight(node->P->P);
				}
			} // if(node->P)
			else 
			{
				Node* uncle = node->P->P->L;
				if (uncle->Color == Colors::Red)
				{
					node->P->Color = Colors::Black;
					uncle->Color = Colors::Black;
					node->P->P->Color = Colors::Red;

					node = node->P->P;
				}
				else
				{
					if (node == node->P->L)
					{
						node = node->P;

						RotateRight(node);
					}

					node->P->Color = Colors::Black;
					node->P->P->Color = Colors::Red;

					RotateLeft(node->P->P);
				}
			}

		} // while(node)

		root->Color = Colors::Black;
	}

public:
	void Print()
	{
		Print(root, 0, 0);
	}

private:
	void Print(Node* node, int depth, int blackCount)
	{
		int i = 0;
		char c = 'X'; // child인지 아닌지
		int v = 0; // 부모의 data

		if (node == NULL || node == nil)
			return;

		if (node->Color == Colors::Black)
			blackCount++;

		if (node->P != NULL)
		{
			v = node->P->Data;

			if (node->P->L == node)
				c = 'L';
			else
				c = 'R';
		}

		for (i = 0; i < depth; i++)
			cout << " ";

		cout << node->Data << "-" << c << " ";
		cout << ((node->Color == Colors::Red) ? "Red" : "Black");
		cout << " [" << v << "] " << "//" << depth << endl;

		//if (node->L == nil && node->R == nil)
		//	cout << "-------------- " << blackCount << endl;

		Print(node->L, depth + 1, blackCount);
		Print(node->R, depth + 1, blackCount);
	}

private:
	Node* nil = new Node();

	struct Node
	{
		int Data;

		Node* P; // parent
		Node* L; // left
		Node* R; // right

		Colors Color;

		Node()
		{
			P = L = R = NULL;
			memset(&Data, 0, sizeof(int));

			Color = Colors::Black;
		}

		Node(int data) : P(NULL)
		{
			Data = data;
		}
	};

	Node* root;
};

void Print(int end)
{

	RedBlackTree* rbt = new RedBlackTree(1);
	for (int i = 2; i <= end; i++)
		rbt->Insert(i);

	cout << "-------" << end << "-------" << endl;

	rbt->Print();

	cout << endl;

	delete rbt;
}

void main()
{
	Print(2);
	Print(3);
	Print(4);
	Print(5);
	Print(6);
}