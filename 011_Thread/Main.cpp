#include <Windows.h>
#include <cstdio>
#include <thread>
using namespace std;

void Func()
{
	for (int i = 0; i < 1000; i++)
		printf("Func : %d\n", i);

	printf("Func ����\n");
}

void Func2()
{
	// ���� ���� �����ϸ� t1�� ���ᰡ �ȵ� t2�� ���ᰡ �ȵǼ� ������ ����
	//for (int i = 0; /*i < 1000*/; i++) {

	//	for (int j = 0; j < 100; j++) {}
	//	
	//	printf("Func2 : %d\n", i);
	//}

	for (int i = 0; i < 1000; i++) {
		Sleep(1000);
		printf("Func2 : %d\n", i);
	}

	printf("Func2 ����\n");
}

void main()
{
	//Func();
	//Func2();

	// �̷��� �ص� �Ȱ��� Func() ������ �����尡 �Ǿ��ؼ�
	//Func();
	//thread t2(Func2);
	//t2.join(); // �̰� ���;� ����ǰ� �������� �Ѿ �� ����

	////////////////////////////////////////

	thread t1(Func);
	thread t2(Func2);

	// t1.join(); // �̷��� ���� �׳� �Լ� ȣ���̶� �ٸ��ٰ� ����
	t2.join(); // �̰� ���;� ����ǰ� �������� �Ѿ �� ����
	t1.join(); // �̰� �ּ��ϸ� ���� ��

	// ���� ���� ȣ������� �� �ü������ �����
	// -> �ΰ��� ���ΰ��� �ݺ��ϰ� �Ϸ��°� ����ȭ��
}