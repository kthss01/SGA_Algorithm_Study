#include <iostream>
using namespace std;

template <typename T> void Print(T data)
{
	cout << "일반 함수 : " << data << endl;
}

template <typename T> void Print(T* data)
{
	cout << "일반 함수 : " << *data << endl;
}

// 템플릿 특수화 하는법
template<> void Print(int data)
{
	cout << "특수화 함수 : " << data << endl;
}



void main()
{
	int i = 10;
	char c = 20;

	//// 특수화 이루어지지 않으면 이렇게 써줘야함
	//Print<int>(i);
	//Print<int>(&i);

	Print(20);
}