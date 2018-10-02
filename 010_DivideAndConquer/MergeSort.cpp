#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <thread>
using namespace std;

void Merge(int* data, int start, int middle, int end)
{
	int left = start;
	int right = middle + 1;

	int destIndex = 0; // 저장할 공간의 번호
	int* dest = new int[end - start + 1];

	while (left <= middle && right <= end)
	{
		if (data[left] < data[right])
		{
			dest[destIndex] = data[left];
			left++;
		}
		else
		{
			dest[destIndex] = data[right];
			right++;
		}

		destIndex++;
	}

	while (left <= middle)
		dest[destIndex++] = data[left++];

	while (right <= end)
		dest[destIndex++] = data[right++];

	destIndex = 0;
	for (int i = start; i <= end; i++)
		data[i] = dest[destIndex++];

	delete[] dest;
}

void MergeSort(int* data, int start, int end)
{
	if (end - start < 1) return;

	int middle = (start + end) / 2;

	MergeSort(data, start, middle);
	MergeSort(data, middle + 1, end);

	Merge(data, start, middle, end);
}

void MergeSortWithThread(int* data, int start, int end)
{
	if (end - start < 1) return;

	int middle = (start + end) / 2;

	thread t1(MergeSort, data, start, middle);
	thread t2(MergeSort, data, middle + 1, end);

	t1.join();
	t2.join();

	Merge(data, start, middle, end);
}

void GetTime(__int64* val)
{
	QueryPerformanceCounter((LARGE_INTEGER *)val);
}

float GetTotal(__int64 start, __int64 end, __int64 tick)
{
	return ((float)(end - start) / tick * 1000.0f);
}

#define MAX_LENGTH 1000000 // 백만
int arr[MAX_LENGTH], arr2[MAX_LENGTH];
void main()
{
	srand((UINT)time(NULL));


	for (int i = 0; i < MAX_LENGTH; i++)
		arr[i] = rand() % 1000;

	memcpy(arr2, arr, sizeof(int) * MAX_LENGTH);

	__int64 tick, start, end;
	QueryPerformanceFrequency((LARGE_INTEGER *)&tick);

	GetTime(&start);
	{
		MergeSort(arr, 0, MAX_LENGTH - 1);
	}
	GetTime(&end);
	float sort1 = GetTotal(start, end, tick);

	GetTime(&start);
	{
		thread t(MergeSortWithThread, arr2, 0, MAX_LENGTH - 1);
		t.join();
	}
	GetTime(&end);
	float sort2 = GetTotal(start, end, tick);

	//for (int i = 0; i < 100; i++)
	//{
	//	GetTime(&start);
	//	{
	//		MergeSortWithThread(arr, 0, MAX_LENGTH - 1);
	//	}
	//	GetTime(&end);
	//	float sort2 = GetTotal(start, end, tick);

	//	if (i % 10 == 0 && i != 0)
	//		printf("\n");

	//	printf("%f ", sort2);
	//}


	//for (int i = 0; i < MAX_LENGTH; i++)
	//{
	//	if (i % 10 == 0 && i != 0) printf("\n");
	//	printf("%03d ", arr[i]);
	//}
	//printf("\n");

	printf("병합 1 : %f\n", sort1);
	printf("병합 2 : %f\n", sort2);
}