#include "Items.h"

Item::Item()
{
}

//Initializes the weapon at the coordinates specified, it decided what the Dex and Strength of the weapon are based on the passed weapon name, and names the weapon the passed weapon name
Weapon::Weapon(std::string type, int row, int col)
{
	setR(row);
	setC(col);
	setSymbol(')');
	setName(type);
	if (type == "mace")
	{
		setDex(0);
		setStrength(2);
		attack = "swings";
	}
	else if (type == "short sword")
	{
		setDex(0);
		setStrength(2);
		attack = "slashes";
	}
	else if (type == "long sword")
	{
		setDex(2);
		setStrength(4);
		attack = "slashes";
	}
	else if (type == "magic axe")
	{
		setDex(5);
		setStrength(5);
		attack = "swings";
	}
	else if (type == "magic fangs of sleep")
	{
		setDex(3);
		setStrength(2);
		attack = "strikes";
	}
}

//Initializes the scroll with the coordinates given, gives a scroll type based on the name of the scroll for easier use of scroll
Scroll::Scroll(std::string scrollName, int row, int col)
{
	setR(row);
	setC(col);
	setSymbol('?');
	setName(scrollName);
	if (scrollName == "a scroll of teleportation")
		type = 't';
	else if (scrollName == "a scroll of improve armor")
		type = 'a';
	else if (scrollName == "a scroll of raise strength")
		type = 's';
	else if (scrollName == "a scroll of enhance health")
		type = 'h';
	else if (scrollName == "a scroll of enhance dexterity")
		type = 'd';
}