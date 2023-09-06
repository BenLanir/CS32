///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

#include "Game.h"
#include "Arena.h"
#include "Player.h"
#include "globals.h"

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
    default:  return false;
    case 'n': dir = NORTH; break;
    case 'e': dir = EAST;  break;
    case 's': dir = SOUTH; break;
    case 'w': dir = WEST;  break;
    }
    return true;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned blood vial and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // How dangerous is it to stand?
    int standDanger = computeDanger(a, r, c);

    // if it's not safe, see if moving is safer
    if (standDanger > 0)
    {
        int bestMoveDanger = standDanger;
        int bestMoveDir = NORTH;  // arbitrary initialization

          // check the four directions to see if any move is
          // better than standing, and if so, record the best
        for (int dir = 0; dir < NUMDIRS; dir++)
        {
            int rnew = r;
            int cnew = c;
            if (attemptMove(a, dir, rnew, cnew))
            {
                int danger = computeDanger(a, rnew, cnew);
                if (danger < bestMoveDanger)
                {
                    bestMoveDanger = danger;
                    bestMoveDir = dir;
                }
            }
        }

        // if moving is better than standing, recommend move
        if (bestMoveDanger < standDanger)
        {
            bestDir = bestMoveDir;
            return true;
        }
    }
    return false;  // recommend standing
}

int computeDanger(const Arena& a, int r, int c)
{
    // Our measure of danger will be the number of vampires that might move
    // to position (r,c).  If a vampire is at that position, it is fatal,
    // so a large value is returned.

    if (a.numberOfVampiresAt(r, c) > 0)
        return MAXVAMPIRES + 1;

    int danger = 0;
    if (r > 1)
        danger += a.numberOfVampiresAt(r - 1, c);
    if (r < a.rows())
        danger += a.numberOfVampiresAt(r + 1, c);
    if (c > 1)
        danger += a.numberOfVampiresAt(r, c - 1);
    if (c < a.cols())
        danger += a.numberOfVampiresAt(r, c + 1);

    return danger;
}

Game::Game(int rows, int cols, int nVampires)
{
    if (nVampires < 0)
    {
        std::cout << "***** Cannot create Game with negative number of vampires!" << std::endl;
        exit(1);
    }
    if (nVampires > MAXVAMPIRES)
    {
        std::cout << "***** Trying to create Game with " << nVampires
            << " vampires; only " << MAXVAMPIRES << " are allowed!" << std::endl;
        exit(1);
    }
    int nEmpty = rows * cols - nVampires - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        std::cout << "***** Game created with a " << rows << " by "
            << cols << " arena, which is too small to hold a player and "
            << nVampires << " vampires!" << std::endl;
        exit(1);
    }

    // Create arena
    m_arena = new Arena(rows, cols);

    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

    // Populate with vampires
    while (nVampires > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addVampire(r, c);
        nVampires--;
    }
}

Game::~Game()
{
    delete m_arena;
}

std::string Game::takePlayerTurn()
{
    for (;;)
    {
        bool historyPressed = false;
        std::cout << "Your move (n/e/s/w/x/h or nothing): ";
        std::string playerMove;
        getline(std::cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
            {
                return player->dropPoisonVial();
            }
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
            {
                return player->dropPoisonVial();
            }
            else if (tolower(playerMove[0] == 'h'))
            {
                m_arena->history().display();
                std::cout << "Press enter to continue" << std::endl;
                std::cin.ignore(10000, '\n');
                m_arena->display("");
                historyPressed = true;

            }
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        if (!historyPressed)
            std::cout << "Player move must be nothing, or 1 character n/e/s/w/x/h." << std::endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while (!player->isDead() && m_arena->vampireCount() > 0)
    {
        std::string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveVampires();
        m_arena->display(msg);
    }
    if (player->isDead())
        std::cout << "You lose." << std::endl;
    else
        std::cout << "You win." << std::endl;
}