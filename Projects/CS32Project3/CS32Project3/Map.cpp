#include "Map.h"
#include <iostream>

using namespace std;

//Intializes the map to all walls and goblin map to all values of 99 to be used later
Map::Map(int goblinSmellDistance): player()
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			floor[i][j] = '#';
			goblinMap[i][j] = 99;
		}
	}
	level = 0;
	gameWon = false;
	smellDistance = goblinSmellDistance;
}

//Deletes and removes all monsters, all items, and all messages
Map::~Map()
{
	for (int i = 0; i < monsters.size(); i++)
		delete monsters[i];
	monsters.clear();
	for (int i = 0; i < items.size(); i++)
		delete items[i];
	items.clear();
	messages.clear();
}

//Used to create a new level at the beginning of the game and each floor
void Map::createLevel()
{
	//Delete monsters from previous floor
	for (int i = 0; i < monsters.size(); i++)
		delete monsters[i];
	monsters.clear();

	for (int i = 0; i < items.size(); i++)
		delete items[i];
	items.clear();

	//reset map to all filled in
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 70; j++)
			floor[i][j] = '#';

	//random room parameters - I messed around with these to create better looking maps
	int rooms = randInt(3, 5);
	int roomHeightMin = 2;
	int roomHeightMax = 5;
	int roomWidthMin = 8;
	int roomWidthMax = 10;

	//First room "start point"
	int startX = randInt(1, 10);
	int startY = randInt(7, 11);

	//Begin loop of room creation
	for (int i = 0; i < rooms; i++)
	{
		//Create a room with random height and width, checks to ensure that it does not go out of bounds
		int roomWidth = randInt(roomWidthMin, roomWidthMax);
		int roomHeight = randInt(roomHeightMin, roomHeightMax);
		for (int j = 0; j < roomWidth; j++)
		{
			if (startX < 69)
			{
				for (int k = 0; k <= roomHeight; k++)
				{
					if (startY + k < 17)
						floor[startY + k][startX] = ' ';
					if (startY - k > 0)
						floor[startY - k][startX] = ' ';
				}
				floor[startY][startX] = ' ';
			}
			startX++;
		}

		//If the height of the current room permits, this creates a chance that another room is created  below the current one
		if (startY - roomHeight > 6 && trueWithProbability(0.5))
		{
			int offshootX = startX - roomWidth / 2 + 1;
			int offshootY = startY - roomHeight;
			int hallHeight = randInt(2, 4);
			int offshootHeight = randInt(roomHeightMin * 2, roomHeightMax * 2);
			int offshootWidth = randInt(roomWidthMin / 2, roomWidthMax / 2);
			for (int j = 0; j < hallHeight; j++)
			{
				floor[offshootY][offshootX] = ' ';
				offshootY--;
			}
			for (int j = 0; j < offshootHeight; j++)
			{
				if (offshootY > 0)
				{
					for (int k = 0; k < offshootWidth; k++)
					{
						if (offshootX + k < 69)
							floor[offshootY][offshootX + k] = ' ';
						if (offshootX - k > 1)
							floor[offshootY][offshootX - k] = ' ';
					}
				}
				offshootY--;
			}
		}
		//If the height of the current room permits, this creates a chance that another room is created  above the current one
		if (startY + roomHeight < 11 && trueWithProbability(0.5))
		{
			int offshootX = startX - roomWidth / 2 + 1;
			int offshootY = startY + roomHeight;
			int hallHeight = randInt(2, 4);
			int offshootHeight = randInt(roomHeightMin * 2, roomHeightMax * 2);
			int offshootWidth = randInt(roomWidthMin / 2, roomWidthMax / 2);
			for (int j = 0; j < hallHeight; j++)
			{
				floor[offshootY][offshootX] = ' ';
				offshootY++;
			}
			for (int j = 0; j < offshootHeight; j++)
			{
				if (offshootY < 17)
				{
					for (int k = 0; k < offshootWidth; k++)
					{
						if (offshootX + k < 69)
							floor[offshootY][offshootX + k] = ' ';
						if (offshootX - k > 1)
							floor[offshootY][offshootX - k] = ' ';
					}
				}
				offshootY++;
			}
		}

		//Unless that was the last room, create a corridor of random length roughly inversely proportional to the number of rooms leading to the next room
		if (i < rooms-1)
		{
			startY += randInt(-roomHeight, roomHeight);
			if (startY < 1)
				startY += (int)(1.5 * roomHeight);
			if (startY > 16)
				startY -= (int)(1.5 * roomHeight);
			int hallSize = randInt(3/rooms + 1, 30/rooms);
			for (int j = 0; j < hallSize; j++)
			{
				if (startX < 69)
				{
					floor[startY][startX] = ' ';
					startX++;
				}
			}
		}
	}

	//Place the ladder or idol
	endC = randInt(1, 68);
	endR = randInt(1, 16);
	while (floor[endR][endC] == '#')
	{
		endC = randInt(1, 68);
		endR = randInt(1, 16);
	}
	if (level == 4)
		floor[endR][endC] = '&';
	else
		floor[endR][endC] = '>';

	//Place the player
	int playerX = randInt(1, 68);
	int playerY = randInt(1, 16);
	while (floor[playerY][playerX] == '#')
	{
		playerX = randInt(1, 68);
		playerY = randInt(1, 16);
	}

	player.setC(playerX);
	player.setR(playerY);

	floor[playerY][playerX] = '@';


	//Place the monsters
	populate();

	//Place the items
	addItems();

	//Put the item symbols on the map if no Actor is on top of them
	for (int i = 0; i < items.size(); i++)
	{
		if (floor[items[i]->getR()][items[i]->getC()] == ' ')
		{
			floor[items[i]->getR()][items[i]->getC()] = items[i]->getSymbol();
		}
	}
}


