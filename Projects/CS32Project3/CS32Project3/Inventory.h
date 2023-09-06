#ifndef INVENTORY_DEFINED
#define INVENTORY_DEFINED

#include "Items.h"
#include <vector>
#include <iostream>
#include "utilities.h"

class Inventory
{
public:
	Inventory();
	~Inventory();
	char show();
	void addItem(std::string temp);
	bool wield(std::string &temp);
	bool read(std::string &temp);
private:
	std::vector<Item*> items; //Will hold pointers to items in the inventory
	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
						  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; //This is to list the items
};

#endif