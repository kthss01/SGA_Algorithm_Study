#include <iostream>
#include <vector>
using namespace std;

void Sort(vector<int>& data)
{
	int value = 0;

	for (size_t i = 1; i < data.size(); i++)
	{
		if (data[i - 1] <= data[i])
			continue;

		value = data[i];

		for (size_t k = 0; k < i; k++)
		{
			if (data[k] > value)
			{
				memmove(&data[k + 1], &data[k], sizeof(int) * (i - k));
				data[k] = value;

				break;
			}
		} // for(k)

		for (int k = 0; k < data.size(); k++)
			cout << data[k] << " ";
		cout << endl;

	} // for(i)
}

void main()
{
	vector<int> vec;

	vec.push_back(6);
	vec.push_back(4);
	vec.push_back(2);
	vec.push_back(3);

	Sort(vec);

	cout << endl;
	cout << "최종 결과" << endl;
	for (int k = 0; k < vec.size(); k++)
		cout << vec[k] << " ";
	cout << endl;
}