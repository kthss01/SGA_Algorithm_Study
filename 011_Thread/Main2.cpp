#include <cstdio>
#include <thread>
#include <mutex>
#include <Windows.h>
using namespace std;

int value = 10;
mutex m;

void Func()
{
	m.lock();
	for (int i = 0; i < 10; i++)
	{
		printf("Func : %d\n", value);
		
		value++;
		Sleep(1);
	}
	m.unlock();
}

void Func2()
{
	m.lock();
	for (int i = 0; i < 10; i++)
	{
		printf("Func2 : %d\n", value);

		value++;
		Sleep(1);
	}
	m.unlock();
}

void main()
{
	thread t(Func);
	thread t2(Func2);

	t2.join();
	t.join();
}