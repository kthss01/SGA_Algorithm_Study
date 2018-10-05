#include <cstdio>
#include <string>
using namespace std;

struct LCSTable
{
	int** Data;
};

int LCS(char* x, char* y, int i, int j, LCSTable* table)
{
	if (i == 0 || j == 0)
	{
		table->Data[i][j] = 0;

		return table->Data[i][j];
	}
	else if (x[i - 1] == y[j - 1])
	{
		table->Data[i][j] = LCS(x, y, i - 1, j - 1, table) + 1;

		return table->Data[i][j];
	}
	else {
		int a = LCS(x, y, i - 1, j, table);
		int b = LCS(x, y, i, j - 1, table);

		if (a > b)
			table->Data[i][j] = a;
		else
			table->Data[i][j] = b;

		return table->Data[i][j];
	}
}

void Print(LCSTable* table, char* x, char* y, int lenX, int lenY)
{
	printf("%4s", "");

	for (int i = 0; i < lenY + 1; i++)
		printf("%c ", y[i]);
	printf("\n");

	for (int i = 0; i < lenX + 1; i++)
	{
		if (i == 0)
			printf("%2s", "");
		else
			printf("%-2c", x[i - 1]);

		for (int j = 0; j < lenY + 1; j++)
			printf("%d ", table->Data[i][j]);

		printf("\n");
	}
}

void main()
{
	char* x = "GOOD MORNING.";
	char* y = "GUTEN MORGEN.";

	int lenX = strlen(x);
	int lenY = strlen(y);

	LCSTable table;
	table.Data = new int*[lenX + 1];

	for (int i = 0; i < lenX + 1; i++) {
		table.Data[i] = new int[lenY + 1];

		memset(table.Data[i], 0, sizeof(int) * (lenY + 1));
	}

	int length = LCS(x, y, lenX, lenY, &table);
	Print(&table, x, y, lenX, lenY);
}