#include <cstdio>
#include <cstring>

struct LCSTable
{
	int** Data;
};

int LCS(char* x, char* y, int i, int j, LCSTable* table)
{
	int m = 0, n = 0;

	for (m = 0; m <= i; m++)
		table->Data[m][0] = 0;
	for (n = 0; n <= j; n++)
		table->Data[0][n] = 0;

	for (m = 1; m <= i; m++)
	{
		for (n = 1; n <= j; n++) 
		{
			if (x[m - 1] == y[n - 1])
			{
				table->Data[m][n] = table->Data[m - 1][n - 1] + 1;
			}
			else
			{
				if (table->Data[m][n - 1] >= table->Data[m - 1][n])
					table->Data[m][n] = table->Data[m][n - 1];
				else
					table->Data[m][n] = table->Data[m - 1][n];
			}
		} // for(n)
	} // for(m)

	return table->Data[i][j];
}

void TraceBack(char* x, char* y, int m, int n, LCSTable* table, char* lcs)
{
	if (m == 0 || n == 0)
		return;

	bool b = table->Data[m][n] > table->Data[m][n - 1]
		&& table->Data[m][n] > table->Data[m - 1][n]
		&& table->Data[m][n] > table->Data[m - 1][n - 1];

	bool c = table->Data[m][n] == table->Data[m][n - 1]
	 && table->Data[m][n] > table->Data[m - 1][n];

	if (b == true)
	{
		char temp[100];
		strcpy(temp, lcs);
		sprintf(lcs, "%c%s", x[m - 1], temp);

		TraceBack(x, y, m - 1, n - 1, table, lcs);
	}
	else if (c == true)
	{
		TraceBack(x, y, m, n - 1, table, lcs);
	}
	else
	{
		TraceBack(x, y, m - 1, n, table, lcs);
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

	char* result = new char[lenX * lenY + 1];
	sprintf(result, "");

	TraceBack(x, y, lenX, lenY, &table, result);

	printf("\n");
	printf("LCS:\"%s\" (Length:%d)\n", result, length);

	//// test
	//printf("%d\n", Add(10, 20));
}