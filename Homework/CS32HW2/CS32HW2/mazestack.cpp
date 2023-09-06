#include <stack>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    Coord a(sr, sc);
    coordStack.push(a);
    maze[sr][sc] = '0';

    while (!coordStack.empty())
    {
        Coord b = coordStack.top();
        coordStack.pop();
        if (b.r() == er && b.c() == ec)
        {
            return true;
        }
        if (maze[b.r() + 1][b.c()] == '.')
        {
            coordStack.push(Coord(b.r() + 1, b.c()));
            maze[b.r() + 1][b.c()] = '0';
        }
        if (maze[b.r()][b.c() - 1] == '.')
        {
            coordStack.push(Coord(b.r(), b.c() - 1));
            maze[b.r()][b.c() - 1] = '0';
        }
        if (maze[b.r() - 1][b.c()] == '.')
        {
            coordStack.push(Coord(b.r() - 1, b.c()));
            maze[b.r() - 1][b.c()] = '0';
        }
        if (maze[b.r()][b.c() + 1] == '.')
        {
            coordStack.push(Coord(b.r(), b.c() + 1));
            maze[b.r()][b.c() + 1] = '0';
        }
    }
    return false;
}