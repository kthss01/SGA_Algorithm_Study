#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode
{
	int Value;
	TreeNode* left, *right;

	TreeNode(int value) : Value(value), left(NULL), right(NULL) {}
};

class Tree
{
public:
	Tree() : root(NULL) {}

public:
	void Insert(int value)
	{
		Insert(root, value);
	}

	void Remove(int value)
	{
		Remove(root, value);
	}

	void PreOrder() {
		PreOrder(root);
	}

	void InOrder() {
		InOrder(root);
	}

	void PostOrder() {
		PostOrder(root);
	}

	void PrintStack() {
		while (stack.empty() == false)
		{
			cout << stack.top() << " ";
			stack.pop();
		}
	}

	void PrintQueue() {
		while (queue.empty() == false)
		{
			cout << queue.front() << " ";
			queue.pop();
		}
	}

private:
	void Insert(TreeNode*& node, int value)
	{
		if (node == NULL)
			node = new TreeNode(value);
		else if (value > node->Value)
			Insert(node->right, value);
		else if (value < node->Value)
			Insert(node->left, value);
	}

	void Remove(TreeNode*& node, int value)
	{
		TreeNode* remove = NULL;

		if (node == NULL)
			return;

		if (value > node->Value)
			Remove(node->right, value);
		else if (value < node->Value)
			Remove(node->left, value);
		else
		{
			// no child
			if (node->left == NULL && node->right == NULL)
			{
				delete node;
				node = NULL;
			}
			else if (node->left == NULL)
			{
				remove = node;
				node = node->right;

				delete remove;
			}

			else if (node->right == NULL)
			{
				remove = node;
				node = node->left;

				delete remove;
			}
			// child 2
			else
			{
				remove = node->right;
				// 최소값 찾기
				while (remove->left != NULL)
					remove = remove->left;

				int minimum = remove->Value;
				Remove(root, minimum);
				node->Value = minimum;
			}

		}
	}

	void PreOrder(TreeNode* node)
	{
		if (node != NULL)
		{
			cout << node->Value << " ";
			PreOrder(node->left);
			PreOrder(node->right);
		}
	}

	void InOrder(TreeNode* node)
	{
		if (node != NULL)
		{
			InOrder(node->left);
			cout << node->Value << " ";

			stack.push(node->Value);
			queue.push(node->Value);

			InOrder(node->right);
		}
	}

	void PostOrder(TreeNode* node)
	{
		if (node != NULL)
		{
			PostOrder(node->left);
			PostOrder(node->right);
			cout << node->Value << " ";
		}
	}

private:
	TreeNode* root;
	stack<int> stack;
	queue<int> queue;
};

void main()
{
	Tree* tree = new Tree();

	tree->Insert(10);
	tree->Insert(20);
	tree->Insert(5);
	tree->Insert(3);
	tree->Insert(9);
	tree->Insert(16);
	tree->Insert(18);
	tree->Insert(13);
	tree->Insert(8);

	cout << endl << endl;
	cout << "전위순회 : ";
	tree->PreOrder();
	cout << endl;

	cout << endl << endl;
	cout << "중위순회 : ";
	tree->InOrder();
	cout << endl;

	cout << endl << endl;
	cout << "후위순회 : ";
	tree->PostOrder();
	cout << endl;

	cout << endl << endl;
	cout << "스택 출력 : ";
	tree->PrintStack();

	cout << endl << endl;
	cout << "큐 출력 : ";
	tree->PrintQueue();

	cout << endl << endl;
	cout << "중위순회 : ";
	tree->InOrder();
	cout << endl;

	tree->Remove(13);

	cout << endl << endl;
	cout << "중위순회 : ";
	tree->InOrder();
	cout << endl;

	delete tree;
}