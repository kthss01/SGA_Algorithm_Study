#include <iostream>
//#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

struct Data
{
	int Number;
	float Score;
};

#define MAX 10000000

Data datas[MAX];

Data* BinarySearch(Data* data, int size, float target, OUT int& count)
{
	int left, right, mid;

	count = 0;
	left = 0; right = size - 1;

	while (left <= right)
	{
		mid = (left + right) / 2;

		if (target == datas[mid].Score)
			return &datas[mid];
		else if (target > datas[mid].Score)
			left = mid + 1;
		else
			right = mid - 1;

		count++;
	}
	return NULL;
}

int CompareScore(const void* _c1, const void* _c2)
{
	Data* c1 = (Data*)_c1;
	Data* c2 = (Data*)_c2;

	if (c1->Score > c2->Score)
		return 1;
	else if (c1->Score > c2->Score)
		return -1;

	return 0;
}

float Random(float r1, float r2)
{
	float random = ((float)rand()) / (float)RAND_MAX; // RAND_MAX 32767
	float diff = r2 - r1;
	float val = random * diff;

	return r1 + val;
}

void main()
{
	srand((unsigned int)time(NULL));

	const float Find = 322554.654f;

	for (int i = 0; i < MAX; i++)
	{
		datas[i].Number = i + 1;
		datas[i].Score = Random(0.0f, 10000.0f);

		if (datas[i].Score == Find)
			datas[i].Score = Random(0.0f, 10000.0f);

		if (i == 8262000)
			datas[i].Score = Find;
	}

	//DWORD start = GetTickCount();
	//DWORD end;

	// frequency 빈도수

	qsort(datas, MAX, sizeof(Data), CompareScore);

	__int64 tick;
	QueryPerformanceCounter((LARGE_INTEGER *)&tick);
	__int64 start;
	QueryPerformanceCounter((LARGE_INTEGER *)&start); // micro second

	for (int i = 0; i < MAX; i++)
	{
		if (datas[i].Score == Find)
			break;
	}

	__int64 end;
	QueryPerformanceCounter((LARGE_INTEGER *)&end);

	float running = (float)((double)(end - start) / tick * 1000); // 초로 보려고 1000 곱한거
	cout << start << " / " << end << " / " << running << endl;

	QueryPerformanceCounter((LARGE_INTEGER *)&start); // micro second
	Data* found;
	int count = 0; 
	{	
		found = BinarySearch(datas, MAX, Find, count);
	}
	QueryPerformanceCounter((LARGE_INTEGER *)&end);
	running = (float)((double)(end - start) / tick * 1000);
	cout << start << " / " << end << " / " << running << endl;
	cout << count << endl;

}