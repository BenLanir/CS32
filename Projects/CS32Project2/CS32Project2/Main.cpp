#include <iostream>
#include "Set.h"
#include <cassert>

using namespace std;

int main()
{
	Set s;
	assert(s.empty());					//test empty
	assert(s.size() == 0);				//test size
	assert(s.insert("giraffe"));		//test insert
	assert(s.insert("lion"));			//test multiple inserts
	assert(s.erase("giraffe"));			//test erase
	assert(!s.contains("giraffe"));		//test contains
	Set q(s);							//test copy constructor
	assert(q.size() == 1);				//test size (also that erase worked)
	assert(q.insert("bear"));			//test insertion at beginning
	assert(q.insert("zebra"));			//test insertion at end
	Set r;
	r.insert("elephant");
	r = q;								//test operator=
	assert(!r.contains("elephant"));	//test to make sure operator= worked
	assert(r.size() == 3);				//test to make sure operator= worked
	assert(r.erase("zebra"));			//test erasing at end
	assert(q.size() == 3);				//test to make sure r doesn't change q
	r.insert("alpaca");
	s.swap(r);
	assert(s.contains("alpaca"));		//test swap
	assert(r.size() == 1);				//test swap
	std::string temp;
	assert(r.get(0, temp));				//test get
	assert(temp == "lion");				//test get
	assert(r.erase(temp));				//test erasing only item
	Set t;
	subtract(s, q, t);
	assert(t.size() == 1);				//test subtract
	assert(t.contains("alpaca"));		//test subtract
	unite(s, q, t);
	assert(t.size() == 4);				//test unite
	subtract(t, q, t);
	assert(t.size() == 1);				//test subtract works with aliasing
	unite(s, q, s);
	assert(s.size() == 4);				//test unite works with aliasing
}