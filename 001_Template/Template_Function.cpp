#include <iostream>
using namespace std;

template <typename T> void Print(T data)
{
	cout << "�Ϲ� �Լ� : " << data << endl;
}

template <typename T> void Print(T* data)
{
	cout << "�Ϲ� �Լ� : " << *data << endl;
}

// ���ø� Ư��ȭ �ϴ¹�
template<> void Print(int data)
{
	cout << "Ư��ȭ �Լ� : " << data << endl;
}



void main()
{
	int i = 10;
	char c = 20;

	//// Ư��ȭ �̷������ ������ �̷��� �������
	//Print<int>(i);
	//Print<int>(&i);

	Print(20);
}