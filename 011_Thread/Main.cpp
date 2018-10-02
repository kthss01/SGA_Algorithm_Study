#include <Windows.h>
#include <cstdio>
#include <thread>
using namespace std;

void Func()
{
	for (int i = 0; i < 1000; i++)
		printf("Func : %d\n", i);

	printf("Func 종료\n");
}

void Func2()
{
	// 무한 루프 돌게하면 t1이 종료가 안됨 t2가 종료가 안되서 멈추질 않음
	//for (int i = 0; /*i < 1000*/; i++) {

	//	for (int j = 0; j < 100; j++) {}
	//	
	//	printf("Func2 : %d\n", i);
	//}

	for (int i = 0; i < 1000; i++) {
		Sleep(1000);
		printf("Func2 : %d\n", i);
	}

	printf("Func2 종료\n");
}

void main()
{
	//Func();
	//Func2();

	// 이렇게 해도 똑같음 Func() 끝나고 스레드가 되야해서
	//Func();
	//thread t2(Func2);
	//t2.join(); // 이게 나와야 종료되고 다음으로 넘어갈 수 있음

	////////////////////////////////////////

	thread t1(Func);
	thread t2(Func2);

	// t1.join(); // 이렇게 쓰면 그냥 함수 호출이랑 다를바가 없음
	t2.join(); // 이게 나와야 종료되고 다음으로 넘어갈 수 있음
	t1.join(); // 이거 주석하면 오류 뜸

	// 누가 먼저 호출될지는 모름 운영체제에서 담당함
	// -> 두개가 서로간의 반복하게 하려는게 동기화임
}