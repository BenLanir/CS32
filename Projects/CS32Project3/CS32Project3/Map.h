#ifndef MAP_DEFINED
#define MAP_DEFINED

#include "utilities.h"
#include "Actor.h"
#include <vector>

//Non-inline functions explained in implementation in cpp file
//All inline functions return what they say they get (getSomething will return that something)
class Map
{
public:
	Map(int goblinSmellDistance);
	~Map();
	void createLevel();
	void combat(Actor& attacker, Actor& defender);
	void playerAttack(int r, int c);
	void moveChars(char c);
	void populate();
	void addItems();
	void addMessage(Actor& attacker, Actor& defender, bool hit, bool dead, bool sleep);
	char getTile(int r, int c) { return floor[r][c]; }
	int getLevel() { return level; }
	Player& getPlayer() { return player; }
	void getMessage(int i) { cout << messages[i] << endl; } //This inline function writes to output the specified message instead of returning
	int getMessageSize() { return messages.size(); }
	bool getGameWon() { return gameWon; }
	void updateGoblinMap();
	void updateGoblinMapHelper(int distance, int r, int c);
private:
	char floor[18][70]; //Keeps current state of map
	int goblinMap[18][70]; //Will be updated to tell goblins where to go
	int level;
	int smellDistance;
	int endR, endC; //Marks the ladder or golden idol
	Player player;
	std::vector<Actor*> monsters; //A list of all monsters
	std::vector<Item*> items; //A list of all items
	std::vector<std::string> messages; //A list of the messages that should be output in some turn
	bool gameWon;
};

#endif