#include <cstdio>
#include <algorithm>

int CountCoins(int amount, int coin)
{
	int count = 0;
	int currentAmount = amount;

	while (currentAmount >= coin) // 실행 가능성 검사
	{
		count++;
		currentAmount = currentAmount - coin;
	}

	return count;
}

void Change(int price, int pay, int* coins, int* change, int size)
{
	int amount = pay - price;

	for (int i = 0; i < size; i++) // 해 선택
	{
		change[i] = CountCoins(amount, coins[i]);

		amount = amount - (coins[i] * change[i]); // 해 검증
	}
}

void Print(int* coins, int* change, int size)
{
	for (int i = 0; i < size; i++)
		printf("%8d원 : %d개\n", coins[i], change[i]);
}

int Compare(const void* a, const void* b)
{
	if (*(int *)a < *(int *)b)
		return 1;
	else if (*(int *)a == *(int *)b)
		return 0;
	else
		return -1;
}

void main()
{
	int unitCount = 0;

	printf("동전의 가짓수 입력 : ");
	scanf("%d", &unitCount);

	int* coins = new int[unitCount];
	int* change = new int[unitCount];

	for (int i = 0; i < unitCount; i++) {
		printf("[%d] 번째 동전의 단위를 입력 : ", i);
		scanf("%d", &coins[i]);
	}

	qsort(coins, unitCount, sizeof(int), Compare);

	int price;
	printf("물건 가격을 입력하세요 : ");
	scanf("%d", &price);

	int pay;
	printf("손님이 지불한 금액 : ");
	scanf("%d", &pay);

	Change(price, pay, coins, change, unitCount);

	Print(coins, change, unitCount);

	delete change;
	delete coins;
}