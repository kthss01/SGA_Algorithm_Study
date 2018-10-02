// �۾����� task
#include <cstdio>
#include <ppl.h> // ���־� ��Ʃ��� 2013 ���ķ� ����
#include <ppltasks.h>
#include <Windows.h>

using namespace std;
using namespace concurrency; // ���༺

//void main()
//{
//	// auto ���� �����Ͻÿ� �ڵ����� ���� ������ �������������� ��밡�� 
//	// auto* �� �Ұ�����
//
//	//auto task_handle = make_task()
//
//	// task ȣ���ϱ� ������ ����ȵ�
//	auto task = make_task([]() 
//	{ 
//		printf("task1\n"); 
//	});
//
//	// ����� ȣ���
//	auto task2 = create_task([]()
//	{
//		printf("task2\n");
//	});
//	// �ٷ� ȣ����� ��������
//	task2.wait(); // ��� ����� ��Ÿ������� ��ٸ���°� -> join�̶� �����Ŷ�� �����ϸ� ��
//
//	task();
//}

//void main()
//{
//	// task group���� �����Ҷ��� make�� �� create �����ڸ��� call �Ǽ�
//	auto task0 = make_task([]() {printf("0"); });
//	auto task1 = make_task([]() {printf("1"); });
//	auto task2 = make_task([]() {printf("2"); });
//
//	// ���������� ����
//	structured_task_group group;
//	group.run(task0);
//	group.run(task1);
//	group.run_and_wait(task2);
//}

// �񵿱�
//void main()
//{
//	// �ִ� 9���� ���� 
//	// group���� ��� �� �� ����
//	// group�� �ִ� 9���ΰ� �׷��ٰ� �Ͻ�
//	parallel_invoke(
//		[]() { printf("0"); },
//		[]() { printf("1"); },
//		[]() { printf("2"); }
//	);
//}

void GetTime(__int64* val)
{
	QueryPerformanceCounter((LARGE_INTEGER *)val);
}

float GetTotal(__int64 start, __int64 end, __int64 tick)
{
	return ((float)(end - start) / tick * 1000.0f);
}

#define MAX 1000000
void main()
{
	__int64 tick, start, end;
	QueryPerformanceFrequency((LARGE_INTEGER *)&tick);

	GetTime(&start);
	int temp = 0;
	for (int i = 0; i < MAX; i++)
		temp += i;
	GetTime(&end);
	float total1 = GetTotal(start, end, tick);

	GetTime(&start);
	int temp2 = 0;
	parallel_for(0, MAX - 1, 1, [&](int i)
	{
		temp2 += i;
	});
	GetTime(&end);
	float total2 = GetTotal(start, end, tick);

	printf("%d, %d\n", temp, temp2); // ���� �ٷ� �� ���� ���߿� �������ֽǲ�
	printf("%f, %f\n", total1, total2);
}