#include "newSet.h"

Set::Set()
{
	setSize = 0;
	container = new ItemType[DEFAULT_MAX_ITEMS];
	maxSize = DEFAULT_MAX_ITEMS;
}

Set::Set(int x)
{
	setSize = 0;
	container = new ItemType[x];
	maxSize = x;
}

Set::~Set()
{
	delete[] container;
}

Set::Set(const Set& other)
{
	setSize = other.setSize;
	container = new ItemType[other.maxSize];
	maxSize = other.maxSize;
	for (int i = 0; i < setSize; i++)
	{
		container[i] = other.container[i];
	}
}

Set& Set::operator=(const Set& other)
{
	if (this != &other)
	{
		Set temp(other);
		swap(temp);
	}
	return *this;
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

bool Set::insert(const ItemType& value)
{
	if (setSize < maxSize)
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
			while (i < setSize)
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

bool Set::contains(const ItemType& value) const
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
	int tempSize = setSize;
	setSize = other.size();
	other.setSize = tempSize;
	int tempMax = maxSize;
	maxSize = other.maxSize;
	other.maxSize = tempMax;

	ItemType* tempContainer = container;
	container = other.container;
	other.container = tempContainer;
}