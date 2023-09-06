#ifndef ACTORS_DEFINED
#define ACTORS_DEFINED

#include "Inventory.h"
#include <iostream>
#include "Items.h"
using namespace std;

class Map;

//Get and set do what they are told
class Actor
{
public:
	Actor();
	virtual ~Actor() { delete weapon; }
	int getR() { return r; }
	int getC() { return c; }
	void setR(int temp) { r = temp; }
	void setC(int temp) { c = temp; }
	char getSymbol() { return symbol; }
	void setSymbol(char c) { symbol = c; }
	int getMove() { return moveAmt; }
	void setMove(int temp) { moveAmt = temp; }
	int getStrength() { return strength; }
	void setStrength(int temp) { strength = temp; }
	int getDex() { return dex; }
	void setDex(int temp) { dex = temp; }
	int getHP() { return hp; }
	void setHP(int temp) { hp = temp; }
	int getMaxHP() { return maxHP; }
	void setMaxHP(int temp) { maxHP = temp; }
	int getSleep() { return sleep; }
	void setSleep(int temp) { sleep = temp; }
	int getArmor() { return armor; }
	void setArmor(int temp) { armor = temp; }
	Weapon& getWeapon() { return *weapon; }
	void setWeapon(Weapon* temp);
	std::string getName() { return name; }
	void setName(std::string temp) { name = temp; }

private:
	int strength, dex, hp, maxHP, sleep, armor;
	int r, c;
	char symbol;
	int moveAmt;
	Weapon *weapon;
	std::string name;
};

//Child of actor
class Player : public Actor
{
public:
	Player();
	virtual ~Player() {}
	void pickup(Item* pickedUp);
	Inventory& getInventory() { return myInventory; }
	bool read(std::string &temp, std::string &extra);
private:
	int strength, dex, hp, maxHP, sleep, armor;
	int r, c;
	Inventory myInventory;
	char symbol;
};

//Child of actor
class Bogeyman : public Actor
{
public:
	Bogeyman(int row, int col);
	virtual ~Bogeyman() {}
private:
	int moveAmt;
	int strength, dex, hp, maxHP, sleep, armor;
	int r, c;
	char symbol;
};

//Child of actor
class Snakewoman : public Actor
{
public:
	Snakewoman(int row, int col);
	virtual ~Snakewoman() {}
private:
	int strength, dex, hp, maxHP, sleep, armor;
	int r, c;
	char symbol;
};

//Child of actor
class Goblin : public Actor
{
public:
	Goblin(int row, int col);
	virtual ~Goblin() {}
private:
};

//Child of actor
class Dragon : public Actor
{
public:
	Dragon(int row, int col);
	virtual ~Dragon() {}
};

#endif