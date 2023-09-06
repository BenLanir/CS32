#include "History.h"
#include "globals.h"

History::History(int nRows, int nCols)
{
	rows = nRows;
	cols = nCols;
	for (int i = 0; i < nRows; i++)
	{
		for (int j = 0; j < nCols; j++)
		{
			grid[i][j] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r > MAXROWS || c > MAXCOLS || r < 1 || c < 1)
	{
		return false;
	}
	if (grid[r - 1][c - 1] == '.')
		grid[r - 1][c - 1] = 'A';
	else if (grid[r - 1][c - 1] == 'A')
		grid[r - 1][c - 1] = 'B';
	else if (grid[r - 1][c - 1] == 'B')
		grid[r - 1][c - 1] = 'C';
	else if (grid[r - 1][c - 1] == 'C')
		grid[r - 1][c - 1] = 'D';
	else if (grid[r - 1][c - 1] == 'D')
		grid[r - 1][c - 1] = 'E';
	else if (grid[r - 1][c - 1] == 'E')
		grid[r - 1][c - 1] = 'F';
	else if (grid[r - 1][c - 1] == 'F')
		grid[r - 1][c - 1] = 'G';
	else if (grid[r - 1][c - 1] == 'G')
		grid[r - 1][c - 1] = 'H';
	else if (grid[r - 1][c - 1] == 'H')
		grid[r - 1][c - 1] = 'I';
	else if (grid[r - 1][c - 1] == 'I')
		grid[r - 1][c - 1] = 'J';
	else if (grid[r - 1][c - 1] == 'J')
		grid[r - 1][c - 1] = 'K';
	else if (grid[r - 1][c - 1] == 'K')
		grid[r - 1][c - 1] = 'L';
	else if (grid[r - 1][c - 1] == 'L')
		grid[r - 1][c - 1] = 'M';
	else if (grid[r - 1][c - 1] == 'M')
		grid[r - 1][c - 1] = 'N';
	else if (grid[r - 1][c - 1] == 'N')
		grid[r - 1][c - 1] = 'O';
	else if (grid[r - 1][c - 1] == 'O')
		grid[r - 1][c - 1] = 'P';
	else if (grid[r - 1][c - 1] == 'P')
		grid[r - 1][c - 1] = 'Q';
	else if (grid[r - 1][c - 1] == 'Q')
		grid[r - 1][c - 1] = 'R';
	else if (grid[r - 1][c - 1] == 'R')
		grid[r - 1][c - 1] = 'S';
	else if (grid[r - 1][c - 1] == 'S')
		grid[r - 1][c - 1] = 'T';
	else if (grid[r - 1][c - 1] == 'T')
		grid[r - 1][c - 1] = 'U';
	else if (grid[r - 1][c - 1] == 'U')
		grid[r - 1][c - 1] = 'V';
	else if (grid[r - 1][c - 1] == 'V')
		grid[r - 1][c - 1] = 'W';
	else if (grid[r - 1][c - 1] == 'W')
		grid[r - 1][c - 1] = 'X';
	else if (grid[r - 1][c - 1] == 'X')
		grid[r - 1][c - 1] = 'Y';
	else if (grid[r - 1][c - 1] == 'Y')
		grid[r - 1][c - 1] = 'Z';

	return true;
}

void History::display() const
{
	clearScreen();
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << grid[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}