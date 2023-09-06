#ifndef ITEMS_DEFINED
#define ITEMS_DEFINED

#include <string>
#include <iostream>

//Get and set functions are self explanatory
class Item
{
public:
	Item();
	virtual ~Item() = default;
	char getSymbol() { return symbol; }
	void setSymbol(char c) { symbol = c; }
	void setName(std::string temp) { name = temp; }
	std::string getName() { return name; }
	int getR() { return r; }
	int getC() { return c; }
	void setR(int temp) { r = temp; }
	void setC(int temp) { c = temp; }
private:
	char symbol;
	std::string name;
	int r, c;
};

//Child of item
class Weapon : public Item
{
public:
	Weapon(std::string type, int row, int col);
	virtual ~Weapon() {}
	int getDex() { return dex; }
	void setDex(int temp) { dex = temp; }
	int getStrength() { return strength; }
	void setStrength(int temp) { strength = temp; }
	std::string getAttack() { return attack; }
private:
	int dex, strength;
	std::string attack; //A description of how this weapon attacks
};

//Child of item
class Scroll : public Item
{
public:
	Scroll(std::string scrollName, int row, int col);
	virtual ~Scroll() {}
	char getType() { return type; }
	void setType(char temp) { type = temp; }
private:
	char type;
};


#endif