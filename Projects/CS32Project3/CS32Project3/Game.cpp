// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
#include <string>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) : map(goblinSmellDistance)
{}

//Starts the game
void Game::play()
{
    map.createLevel();

    display();
    char buttonPressed;


    while (1)
    {
        //Checks to see if the game was won, lost, or the player quit, if not runs another turn
        if (map.getPlayer().getHP() <= 0)
        {
            cout << "Press q to exit game." << endl;
            while (1)
                if (getCharacter() == 'q')
                    return;
        }
        else if (map.getGameWon())
        {
            cout << "You pick up the golden idol" << endl;
            cout << "Congratulations, you won!" << endl << endl;
            cout << "Press q to exit game.";
            while (1)
                if (getCharacter() == 'q')
                    return;
        }
        buttonPressed = getCharacter();
        if (buttonPressed == 'q')
        {
            break;
        }
        else
        {
            map.moveChars(buttonPressed);
            display();
        }
    }
}

//Displays the current state of the game with the stats below it, and any messages for that turn
void Game::display()
{
    clearScreen();
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 70; j++)
            cout << map.getTile(i, j);
        cout << endl;
    }
    cout << "Dungeon Level: " << map.getLevel();
    cout << ", Hit points: " << map.getPlayer().getHP();
    cout << ", Armor: " << map.getPlayer().getArmor();
    cout << ", Strength: " << map.getPlayer().getStrength();
    cout << ", Dex: " << map.getPlayer().getDex() << endl;

    for (int i = 0; i < map.getMessageSize(); i++)
        map.getMessage(i);

}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
