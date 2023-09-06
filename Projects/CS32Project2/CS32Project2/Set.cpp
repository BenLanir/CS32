#include "Set.h"

//This struct will act as each of our nodes in our list
//value will store the value, next will point to the next node, previous will point to the previous node
struct Set::Node
{
	ItemType value;
	Node* next;
	Node* previous;
};

Set::Set()
{
	head = nullptr;
}

//Destructor
Set::~Set()
{
	//If the list is empty we only need to delete the pointer "head"
	if (!empty())
	{
		Node* p;
		p = head;

		//Reach end of linked list
		while (p->next != nullptr)
		{
			p = p->next;
		}

		//Move from end to beginning of linked list, deleting nodes along the way
		while (p->previous != nullptr)
		{
			p = p->previous;
			delete p->next;
		}
		delete head;
	}
}


//Copy constructor
Set::Set(const Set& other)
{
	head = nullptr;

	//Cycle through the other list retrieving its values and inserting them in the new list
	for (int i = 0; i < other.size(); i++)
	{
		ItemType value;
		other.get(i, value);
		this->insert(value);
	}
}


//Operator =
Set& Set::operator=(const Set& rhs)
{
	//Create a copy set of the passed set then swap it with our current set
	Set temp(rhs);
	swap(temp);
	return *this;
}

//Check if empty
bool Set::empty() const
{
	//if it is empty the head points to the nullptr
	if (head == nullptr)
	{
		return true;
	}
	return false;
}

//Returns size of linked list
int Set::size() const
{
	int tempSize = 0;
	Node* p = head;

	//Go to each item in the linked list and keep a tally of how many you have been to, then return the final tally
	while (p != nullptr)
	{
		tempSize++;
		p = p->next;
	}
	return tempSize;
}

//Check to see if value is contained
bool Set::contains(const ItemType& value) const
{
	Node* p = head;

	//Traverse the set and check if the value of the node is the same as the given value at some point, return false if not
	while (p != nullptr)
	{
		if (p->value == value)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}

//Insert items into the set, nodes are inserted such that values are in sequential order
bool Set::insert(const ItemType& value)
{
	//Only insert if the set does not yet contain that value
	if (this->contains(value))
	{
		return false;
	}

	//Case 1, the empty set: create a new node with value set head to that new node and the new nodes previous and next to the null pointer
	Node* p = head;
	if (p == nullptr)
	{
		Node* inserted;
		inserted = new Node;
		inserted->value = value;
		inserted->next = nullptr;
		inserted->previous = nullptr;
		head = inserted;
		return true;
	}

	//Case 2, inserting at the beginning: create a new node with the value, set head to that new node and
	//set the next value to be the old first item and the previous item to nullptr, set the old first items
	//next value to be the new node
	if (p->value > value)
	{
		Node* inserted;
		inserted = new Node;
		inserted->value = value;
		inserted->next = p;
		p->previous = inserted;
		inserted->previous = nullptr;
		head = inserted;
		return true;
	}

	//Case 3, new node is in the middle or at the end: create a new node, store the value, link it between two others setting the node before
	//the new one's next, and the node after the new one's previous to be the node and setting the node's next and previous to be those two respectively
	while (p->next != nullptr && p->next->value < value)
	{
		p = p->next;
	}
	Node* inserted;
	inserted = new Node;
	inserted->value = value;
	inserted->next = p->next;
	inserted->previous = p;
	p->next = inserted;

	//Special case for end: do the same as above but don't change the next node (as there is no next node) and set next to nullptr
	if (inserted->next != nullptr)
	{
		inserted->next->previous = inserted;
	}
	return true;
}

//Get the smallest item strictly greater than i items
bool Set::get(int i, ItemType& value) const
{
	//Check to make sure i is in range of the list
	if (i < 0 || i >= this->size())
	{
		return false;
	}

	//Since the list is ordered this part just traverses the list to the i+1th term and sets value to that
	Node* p = head;
	for (int j = 0; j < i; j++)
	{
		p = p->next;
	}
	value = p->value;
	return true;
}


//Swap two sets
void Set::swap(Set &other)
{
	//Creates a temporary node and then swaps the value of the two heads storing the value of the other in temp during the switch
	Node* temp;
	temp = other.head;
	other.head = head;
	head = temp;
}

//Erase the given node if it contains that value
bool Set::erase(const ItemType& value)
{
	//Check if the list contains the value to be erased and return false if it doesn't
	if (!contains(value))
	{
		return false;
	}

	//If there is only one node delete that node, set the head to nullptr
	if (size() == 1)
	{
		delete head;
		head = nullptr;
		return true;
	}

	//Cycle to find which node has that value
	Node* p = head;
	while (p->value != value)
	{
		p = p->next;
	}

	//Case 1, node is the last node: link the previous node's next to nullptr and delete the node
	if (p->next == nullptr)
	{
		p->previous->next = p->next;
		delete p;
		return true;
	}

	//Case 2, node is first node: link the next node's previous to nullptr, set the head to the next node and delete the node
	if (p->previous == nullptr)
	{
		p->next->previous = p->previous;
		head = p->next;
		delete p;
		return true;
	}

	//Case 3, middle node: set the next node's previous to the previous node, the previous node's next to the next node, and delete the node
	p->previous->next = p->next;
	p->next->previous = p->previous;
	delete p;
	return true;
}


//Dump function
void Set::dump() const
{
	//If the list is empty do nothing
	if (head != nullptr)
	{
		Node* p;
		p = head;
		std::cerr << p->value << std::endl;

		//Print out all values going forward through the linked list
		while (p->next != nullptr)
		{
			std::cerr << p->next->value << std::endl;
			p = p->next;
		}
		std::cerr << p->value << std::endl;

		//Print out all values going backward thorugh the linked list (this ensures that my backward linking worked as well)
		while (p->previous != nullptr)
		{
			std::cerr << p->previous->value << std::endl;
			p = p->previous;
		}
	}
}

//Changes result to be a linked list with all the values present in s1 but not in s2
void subtract(const Set& s1, const Set& s2, Set& result)
{
	//Create a temporary list (in case result and s1 or s2 are the same) to create this list, and set it to s1
	Set temp;
	temp = s1;
	ItemType tempValue;
	//Cycle through the s2, erasing from temp each of it's values, since erase returns false and changes nothing if the value is not present
	//this only affects the values from s2 which are in temp
	for (int i = 0; i < s2.size(); i++)
	{
		s2.get(i, tempValue);
		temp.erase(tempValue);
	}
	//Swap temp and result so that result is changed to the subtracted version
	result.swap(temp);
}

//Unite two sets in another set called result
void unite(const Set& s1, const Set& s2, Set& result)
{
	//Use a temp set to make sure nothing goes wrong if the passed result is the same set as s1 and s2, I will swap this at the end with result
	Set temp;

	//Set the temporary variable to s2, then cycle through s1 inserting each of its values, since insert changes nothing if the value
	//is already present, this already prevents duplicates and thus completes the task
	temp = s2;
	ItemType tempValue;
	for (int i = 0; i < s1.size(); i++)
	{
		s1.get(i, tempValue);
		temp.insert(tempValue);
	}
	result.swap(temp);
}