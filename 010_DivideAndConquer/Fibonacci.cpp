#include <cstdio>
#include <Windows.h>

struct Matrix
{
	ULONG Data[2][2];
};

// const 가능 한거 맨뒤는 멤버일때만 가능
// 엔진에선 철두철미함 클라이언트가 바뀌어선 안되서
//const Matrix const & const Multiply(const Matrix const & const a, const Matrix& b) //const
Matrix & Multiply(Matrix & a, Matrix & b)
{
	Matrix c;

	c.Data[0][0] = a.Data[0][0] * b.Data[0][0] + a.Data[0][1] * b.Data[1][0];
	c.Data[0][1] = a.Data[0][0] * b.Data[1][0] + a.Data[0][1] * b.Data[1][1];

	c.Data[1][0] = a.Data[1][0] * b.Data[0][0] + a.Data[1][1] * b.Data[1][0];
	c.Data[1][1] = a.Data[1][0] * b.Data[1][0] + a.Data[1][1] * b.Data[1][1];

	return c;
}

Matrix Power(Matrix a, int n)
{
	printf("%d ", n);

	if (n <= 1)
		return a;

	a = Power(a, n / 2);
	a = Multiply(a, a);

	// n이 홀수면
	if (n & 1)
	{
		Matrix b;
		b.Data[0][0] = 1; b.Data[0][1] = 1;
		b.Data[1][0] = 1; b.Data[1][1] = 0;

		a = Multiply(a, b);
	}

	return a;
}

ULONG Fibonacci(int n)
{
	Matrix a;
	a.Data[0][0] = 1; a.Data[0][1] = 1;
	a.Data[1][0] = 1; a.Data[1][1] = 0;

	a = Power(a, n);

	return a.Data[0][1];
}

// wmain wchar 쓰겠다는거
// tmain tchar 쓰겠다는거
void main()
{
	int n = 10;

	ULONG r = Fibonacci(n);

	printf("\nFibonacci(%d) : %lu\n", n, r);
}