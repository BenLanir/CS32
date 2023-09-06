#include "Set.h"

Set::Set()
{
	setSize = 0;
}

bool Set::empty() const
{
	if (setSize == 0)
	{
		return true;
	}
	return false;
}

int Set::size() const
{
	return setSize;
}

bool Set::insert(const ItemType &value)
{
	if (setSize < DEFAULT_MAX_ITEMS)
	{
		for (int i = 0; i < setSize; i++)
		{
			if (value == container[i])
			{
				return false;
			}
		}
		for (int i = 0; i <= setSize; i++)
		{
			if (value <= container[i] && (i != setSize))
			{
				int j = setSize;
				while (j > i)
				{
					container[j] = container[j - 1];
					j--;
				}
				container[i] = value;
				setSize++;
				i = setSize;
			}
			else if (i == setSize)
			{
				container[i] = value;
				setSize++;
				i = setSize;
			}
		}
		return true;
	}
	return false;
}

bool Set::erase(const ItemType& value)
{
	for (int i = 0; i < setSize; i++)
	{
		if (container[i] == value)
		{
			while(i < setSize)
			{
				container[i] = container[i + 1];
				i++;
			}
			setSize--;
			return true;
		}
	}
	return false;
}

bool Set::contains(const ItemType &value) const
{
	for (int i = 0; i < setSize; i++)
	{
		if (container[i] == value)
		{
			return true;
		}
	}
	return false;
}

bool Set::get(int i, ItemType& value) const //will the same item ever be put into the set???
{
	if (i >= setSize || i < 0) //test to make sure < vs <= and > vs >=
	{
		return false;
	}
	value = container[i];	
	return true;
}

void Set::swap(Set& other)
{
	//ItemType* temp = &other.container[0];
	ItemType temp;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		temp = other.container[i];
		other.container[i] = container[i];
		container[i] = temp;
	}
	int tempSize = setSize;
	setSize = other.size();
	other.setSize = tempSize;
}