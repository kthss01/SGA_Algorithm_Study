// pow 실제 이렇게 됨

#include <cstdio>
#include <cmath>

unsigned int Power(int base, int exponent) {
	if (base == 0)
		return 0;

	if (exponent == 1)
		return base;
	else if (exponent == 0)
		return 1;

	if (exponent % 2 == 0)
	{
		unsigned int temp = Power(base, exponent / 2);

		return temp * temp;
	}
	else
	{
		unsigned int temp = Power(base, (exponent - 1) / 2);
		return temp * temp * base;
	}
}

void main()
{
	int base = 2;
	int exponent;

	while (true)
	{
		printf("exponenet : ");
		scanf("%d", &exponent);

		printf("Power : %d\n", Power(base, exponent));
	}

	//int temp = pow(2, -1);
}