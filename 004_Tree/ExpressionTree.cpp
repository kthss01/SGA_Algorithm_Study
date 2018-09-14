#include <iostream>
#include <iomanip>
using namespace std;

class ExpressionTree
{
public:
	struct Node;

	ExpressionTree(char* expression)
	{
		Build(expression, &root);
	}
	~ExpressionTree()
	{
		DestroyNode(root);
	}

	void PrintOrder()
	{
		PrintInOrder(root);

		cout << endl;
	}

	void Evaluate()
	{
		cout << Evaluate(root) << endl;
	}

private:
	Node* CreateNode(char data)
	{
		Node* node = new Node(data);
		node->Left = NULL;
		node->Right = NULL;

		return node;
	}

	void DestroyNode(Node* node) {
		if (node == NULL) return;

		DestroyNode(node->Left);
		DestroyNode(node->Right);

		delete node;
	}

	void Build(char* expression, Node** node)
	{
		//Node* node = NULL;
		int len = strlen(expression);
		char token = expression[len - 1];
		expression[len - 1] = '\0';

		switch (token)
		{
		case '+': case '-': case '*': case '/':
		{
			(*node) = CreateNode(token);
			
			// right부터 들어감 후위순회 역이라
			Build(expression, &(*node)->Right);
			Build(expression, &(*node)->Left);
		}
		break;

		default:
			(*node) = CreateNode(token);
			break;
		}
	}

	int Evaluate(Node* node)
	{
		char temp[2];

		int left = 0, right = 0, result = 0;
		if (node == NULL) return 0;

		switch (node->Data)
		{
			case '+': case '-': case '*': case '/':
			{
				left = Evaluate(node->Left);
				right = Evaluate(node->Right);

				if (node->Data == '+') result = left + right;
				if (node->Data == '-') result = left - right;
				if (node->Data == '*') result = left * right;
				if (node->Data == '/') result = left / right;
				return result;
			}
			break;

			default:
			{
				memset(temp, 0, sizeof(char) * 2);
				temp[0] = node->Data;

				//const char* a = static_cast<char *> (&temp[0]); // 정적변수에 대한 형변환이 일어나지 않으면 a null 나옴
				result = atoi(&temp[0]);
				return result;
			}
			break;
		}
	}

	void PrintInOrder(Node* node)
	{
		if (node == NULL) return;

		if(node->Left != NULL) cout << "(";
		PrintInOrder(node->Left);

		cout << node->Data;

		PrintInOrder(node->Right);
		if(node->Right != NULL) cout << ")";
	}

public:
	struct Node
	{
		Node* Left;
		Node* Right;
	
		char Data;

		Node(char data) : Data(data) {}
	};

private:
	Node* root;
};

void main()
{

	//string data = "12+43-*";
	char data[20] = "12+43-*";

	ExpressionTree* tree = new ExpressionTree(data);

	//tree->Build(data, &root);

	tree->PrintOrder();
	tree->Evaluate();

	delete tree;
}