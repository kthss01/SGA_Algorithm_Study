#include <cstdio>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

int Selection(vector< pair<int,int> >& order)
{
	// earliest : ���ǽ��� �������� �ִܽð�
	// selected : ���ݱ��� ���ǽ��� ���� ��
	int earliest = 0, selected = 0;
	for (int i = 0; i < order.size(); i++) // �� ����
	{
		int begin = order[i].second;
		int end = order[i].first;

		if (earliest <= begin) // ���� ���ɼ� ����
		{
			earliest = end; // �� ����
			++selected;
		}
	}

	return selected;
}

void main()
{
	int count = 20;
	srand(time(0));

	vector< pair<int, int> > order;
	for (int i = 0; i < count; i++)
	{
		int start = rand() % 20 + 1;
		int end = rand() % 10 + 1;
		end = start + end;

		order.push_back(make_pair(end, start));
	}
	sort(order.begin(), order.end());

	count = Selection(order);

	for (pair<int, int>& temp : order)
		printf("start : %d, end : %d\n", temp.second, temp.first);

	printf("�� ���� Ƚ�� : %d\n", count);
	
}