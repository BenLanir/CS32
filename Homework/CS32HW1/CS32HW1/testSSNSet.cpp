#include "SSNSet.h"
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
	SSNSet test;
	SSNSet test2;
	test.add(123);
	test.add(456);
	assert(!test.add(123));
	test2.add(789);
	test = test2;
	test.print();
}