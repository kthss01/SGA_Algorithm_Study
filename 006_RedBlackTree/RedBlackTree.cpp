#include <iostream>
using namespace std;

// enum class class 내에 소속된거라 전역이 아님
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

// parent 삽입될 노드의 부모
void RotationRight(Node** root, Node* parent)
{
	// 왼쪽 자식의 오른쪽 자식노드 -> 부모 노드의 오른쪽 자식
	Node* leftChild = parent->Left;
	parent->Right = leftChild->Right;


	if (leftChild->Right != Nil)
		leftChild->Right->Parent = parent;

	leftChild->Parent = parent;

	
	if (parent->Parent == NULL) // 부모가 루트라면 왼쪽 자식을 루트로 -> 우회전 준비
	{
		*root = leftChild;
	}
	else
	{
		if (parent == parent->Parent->Left) // 왼쪽 자식 노드를 부모가 있던 곳으로 올림
			parent->Parent->Left = leftChild;
		else
			parent->Parent->Right = leftChild;
	}

	leftChild->Right = parent;
	parent->Parent = leftChild;
}

void Insert(Node** tree, Node* node)
{
	InsertNode(tree, node); // 노드 삽입

	node->Color = Color::Red;
	node->Left = Nil;
	node->Right = Nil;

	// 이때가 검증절차
	Rebuild(tree, node);
}

void main()
{
	Nil->Left = Nil->Right = Nil->Parent = NULL;
	Nil->Color = Color::Black;
	Nil->Data = 0;


}