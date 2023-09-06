// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED


#include "Map.h"
// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    void display();
    void play();
private:
    Map map;
};

#endif // GAME_INCLUDED
