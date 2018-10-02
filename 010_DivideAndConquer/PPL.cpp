// 작업단위 task
#include <cstdio>
#include <ppl.h> // 비주얼 스튜디오 2013 이후로 가능
#include <ppltasks.h>
#include <Windows.h>

using namespace std;
using namespace concurrency; // 병행성

//void main()
//{
//	// auto 변수 컴파일시에 자동으로 변수 맞춰줌 지역변수에서만 사용가능 
//	// auto* 는 불가능함
//
//	//auto task_handle = make_task()
//
//	// task 호출하기 전까지 실행안됨
//	auto task = make_task([]() 
//	{ 
//		printf("task1\n"); 
//	});
//
//	// 만들고 호출됨
//	auto task2 = create_task([]()
//	{
//		printf("task2\n");
//	});
//	// 바로 호출되지 않으려면
//	task2.wait(); // 모든 결과가 나타나기까지 기다리라는거 -> join이랑 같은거라고 생각하면 됨
//
//	task();
//}

//void main()
//{
//	// task group으로 관리할때는 make만 씀 create 만들자마자 call 되서
//	auto task0 = make_task([]() {printf("0"); });
//	auto task1 = make_task([]() {printf("1"); });
//	auto task2 = make_task([]() {printf("2"); });
//
//	// 순차적으로 나옴
//	structured_task_group group;
//	group.run(task0);
//	group.run(task1);
//	group.run_and_wait(task2);
//}

// 비동기
//void main()
//{
//	// 최대 9개만 가능 
//	// group으로 묶어서 쓸 수 있음
//	// group도 최대 9개인가 그렇다고 하심
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

	printf("%d, %d\n", temp, temp2); // 합이 다룰 수 있음 나중에 설명해주실꺼
	printf("%f, %f\n", total1, total2);
}