//Choose random number of monsters scaling to level and insert appropriate monsters for that level
void Map::populate()
{
	//Note: placing goblins at end of monster vector allows for slight improvement in goblin AI
	int numMonsters = randInt(2, 5 * (level + 1) + 1);

	//Switch decides what types of monsters should be created (as Bogeyman only appear at level 2 and dragons at level 3)
	//Each case cycles through until an appropriate number of monsters has been created, making sure that no monster is created in a wall or on top of another Actor
	switch (level)
	{
	case 0:
	case 1:
		for (int i = 0; i < numMonsters; i++)
		{
			int tempRow = randInt(0, 17);
			int tempCol = randInt(0, 69);
			while (floor[tempRow][tempCol] != ' ')
			{
				tempRow = randInt(0, 17);
				tempCol = randInt(0, 69);
			}
			if (trueWithProbability(0.5))
			{
				monsters.push_back(new Goblin(tempRow, tempCol));
				floor[tempRow][tempCol] = 'G';
			}
			else
			{
				monsters.insert(monsters.begin(), new Snakewoman(tempRow, tempCol));
				floor[tempRow][tempCol] = 'S';
			}
		}
		break;
	case 2:
		for (int i = 0; i < numMonsters; i++)
		{
			int tempRow = randInt(0, 17);
			int tempCol = randInt(0, 69);
			while (floor[tempRow][tempCol] != ' ')
			{
				tempRow = randInt(0, 17);
				tempCol = randInt(0, 69);
			}
			if (trueWithProbability(0.33))
			{
				monsters.push_back(new Goblin(tempRow, tempCol));
				floor[tempRow][tempCol] = 'G';
			}
			else if (trueWithProbability(0.5))
			{
				monsters.insert(monsters.begin(), new Snakewoman(tempRow, tempCol));
				floor[tempRow][tempCol] = 'S';
			}
			else
			{
				monsters.insert(monsters.begin(), new Bogeyman(tempRow, tempCol));
				floor[tempRow][tempCol] = 'B';
			}
			floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
		}
		break;
	case 3:
	case 4:
		for (int i = 0; i < numMonsters; i++)
		{
			int tempRow = randInt(0, 17);
			int tempCol = randInt(0, 69);
			while (floor[tempRow][tempCol] != ' ')
			{
				tempRow = randInt(0, 17);
				tempCol = randInt(0, 69);
			}
			if (trueWithProbability(0.25))
			{
				monsters.push_back(new Goblin(tempRow, tempCol));
				floor[tempRow][tempCol] = 'G';
			}
			else if (trueWithProbability(0.33))
			{
				monsters.insert(monsters.begin(), new Snakewoman(tempRow, tempCol));
				floor[tempRow][tempCol] = 'S';
			}
			else if (trueWithProbability(0.5))
			{
				monsters.insert(monsters.begin(), new Bogeyman(tempRow, tempCol));
				floor[tempRow][tempCol] = 'B';
			}
			else
			{
				monsters.insert(monsters.begin(), new Dragon(tempRow, tempCol));
				floor[tempRow][tempCol] = 'D';
			}
			//Puts the monster on the map to make sure that no other monster spawns on top of it
			floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
		}
		break;
	}
}

