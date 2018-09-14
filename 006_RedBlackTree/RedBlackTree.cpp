#include <iostream>
using namespace std;

// enum class class ���� �ҼӵȰŶ� ������ �ƴ�
enum class Color
{
	Red = 0, Black
};

struct Node
{
	Node* Parent;
	Node* Left, * Right;

	Color Color;
	int Data;
};

Node* Nil = new Node();

// parent ���Ե� ����� �θ�
void RotationRight(Node** root, Node* parent)
{
	// ���� �ڽ��� ������ �ڽĳ�� -> �θ� ����� ������ �ڽ�
	Node* leftChild = parent->Left;
	parent->Right = leftChild->Right;


	if (leftChild->Right != Nil)
		leftChild->Right->Parent = parent;

	leftChild->Parent = parent;

	
	if (parent->Parent == NULL) // �θ� ��Ʈ��� ���� �ڽ��� ��Ʈ�� -> ��ȸ�� �غ�
	{
		*root = leftChild;
	}
	else
	{
		if (parent == parent->Parent->Left) // ���� �ڽ� ��带 �θ� �ִ� ������ �ø�
			parent->Parent->Left = leftChild;
		else
			parent->Parent->Right = leftChild;
	}

	leftChild->Right = parent;
	parent->Parent = leftChild;
}

void Insert(Node** tree, Node* node)
{
	InsertNode(tree, node); // ��� ����

	node->Color = Color::Red;
	node->Left = Nil;
	node->Right = Nil;

	// �̶��� ��������
	Rebuild(tree, node);
}

void main()
{
	Nil->Left = Nil->Right = Nil->Parent = NULL;
	Nil->Color = Color::Black;
	Nil->Data = 0;


}