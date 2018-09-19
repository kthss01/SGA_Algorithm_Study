#include <iostream>
#include <assert.h>
using namespace std;

class RedBlackTree
{
private:
	struct Node;
	enum class Colors { Red = 0, Black, };

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

		node->Color = Colors::Red;
		node->L = nil;
		node->R = nil;

		Print(root, 0, 0);

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
			bool bLeft = false;
			bLeft = node->P == node->P->P->L;

			Node* uncle = (bLeft == true) ? node->P->P->R : node->P->P->L;
			// 삼촌이 레드일때
			if (uncle->Color == Colors::Red)
			{
				node->P->Color = Colors::Black;
				uncle->Color = Colors::Black;
				node->P->P->Color = Colors::Red;

				node = node->P->P;

				continue;
			}

			// 삼촌이 블랙
			// 내 부모가 Left Child인지
			if (bLeft == true)
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
			// 내 부모가 Right Child인지
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
		}//while(node)

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
		char c = 'X';
		int v = 0;

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
			cout << "  ";

		cout << node->Data << "-" << c << " ";
		cout << ((node->Color == Colors::Red) ? "Red" : "Black");
		cout << " [" << v << "] " << "//" << depth << endl;

		/*if (node->L == nil && node->R == nil)
		cout << "----------- " << blackCount << endl;*/

		Print(node->L, depth + 1, blackCount);
		Print(node->R, depth + 1, blackCount);
	}

private:
	Node* nil = new Node();

	struct Node
	{
		int Data;

		Node* P;
		Node* L;
		Node* R;

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

	cout << "-----" << end << "-----" << endl;
	for (int i = 2; i <= end; i++)
		rbt->Insert(i);

	rbt->Print();
	cout << endl;
	delete rbt;
}

void main()
{
	/*Print(2);
	Print(3);
	Print(4);
	Print(5);
	Print(6);*/

	RedBlackTree* rbt = new RedBlackTree(1);
	rbt->Insert(2);
	rbt->Insert(3);
	rbt->Insert(4);

	//RedBlackTree* rbt = new RedBlackTree(5);
	//rbt->Insert(4);
	//rbt->Insert(3);

	rbt->Print();
}