//Creates 2 or 3 random items for each level and places them
void Map::addItems()
{
	int itemCount = randInt(2, 3);
	for (int i = 0; i < itemCount; i++)
	{
		//Checks to make sure there isn't annother item or a wall or the ladder or idol already there
		int itemRow = randInt(1, 16);
		int itemCol = randInt(1, 68);
		bool itemThereAlready = false;
		while (floor[itemRow][itemCol] == '#' || (itemRow == endR && itemCol == endC) && !itemThereAlready)
		{
			itemThereAlready = false;
			itemRow = randInt(1, 16);
			itemCol = randInt(1, 68);
			for (int i = 0; i < items.size(); i++)
			{
				if (items[i]->getR() == itemRow && items[i]->getC() == itemCol)
					itemThereAlready = true;
			}
		}
		//Selects which item of the 7 that can randomly spawn and places it
		int whichItem = randInt(0, 6);
		switch (whichItem)
		{
		case 0:
			items.push_back(new Weapon("short sword", itemRow, itemCol));
			break;
		case 1:
			items.push_back(new Weapon("mace", itemRow, itemCol));
			break;
		case 2:
			items.push_back(new Weapon("long sword", itemRow, itemCol));
			break;
		case 3:
			items.push_back(new Scroll("a scroll of improve armor", itemRow, itemCol));
			break;
		case 4:
			items.push_back(new Scroll("a scroll of raise strength", itemRow, itemCol));
			break;
		case 5:
			items.push_back(new Scroll("a scroll of enhance health", itemRow, itemCol));
			break;
		case 6:
			items.push_back(new Scroll("a scroll of enhance dexterity", itemRow, itemCol));
			break;
		}
	}
}

