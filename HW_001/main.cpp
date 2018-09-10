#include <iostream>
using namespace std;

template<typename T>
struct TreeNode
{
	T Value;
	TreeNode<T>* left, *right;

	TreeNode(T value) : Value(value), left(NULL), right(NULL) {}
};

template<typename T>
class Tree
{
public:
	Tree() : root(NULL) {}

public:
	void Insert(T value)
	{
		Insert(root, value);
	}

	void Remove(T value)
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
	void Insert(TreeNode<T>*& node, T value)
	{
		if (node == NULL)
			node = new TreeNode<T>(value);
		else if (value > node->Value)
			Insert(node->right, value);
		else if (value < node->Value)
			Insert(node->left, value);
	}

	void Remove(TreeNode<T>*& node, T value)
	{
		TreeNode<T>* remove = NULL;

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

	void PreOrder(TreeNode<T>* node)
	{
		if (node != NULL)
		{
			cout << node->Value << " ";
			PreOrder(node->left);
			PreOrder(node->right);
		}
	}

	void InOrder(TreeNode<T>* node)
	{
		if (node != NULL)
		{
			InOrder(node->left);
			cout << node->Value << " ";

			InOrder(node->right);
		}
	}

	void PostOrder(TreeNode<T>* node)
	{
		if (node != NULL)
		{
			PostOrder(node->left);
			PostOrder(node->right);
			cout << node->Value << " ";
		}
	}

private:
	TreeNode<T>* root;

};

int main() {

	Tree<int>* tree = new Tree<int>();

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

	delete tree;

	cout << "\n///////////////////////////////////////////////\n";

	Tree<char>* charTree = new Tree<char>();

	for (int i = 0; i < 26; i++)
		charTree->Insert(i + 'a');

	cout << endl << endl;
	cout << "중위순회 : ";
	charTree->InOrder();
	cout << endl;

	charTree->Remove('c');

	cout << endl << endl;
	cout << "중위순회 : ";
	charTree->InOrder();
	cout << endl;

	return 0;
}