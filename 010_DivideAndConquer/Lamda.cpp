#include <cstdio> 
#include <functional>
#include <array>
using namespace std;


class Add
{
public:
	int operator() (int a, int b) // 생성자 재정의 생성자 기호 -> 함수자
	{
		return a + b;
	}
};

int Add(int a, int b) 
{
	return a + b;
}

void main()
{
	// 함수자
	//printf("%d\n", Add()(1, 2));

	// 람다식
	//auto Add = [=](int a, int b)->int
	//{
	//	return a + b;
	//};
	//printf("%d\n", Add(1,2));

	// function
	//function<int(int, int)> add[2];

	//add[0] = function<int(int, int)>(Add);
	//add[1] = function<int(int, int)>(
	//	[](int a, int b)->int
	//	{
	//		return a + b;
	//	}
	//);

	//auto add2 = [](int a, int b)->int
	//{
	//	return a + b;
	//};

	//printf("%d \n", add[0](1, 2));
	//printf("%d \n", add[1](1, 2));
	//printf("%d \n", add2(1, 2));

	// array
	// iterator size 쓸 수 있음
	int temp = 0;
	array<int, 5> a = { 0,1,2,3,4 };
	for_each(a.begin(), a.end(), [&](int n) 
	{
		temp += n;
	});
	printf("%d\n", temp);
	
	for (int& b : a) {
		printf("%d\n", b);

		// &면 값 참조가 일어나서 바꿀 수 있음 아니면 값 복사
	}
}