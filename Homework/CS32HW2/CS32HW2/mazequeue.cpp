#include <queue>
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
    queue<Coord> coordQueue;
    Coord a(sr, sc);
    coordQueue.push(a);
    maze[sr][sc] = '0';

    while (!coordQueue.empty())
    {
        Coord b = coordQueue.front();
        coordQueue.pop();
        if (b.r() == er && b.c() == ec)
        {
            return true;
        }
        if (maze[b.r() + 1][b.c()] == '.')
        {
            coordQueue.push(Coord(b.r() + 1, b.c()));
            maze[b.r() + 1][b.c()] = '0';
        }
        if (maze[b.r()][b.c() - 1] == '.')
        {
            coordQueue.push(Coord(b.r(), b.c() - 1));
            maze[b.r()][b.c() - 1] = '0';
        }
        if (maze[b.r() - 1][b.c()] == '.')
        {
            coordQueue.push(Coord(b.r() - 1, b.c()));
            maze[b.r() - 1][b.c()] = '0';
        }
        if (maze[b.r()][b.c() + 1] == '.')
        {
            coordQueue.push(Coord(b.r(), b.c() + 1));
            maze[b.r()][b.c() + 1] = '0';
        }
    }
    return false;
}