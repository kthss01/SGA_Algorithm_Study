#include <cstdio>
#include <cassert>
#include <string>
using namespace std;

#define MAX 1024
#define INIT -1

#define START 'S'
#define FINISH 'F'
#define WAY ' '
#define WALL '#'
#define MARKED '+' // finish로 가는 길 마킹

enum class Direction
{
	North, South, East, West
};

struct Position
{
	int X;
	int Y;
};

struct MazeDesc
{
	int Columns;
	int Rows;

	char** Data;
};

bool NextStep(MazeDesc* desc, Position* current, Direction direction, Position* next)
{
	switch (direction)
	{
		case Direction::North:
		{
			next->X = current->X;
			next->Y = current->Y - 1;

			if (next->Y == -1)
				return false;
		}
			break;
		case Direction::South:
		{
			next->X = current->X;
			next->Y = current->Y + 1;

			if (next->Y == desc->Rows)
				return false;
		}
			break;
		case Direction::East:
		{
			next->X = current->X + 1;
			next->Y = current->Y;

			if (next->X == desc->Columns)
				return false;
		}
			break;
		case Direction::West:
		{
			next->X = current->X - 1;
			next->Y = current->Y;

			if (next->X == -1)
				return false;
		}
			break;
	}

	if (desc->Data[next->X][next->Y] == WALL)
		return false;

	if (desc->Data[next->X][next->Y] == MARKED)
		return false;

	return true;
}

bool MoveTo(MazeDesc* desc, Position* current)
{
	Position next;

	if (desc->Data[current->X][current->Y] == FINISH)
		return true;

	desc->Data[current->X][current->Y] = MARKED;

	for (int i = 0; i < 4; i++)
	{
		if (NextStep(desc, current, (Direction)i, &next) == false)
			continue;

		//if (MoveTo(desc, &next, Direction::North) == true)
		if (MoveTo(desc, &next) == true)
			return true;
	}

	desc->Data[current->X][current->Y] = WAY;

	return false;
}

bool Solve(MazeDesc* desc)
{
	bool foundedStart = false;
	bool result = false;

	Position start;

	for (int x = 0; x < desc->Rows; x++)
	{
		for (int y = 0; y < desc->Columns; y++)
		{
			if (desc->Data[x][y] == START)
			{
				start.X = x;
				start.Y = y;

				foundedStart = true;
			}
		}
	}

	if (foundedStart == false)
		return false;

	if (MoveTo(desc, &start))
		result = true;

	desc->Data[start.X][start.Y] = START;

	return result;
}

void ReadMaze(string path, MazeDesc* desc)
{
	FILE* fp = fopen(path.c_str(), "r");
	assert(fp != NULL);

	int rows = 0;
	int columns = INIT;

	char buffer[MAX];
	while (fgets(buffer, MAX, fp) != NULL)
	{
		rows++;

		if (columns == INIT)
			columns = strlen(buffer) - 1;
		else if (columns != strlen(buffer) - 1) 
		{
			fclose(fp);
			assert(false);
		}
	}

	desc->Rows = rows;
	desc->Columns = columns;
	desc->Data = new char*[rows];

	for (int i = 0; i < rows; i++)
		desc->Data[i] = new char[columns];

	rewind(fp); // 처음의 file pointer로 돌리라는거

	for (int i = 0; i < rows; i++)
	{
		fgets(buffer, MAX, fp);

		for (int j = 0; j < columns; j++)
			desc->Data[i][j] = buffer[j];
	}

	fclose(fp);
}

void main()
{
	string mazePath = "MazeSample2.txt";

	MazeDesc desc;
	ReadMaze(mazePath, &desc);

	Solve(&desc);

	for (int x = 0; x < desc.Rows; x++)
	{
		for (int y = 0; y < desc.Columns; y++)
		{
			printf("%c", desc.Data[x][y]);
		}
		printf("\n");
	}
}