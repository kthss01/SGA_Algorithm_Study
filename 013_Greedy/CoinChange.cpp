#include <cstdio>
#include <algorithm>

int CountCoins(int amount, int coin)
{
	int count = 0;
	int currentAmount = amount;

	while (currentAmount >= coin) // ���� ���ɼ� �˻�
	{
		count++;
		currentAmount = currentAmount - coin;
	}

	return count;
}

void Change(int price, int pay, int* coins, int* change, int size)
{
	int amount = pay - price;

	for (int i = 0; i < size; i++) // �� ����
	{
		change[i] = CountCoins(amount, coins[i]);

		amount = amount - (coins[i] * change[i]); // �� ����
	}
}

void Print(int* coins, int* change, int size)
{
	for (int i = 0; i < size; i++)
		printf("%8d�� : %d��\n", coins[i], change[i]);
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

	printf("������ ������ �Է� : ");
	scanf("%d", &unitCount);

	int* coins = new int[unitCount];
	int* change = new int[unitCount];

	for (int i = 0; i < unitCount; i++) {
		printf("[%d] ��° ������ ������ �Է� : ", i);
		scanf("%d", &coins[i]);
	}

	qsort(coins, unitCount, sizeof(int), Compare);

	int price;
	printf("���� ������ �Է��ϼ��� : ");
	scanf("%d", &price);

	int pay;
	printf("�մ��� ������ �ݾ� : ");
	scanf("%d", &pay);

	Change(price, pay, coins, change, unitCount);

	Print(coins, change, unitCount);

	delete change;
	delete coins;
}