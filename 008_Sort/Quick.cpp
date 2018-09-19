#include <iostream>
#include <vector>
using namespace std;

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int Partition(vector<int>& data, int left, int right)
{
	int first = left;
	int pivot = data[first];

	++left;
	while (left <= right)
	{
		while (data[left] <= pivot && left < right)
			++left;
		while (data[right] >= pivot && left <= right)
			--right;

		if (left < right)
			Swap(&data[left], &data[right]);
		else
			break;
	}

	Swap(&data[first], &data[right]);

	return right;
}

void Sort(vector<int>& data, int left, int right)
{
	if (left < right)
	{
		for (size_t i = 0; i < data.size(); i++)
			cout << data[i] << " ";
		cout << endl;

		int index = Partition(data, left, right);

		Sort(data, left, index - 1);
		Sort(data, index + 1, right);

		//for (size_t i = 0; i < data.size(); i++)
		//	cout << data[i] << " ";
		//cout << endl << endl;
	}
}

int Compare(const void* v1, const void* v2)
{
	// 리턴값이 0 보다 작으면 v1 < v2
	// 반대면 v1 > v2
	// 같으면 v1 == v2
	int * temp1 = (int*)v1;
	int * temp2 = (int*)v2;

	if (*temp1 > *temp2)
		return 1;
	else if (*temp1 < *temp2)
		return -1;

	return 0;
}

void main()
{
	vector<int> vec;
	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(1);
	vec.push_back(5);

	//Sort(vec, 0, vec.size() - 1);

	qsort((void*)&vec[0], vec.size(), sizeof(int), Compare);

	cout << endl << "최종 결과" << endl;
	for (size_t i = 0; i < vec.size(); i++)
		cout << vec[i] << " ";
	cout << endl;
}