//Takes a turn, performs whatever action the player did, moves all actors, and deletes dead monsters
void Map::moveChars(char c)
{
	//Clear the messages (they only should appear once)
	while (!messages.empty())
		messages.pop_back();

	//Chance to heal the player
	if (player.getHP() < player.getMaxHP())
		if (trueWithProbability(0.1))
			player.setHP(player.getHP() + 1);

	//If the player is sleeping it cannot take actions
	if (player.getSleep() != 0)
		player.setSleep(player.getSleep() - 1);

	//Takes the player input and figures out what to do
	else
	{
		std::string weaponOrScroll = "";
		std::string extraMessage = "";
		switch (c) {
			//Cases h, j, k, l, or the appropriate arrow keys: moves the player if able, or calls attack if player moved into a monster
		case 'k':
			if (floor[player.getR() - 1][player.getC()] == ' ' || floor[player.getR() - 1][player.getC()] == ')' || floor[player.getR() - 1][player.getC()] == '?' || floor[player.getR() - 1][player.getC()] == '>' || floor[player.getR() - 1][player.getC()] == '&')
			{
				floor[player.getR()][player.getC()] = ' ';
				floor[player.getR() - 1][player.getC()] = '@';
				player.setR(player.getR() - 1);
			}
			else if (floor[player.getR() - 1][player.getC()] == 'S' || floor[player.getR() - 1][player.getC()] == 'B' || floor[player.getR() - 1][player.getC()] == 'D' || floor[player.getR() - 1][player.getC()] == 'G')
				playerAttack(player.getR() - 1, player.getC());
			break;
		case 'l':
			if (floor[player.getR()][player.getC() + 1] == ' ' || floor[player.getR()][player.getC() + 1] == ')' || floor[player.getR()][player.getC() + 1] == '?' || floor[player.getR()][player.getC() + 1] == '>' || floor[player.getR()][player.getC() + 1] == '&')
			{
				floor[player.getR()][player.getC()] = ' ';
				floor[player.getR()][player.getC() + 1] = '@';
				player.setC(player.getC() + 1);
			}
			else if (floor[player.getR()][player.getC() + 1] == 'S' || floor[player.getR()][player.getC() + 1] == 'B' || floor[player.getR()][player.getC() + 1] == 'D' || floor[player.getR()][player.getC() + 1] == 'G')
				playerAttack(player.getR(), player.getC() + 1);
			break;
		case 'j':
			if (floor[player.getR() + 1][player.getC()] == ' ' || floor[player.getR() + 1][player.getC()] == ')' || floor[player.getR() + 1][player.getC()] == '?' || floor[player.getR() + 1][player.getC()] == '>' || floor[player.getR() + 1][player.getC()] == '&')
			{
				floor[player.getR()][player.getC()] = ' ';
				floor[player.getR() + 1][player.getC()] = '@';
				player.setR(player.getR() + 1);
			}
			else if (floor[player.getR() + 1][player.getC()] == 'S' || floor[player.getR() + 1][player.getC()] == 'B' || floor[player.getR() + 1][player.getC()] == 'D' || floor[player.getR() + 1][player.getC()] == 'G')
				playerAttack(player.getR() + 1, player.getC());
			break;
		case 'h':
			if (floor[player.getR()][player.getC() - 1] == ' ' || floor[player.getR()][player.getC() - 1] == ')' || floor[player.getR()][player.getC() - 1] == '?' || floor[player.getR()][player.getC() - 1] == '>' || floor[player.getR()][player.getC() - 1] == '&')
			{
				floor[player.getR()][player.getC()] = ' ';
				floor[player.getR()][player.getC() - 1] = '@';
				player.setC(player.getC() - 1);
			}
			else if (floor[player.getR()][player.getC() - 1] == 'S' || floor[player.getR()][player.getC() - 1] == 'B' || floor[player.getR()][player.getC() - 1] == 'D' || floor[player.getR()][player.getC() - 1] == 'G')
				playerAttack(player.getR(), player.getC() - 1);
			break;
			//Case >: if player is over a ladder move to a new level
		case '>':
			if (player.getR() == endR && player.getC() == endC && level != 4)
			{
				level++;
				createLevel();
			}
			break;
			//Case c: cheat
		case 'c':
			player.setStrength(9);
			player.setMaxHP(50);
			player.setHP(50);
			break;
			//Case g: if the player is standing on the idol, win the game, otherwise check if the player is on an item and pick it up if so
		case 'g':
			if (level == 4 && player.getC() == endC && player.getR() == endR)
				gameWon = true;
			else
			{
				for (int i = 0; i < items.size(); i++)
				{
					if (items[i]->getR() == player.getR() && items[i]->getC() == player.getC())
					{
						player.pickup(items[i]);
						messages.push_back("You pick up " + items[i]->getName());
						delete items[i];
						items.erase(items.begin() + i);
					}
				}
			}
			break;
			//Case i: show inventory
		case 'i':
			player.getInventory().show();
			break;
		case 'w':
			//Case w: show inventory, if player selects a weapon make that the players weapon, add a message about it
			if (player.getInventory().wield(weaponOrScroll))
			{
				Weapon* tempWeapon = &player.getWeapon();
				delete tempWeapon;
				player.setWeapon(new Weapon(weaponOrScroll, -1, 1));
				messages.push_back("You are wielding " + player.getWeapon().getName());
			}
			else if (weaponOrScroll != "")
			{
				messages.push_back("You can't wield " + weaponOrScroll + "!");
			}
			break;
			//Case r: show inventory, if the player selects a scroll read the scroll and change stats accordingly, add a message about it
			//If the scroll is a teleport scroll find a new empty location to place the player and move them there
		case 'r':
			if (player.read(weaponOrScroll, extraMessage))
			{
				if (weaponOrScroll == "a scroll of teleportation")
				{
					floor[player.getR()][player.getC()] = ' ';
					int newPlayerR = randInt(1, 17);
					int newPlayerC = randInt(1, 68);
					while (floor[newPlayerR][newPlayerC] == '#' || floor[newPlayerR][newPlayerC] == 'G' || floor[newPlayerR][newPlayerC] == 'S' || floor[newPlayerR][newPlayerC] == 'B' || floor[newPlayerR][newPlayerC] == 'D')
					{
						newPlayerR = randInt(1, 17);
						newPlayerC = randInt(1, 68);
					}
					player.setR(newPlayerR);
					player.setC(newPlayerC);
					floor[player.getR()][player.getC()] = '@';
				}
				messages.push_back("You read " + weaponOrScroll);
				messages.push_back(extraMessage);
			}
			else if (weaponOrScroll != "")
				messages.push_back("You can't read " + weaponOrScroll + "!");
			break;
		}
	}

	//Move the monsters
	for (int i = 0; i < monsters.size(); i++)
	{
		//playerDist is used to see if the monster is close enough to smell the player, and if the monster is close enough to attack
		int playerDist = abs(player.getR() - monsters[i]->getR()) + abs(player.getC() - monsters[i]->getC());

		//Kills a dead monster, removes it from the monster list and deletes it, also checks to see if anything is on the floor and has a chance to drop an item if not
		if (monsters[i]->getHP() <= 0)
		{
			bool itemThere = false;
			for (int j = 0; j < items.size(); j++)
				if (items[j]->getR() == monsters[i]->getR() && items[j]->getC() == monsters[i]->getC())
					itemThere = true;
			if (!itemThere)
			{
				if (monsters[i]->getName() == "the Goblin")
				{
					if (trueWithProbability(0.33))
					{
						if (trueWithProbability(0.5))
							items.push_back(new Weapon("magic axe", monsters[i]->getR(), monsters[i]->getC()));
						else
							items.push_back(new Weapon("magic fangs of sleep", monsters[i]->getR(), monsters[i]->getC()));
					}
				}
				else if (monsters[i]->getName() == "the Snakewoman")
				{
					if (trueWithProbability(0.33))
						items.push_back(new Weapon("magic fangs of sleep", monsters[i]->getR(), monsters[i]->getC()));
				}
				else if (monsters[i]->getName() == "the Bogeyman")
				{
					if (trueWithProbability(0.1))
						items.push_back(new Weapon("magic axe", monsters[i]->getR(), monsters[i]->getC()));
				}
				else if (monsters[i]->getName() == "the Dragon")
				{
					int whichScroll = randInt(0, 4);
					switch (whichScroll)
					{
					case 0:
						items.push_back(new Scroll("a scroll of teleportation", monsters[i]->getR(), monsters[i]->getC()));
						break;
					case 1:
						items.push_back(new Scroll("a scroll of improve armor", monsters[i]->getR(), monsters[i]->getC()));
						break;
					case 2:
						items.push_back(new Scroll("a scroll of raise strength", monsters[i]->getR(), monsters[i]->getC()));
						break;
					case 3:
						items.push_back(new Scroll("a scroll of enhance health", monsters[i]->getR(), monsters[i]->getC()));
						break;
					case 4:
						items.push_back(new Scroll("a scroll of enhance dexterity", monsters[i]->getR(), monsters[i]->getC()));
						break;
					}
				}
			}
			floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
			delete monsters[i];
			monsters.erase(monsters.begin() + i);
			if (i > 0)
				i--;
		}
		//Monsters don't do anything if they are asleep
		else if (monsters[i]->getSleep() != 0)
			monsters[i]->setSleep(monsters[i]->getSleep() - 1);
		//If the monster is next to the player it attacks
		else if (playerDist == 1)
		{
			combat(*monsters[i], player);
		}
		//Decides monster movement for everything except goblins
		else if (monsters[i]->getSymbol() != 'G')
		{
			//If the monster is a dragon it has a chance to heal
			if (monsters[i]->getSymbol() == 'D')
				if (monsters[i]->getHP() < monsters[i]->getMaxHP() && trueWithProbability(0.1))
					monsters[i]->setHP(monsters[i]->getHP() + 1);
			//If the monster is within smell distance it moves toward the player if it can (but it doesn't see walls, other monsters)
			if (playerDist <= monsters[i]->getMove())
			{
				if (player.getC() > monsters[i]->getC() && (floor[monsters[i]->getR()][monsters[i]->getC() + 1] == ' ' || floor[monsters[i]->getR()][monsters[i]->getC() + 1] == '?' || floor[monsters[i]->getR()][monsters[i]->getC() + 1] == ')' || floor[monsters[i]->getR()][monsters[i]->getC() + 1] == '>' || floor[monsters[i]->getR()][monsters[i]->getC() + 1] == '&'))
				{
					floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
					monsters[i]->setC(monsters[i]->getC() + 1);
					floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
				}
				else if (player.getR() > monsters[i]->getR() && (floor[monsters[i]->getR() + 1][monsters[i]->getC()] == ' ' || floor[monsters[i]->getR() + 1][monsters[i]->getC()] == '?' || floor[monsters[i]->getR() + 1][monsters[i]->getC()] == ')' || floor[monsters[i]->getR() + 1][monsters[i]->getC()] == '>' || floor[monsters[i]->getR() + 1][monsters[i]->getC()] == '&'))
				{
					floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
					monsters[i]->setR(monsters[i]->getR() + 1);
					floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
				}
				else if (player.getC() < monsters[i]->getC() && (floor[monsters[i]->getR()][monsters[i]->getC() - 1] == ' ' || floor[monsters[i]->getR()][monsters[i]->getC() - 1] == '?' || floor[monsters[i]->getR()][monsters[i]->getC() - 1] == ')' || floor[monsters[i]->getR()][monsters[i]->getC() - 1] == '>' || floor[monsters[i]->getR()][monsters[i]->getC() - 1] == '&'))
				{
					floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
					monsters[i]->setC(monsters[i]->getC() - 1);
					floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
				}
				else if (player.getR() < monsters[i]->getR() && (floor[monsters[i]->getR() - 1][monsters[i]->getC()] == ' ' || floor[monsters[i]->getR() - 1][monsters[i]->getC()] == '?' || floor[monsters[i]->getR() - 1][monsters[i]->getC()] == ')' || floor[monsters[i]->getR() - 1][monsters[i]->getC()] == '>' || floor[monsters[i]->getR() - 1][monsters[i]->getC()] == '&'))
				{
					floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
					monsters[i]->setR(monsters[i]->getR() - 1);
					floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
				}
			}
		}
		//If the monster is a goblin, update the goblin map, then move toward a lower number on the goblin map if one is adjacent
		//Goblin map is explained below in updateGoblinMap and updateGoblinMapHelper section
		else if (monsters[i]->getSymbol() == 'G')
		{
			updateGoblinMap();
			int current = goblinMap[monsters[i]->getR()][monsters[i]->getC()];
			int up = goblinMap[monsters[i]->getR() - 1][monsters[i]->getC()];
			int down = goblinMap[monsters[i]->getR() + 1][monsters[i]->getC()];
			int left = goblinMap[monsters[i]->getR()][monsters[i]->getC() - 1];
			int right = goblinMap[monsters[i]->getR()][monsters[i]->getC() + 1];
			if (down < current && down <= up && down <= left && down <= right)
			{
				floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
				monsters[i]->setR(monsters[i]->getR() + 1);
				floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
			}
			else if (up < current && up <= down && up <= left && up <= right)
			{
				floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
				monsters[i]->setR(monsters[i]->getR() - 1);
				floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
			}
			else if (right < current && right <= down && right <= up && right <= left)
			{
				floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
				monsters[i]->setC(monsters[i]->getC() + 1);
				floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
			}
			else if (left < current && left <= down && left <= up && left <= right)
			{
				floor[monsters[i]->getR()][monsters[i]->getC()] = ' ';
				monsters[i]->setC(monsters[i]->getC() - 1);
				floor[monsters[i]->getR()][monsters[i]->getC()] = monsters[i]->getSymbol();
			}
		}
	}

	//Replace any uncovered ladder, idol, or item
	if (floor[endR][endC] == ' ')
		if (level == 4)
			floor[endR][endC] = '&';
		else
			floor[endR][endC] = '>';

	for (int i = 0; i < items.size(); i++)
		if (floor[items[i]->getR()][items[i]->getC()] == ' ')
			floor[items[i]->getR()][items[i]->getC()] = items[i]->getSymbol();
}

