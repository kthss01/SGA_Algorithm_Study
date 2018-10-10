#include <cstdio>
#include <Windows.h>

// ������ ������ ������, ������ ó��, ���⼭ �� �� ���ٴ� �ǹ�
bool Threatened(int* columns, int row)
{
	for (int i = 0; i < row; i++)
	{
		bool check = false;
		check |= columns[row] == columns[i];
		check |= abs(columns[row] - columns[i]) == abs(row - i);

		if (check == true)
			return true;
	}

	return false;
}

void Print(int* columns, int number)
{
	for (int x = 0; x < number; x++)
	{
		for (int y = 0; y < number; y++)
		{
			if (columns[x] == y)
				printf("��");
			else
				printf("��");
		}
			
		printf("\n");
	}
	
	printf("\n");
}

void FindQueens(int* columns, int row, int number, int* count)
{
	if (Threatened(columns, row))
		return;

	if (row == number - 1)
	{
		printf("Solution : %d :\n", ++(*count));

		Print(columns, number);
	}
	else
	{
		for (int i = 0; i < number; i++)
		{
			columns[row + 1] = i;

			FindQueens(columns, row + 1, number, count);
		}
	}
}

void main()
{
	int count = 0;
	int number = 4;

	// columns �ش� �ο쿡 ���� � ���� ������ ��
	int* columns = new int[number];
	for (int i = 0; i < number; i++)
	{
		columns[0] = i;

		FindQueens(columns, 0, number, &count);
	}

	delete[] columns;
}