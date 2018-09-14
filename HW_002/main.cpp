// ���� -> ����, ���� -> ������ �����ϱ�
/*
	stack �̿��ؼ� ���ϱ�
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;


stack<char> st;
vector<char> op;

vector<char> ans;

int priority(char op) {
	switch (op)
	{
		case '(': case ')': return 0;
		case '+': case '-': return 1;
		case '*': case '/': return 2;
	}
	return -1;
}

int main() {
	string str = "((1+2)*(3-2)/2)";

	// ���� -> ����
	{
		for (int i = 0; i < str.length(); i++) {
			char symbol = str[i];

			switch (symbol)
			{
				// ���� ��ȣ
				case '(':
					st.push(symbol);
					break;

				case ')':
				{
					char temp = st.top();
					st.pop();
					while (temp != '(') {
						ans.push_back(temp);
						temp = st.top();
						st.pop();
					}

				}
				break;

				case '+': case '-': case '*': case '/':
				{
					while (!st.empty() && priority(st.top()) >= priority(symbol)) {
						char temp = st.top();
						st.pop();
						ans.push_back(temp);
					}
					st.push(symbol);
				}
				break;

				default:
					ans.push_back(symbol);
					break;
			}
		}
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i];
		cout << endl;
	}

	str.clear();
	ans.clear();

	// ���� -> ����
	{

	}
	
	return 0;
}