//Resolves a combat between two actors (a player and a monster)
void Map::combat(Actor& attacker, Actor& defender)
{
	//Booleans to describe what happens
	bool hit = false;
	bool sleep = false;
	bool dead = false;

	int attackerPoints = attacker.getDex() + attacker.getWeapon().getDex();
	int defenderPoints = defender.getDex() + defender.getArmor();

	int damagePoints = randInt(0, attacker.getStrength() + attacker.getWeapon().getStrength());
	//Checks to see if hit, then resolves combat
	if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
	{
		defender.setHP(defender.getHP() - damagePoints);
		hit = true;
		//Checks to see if the defender died
		if (defender.getHP() <= 0)
			dead = true;
		//Checks to see if the defender can be put to sleep
		else if (attacker.getWeapon().getName() == "magic fangs of sleep")
		{
			if (trueWithProbability(0.2))
			{
				int sleepTime = randInt(2, 6);
				defender.setSleep(sleepTime>defender.getSleep()?sleepTime:defender.getSleep());
				sleep = true;
			}
		}
	}
	//Calls for a message to be made about the combat
	addMessage(attacker, defender, hit, dead, sleep);
}

//This is another step a player must go through in combat to figure out which monster it is attacking, once it does it calls combat
void Map::playerAttack(int r, int c)
{
	for (int i = 0; i < monsters.size(); i++)
		if (monsters[i]->getR() == r && monsters[i]->getC() == c)
			combat(player, *monsters[i]);
}

