#include <cstdio>
#include <Windows.h>

ULONG Fibonacci(int n)
{
	if (n == 0 || n == 1)
		return n;

	ULONG* table = new ULONG[n + 1];

	table[0] = 0;
	table[1] = 1;

	for (int i = 2; i <= n; i++)
		table[i] = table[i - 1] + table[i - 2];

	ULONG result = table[n];

	delete[] table;

	return result;
}

void main()
{
	int n = 10;
	ULONG r = Fibonacci(n);

	printf("Fibonacci(%d) : %lu\n", n, r);
}