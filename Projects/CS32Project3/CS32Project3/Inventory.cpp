#include "Inventory.h"

Inventory::Inventory()
{
}

//Deletes the items and clears the item list
Inventory::~Inventory()
{
	for (int i = 0; i < items.size(); i++)
		delete items[i];
	items.clear();
}

//Shows the inventory screen by clearing the screen and the pasting the inventory items after a letter corresponding to that item
//Closes after the player presses a button on the keyboard
char Inventory::show()
{
	clearScreen();
	for (int i = 0; i < items.size(); i++)
	{
		std::cout << alphabet[i] << ". ";
		std::cout << items[i]->getName() << std::endl;
	}
	return getCharacter();
}

//If there are fewer than 26 items in the inventory, it adds another, called when player picks up an item
void Inventory::addItem(std::string temp)
{
	if (items.size() <= 25)
	{
		if (temp == "short sword" || temp == "long sword" || temp == "mace" || temp == "magic fangs of sleep" || temp == "magic axe")
			items.push_back(new Weapon(temp, -1, -1));
		else
			items.push_back(new Scroll(temp, -1, -1));
	}
}

//Called when player uses the 'w' command, shows the inventory, waits for the player to select a letter, then returns true if that letter corresponds to a weapon
//The weapon name is given to temp for use in determining what weapon to equip the player with
bool Inventory::wield(std::string &temp)
{
	char selected = show();
	for (int i = 0; i < items.size(); i++)
	{
		if (selected == alphabet[i] && items[i]->getSymbol() == ')')
		{
			temp = items[i]->getName();
			return true;
		}
		else if (selected == alphabet[i])
			temp = items[i]->getName();
	}
	return false;
}

//Called when the player uses the 'r' command, shows the inventory and waits for the player to select a letter, then returns true if that letter corresponds to a scroll
//The scroll name is stored in temp for future use
bool Inventory::read(std::string &temp)
{
	char selected = show();
	for (int i = 0; i < items.size(); i++)
	{
		if (selected == alphabet[i] && items[i]->getSymbol() == '?')
		{
			temp = items[i]->getName();
			delete items[i];
			items.erase(items.begin() + i);
			return true;
		}
		else if (selected == alphabet[i])
			temp = items[i]->getName();
	}
	return false;
}