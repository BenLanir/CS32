#include "Actor.h"
#include "Map.h"

//All constructors (actor and its children) intialize r and c to -1 and the stats to their appropriate values, give appropriate weapons, names, and symbols
Actor::Actor() : armor(2), strength(2), r(-1), c(-1), dex(2), hp(20), maxHP(20), sleep(0)
{
}

void Actor::setWeapon(Weapon* temp)
{
	weapon = temp;
}


Player::Player() : myInventory()
{
	armor = 2;
	strength = 2;
	r = -1;
	c = -1;
	dex = 2;
	hp = 20;
	maxHP = 20;
	sleep = 0;
	symbol = '@';
	setWeapon(new Weapon("short sword", -1, -1));
	setName("Player");
	myInventory.addItem(getWeapon().getName());
}

//For when the player picks up an item
void Player::pickup(Item* pickedUp)
{
	myInventory.addItem(pickedUp->getName());
}

//Figures out what scroll was read, updates the appropriate stat, and changes temp and extra the appropriate scroll name and additional message, returns true if a scroll was read
bool Player::read(std::string &temp, std::string &extra)
{
	if (myInventory.read(temp))
	{
		if (temp == "a scroll of teleportation")
		{
			extra = "You feel your body wrencehd in space and time";
		}
		else if (temp == "a scroll of improve armor")
		{
			setArmor(getArmor() + randInt(1, 3));
			extra = "Your armor glows blue";
			if (getArmor() > 99)
				setArmor(99);
		}
		else if (temp == "a scroll of raise strength")
		{
			setStrength(getStrength() + randInt(1, 3));
			extra = "You feel your muscles bulge";
			if (getStrength() > 99)
				setStrength(99);
		}
		else if (temp == "a scroll of enhance dexterity")
		{
			setDex(getDex() + 1);
			extra = "You feel like less of a klutz";
			if (getDex() > 99)
				setDex(99);
		}
		else if (temp == "a scroll of enhance health")
		{
			setMaxHP(getMaxHP() + randInt(3, 8));
			extra = "You feel your heart beating stronger";
			if (getMaxHP() > 99)
				setMaxHP(99);
		}
		return true;
	}
	return false;
}

Bogeyman::Bogeyman(int row, int col) : Actor()
{
	setR(row);
	setC(col);
	setArmor(2);
	setStrength(randInt(2, 3));
	setDex(randInt(2, 3));
	setHP(randInt(5, 10));
	setMaxHP(getHP());
	setSleep(0);
	setSymbol('B');
	setMove(5);
	setWeapon(new Weapon("short sword", -1, -1));
	setName("the Bogeyman");
}

Snakewoman::Snakewoman(int row, int col) : Actor()
{
	setR(row);
	setC(col);
	setArmor(3);
	setStrength(2);
	setDex(3);
	setHP(randInt(3, 6));
	setMaxHP(getHP());
	setSleep(0);
	setSymbol('S');
	setMove(3);
	setWeapon(new Weapon("magic fangs of sleep", -1, -1));
	setName("the Snakewoman");
}

Goblin::Goblin(int row, int col) : Actor()
{
	setR(row);
	setC(col);
	setArmor(1);
	setStrength(3);
	setDex(1);
	setHP(randInt(15, 20));
	setMaxHP(getHP());
	setSleep(0);
	setSymbol('G');
	setMove(1);
	setWeapon(new Weapon("short sword", -1, -1));
	setName("the Goblin");
}

Dragon::Dragon(int row, int col) : Actor()
{
	setR(row);
	setC(col);
	setArmor(4);
	setStrength(4);
	setDex(4);
	setHP(randInt(20, 25));
	setMaxHP(getHP());
	setSleep(0);
	setSymbol('D');
	setMove(1);
	setWeapon(new Weapon("long sword", -1, -1));
	setName("the Dragon");
}