//Adds messages about the combat for the turn, creates a message based on who attacked who, find their weapons, and uses hit, dead, and sleep to add on appropriate endings to the message
void Map::addMessage(Actor& attacker, Actor& defender, bool hit, bool dead, bool sleep)
{
	std::string message = attacker.getName();
	message += " ";
	message += attacker.getWeapon().getAttack();
	message += " ";
	message += attacker.getWeapon().getName();
	message += " at ";
	message += defender.getName();
	if (dead)
		message += " dealing the final blow.";
	else if (hit)
		message += " and hits.";
	else
		message += " and misses.";
	if (sleep)
	{
		message.pop_back();
		message += ", putting " + defender.getName() + " to sleep.";
	}
	//Adds the message to the message list ot be played during the display section of Game.cpp
	messages.push_back(message);
}

//The first part of the goblin map algorithm resets the goblin map to all 99 and then calls the recursive part
void Map::updateGoblinMap()
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			goblinMap[i][j] = 99;
		}
	}
	updateGoblinMapHelper(smellDistance, player.getR(), player.getC());
}

//The recursive part of the goblin map algorithm
//Takes a distance which is equal to (goblinSmellDistance - distance from the player) such that if the distance is 0 that spot (denoted by r and c) is goblinSmellDistance spots away from the player
//When this is finished running it will create a map where all tiles are 99 except the tiles that can be reached within goblinSmellDistance of the player, all of which will be marked by how far away from the player the player, taking into account walls and monsters, they are
void Map::updateGoblinMapHelper(int distance, int r, int c)
{
	//If the distance variable is 0 or the coordinates are at the edge of the map or out of bounds, or the current location is already a smaller number than this can make it, do nothing
	if (distance == 0 || r < 1 || c < 1 || r > 17 || c > 68 || goblinMap[r][c] < smellDistance - distance)
		return;

	//Otherwise make the current location a number equal to how many not occupied by wall or monster tiles the current tile is away from the player
	goblinMap[r][c] = smellDistance - distance;
	//Then check if any of the adjacent tiles are able to be walked on (not walls or monsters) and then run the recursive algorithm with them, decreasing distance by 1
	if (floor[r + 1][c] != '#' && floor[r + 1][c] != 'G' && floor[r + 1][c] != 'S' && floor[r + 1][c] != 'B' && floor[r + 1][c] != 'D')
		updateGoblinMapHelper(distance - 1, r + 1, c);
	if (floor[r - 1][c] != '#' && floor[r - 1][c] != 'G' && floor[r - 1][c] != 'S' && floor[r - 1][c] != 'B' && floor[r - 1][c] != 'D')
		updateGoblinMapHelper(distance - 1, r - 1, c);
	if (floor[r][c + 1] != '#' && floor[r][c + 1] != 'G' && floor[r][c + 1] != 'S' && floor[r][c + 1] != 'B' && floor[r][c + 1] != 'D')
		updateGoblinMapHelper(distance - 1, r, c + 1);
	if (floor[r][c - 1] != '#' && floor[r][c - 1] != 'G' && floor[r][c - 1] != 'S' && floor[r][c - 1] != 'B' && floor[r][c - 1] != 'D')
		updateGoblinMapHelper(distance - 1, r, c - 1);
}