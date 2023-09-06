#ifndef HISTORY_DEFINED
#define HISTORY_DEFINED

#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
	
private:
	int rows, cols;
	char grid[MAXROWS][MAXCOLS];
};

#endif